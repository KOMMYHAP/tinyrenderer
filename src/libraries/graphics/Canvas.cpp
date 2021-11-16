#include "Canvas.h"

#include "Model.h"
#include "MathLib.h"
#include "Utils.h"
#include "tgaimage.h"

namespace Graphics
{
	Canvas::Canvas() = default;

	Canvas::Canvas(uint32_t sizeX, uint32_t sizeY)
		: _texture(sizeX, sizeY)
		, _zBuffer(sizeX * sizeY, -std::numeric_limits<float>::infinity())
	{
	}

	void Canvas::Line(const Math::Vec3f & p1, const Math::Vec3f & p2, const Color& color)
	{
		bool steep = false;
		int32_t x0 = p1.x, x1 = p2.x;
		int32_t y0 = p1.y, y1 = p2.y;

		if (std::abs(x0 - x1) < std::abs(y0 - y1))
		{
			std::swap(x0, y0);
			std::swap(x1, y1);
			steep = true;
		}
		if (x0 > x1)
		{
			std::swap(x0, x1);
			std::swap(y0, y1);
		}

		for (uint32_t x = x0; x <= x1; x++)
		{
			float t = 1.0f;
			if (x1 != x0)
			{
				t = static_cast<float>(x - x0) / static_cast<float>(x1 - x0);
			}
			uint32_t y = static_cast<uint32_t>(Math::lerp(y0, y1, t));
			if (steep)
			{
				_texture.Set(y, x, color);
			}
			else
			{
				_texture.Set(x, y, color);
			}
		}
	}

	void Canvas::Triangle(const Math::Vec3f & p1, const Math::Vec3f & p2, const Math::Vec3f & p3, const Color & color)
	{
		ColorFunction getColor = [&color](const ColorContext &)
		{
			return color;
		};
		Triangle(p1, p2, p3, getColor);
	}

	void Canvas::Triangle(const Math::Vec3f& p1, const Math::Vec3f& p2, const Math::Vec3f& p3, ColorFunction colorFunction)
	{
		CheckPointIsInside(Math::Vec3u(p1));
		CheckPointIsInside(Math::Vec3u(p2));
		CheckPointIsInside(Math::Vec3u(p3));
		if (!colorFunction)
		{
			return;
		}

		auto bbox = Math::BoundingBox(p1, p2, p3);
		auto min = Math::Vec3u(bbox.Min());
		auto max = Math::Vec3u(bbox.Max());

		Math::Vec3u it;
		for (it.x = min[0]; it.x <= max[0]; ++it.x)
		{
			for (it.y = min[1]; it.y <= max[1]; ++it.y)
			{
				Math::Vec3f bcPoint = barycentric(p1, p2, p3, Math::Vec3f(it));
				if (bcPoint.x >= 0.0f && bcPoint.y >= 0.0f && bcPoint.z >= 0.0f)
				{
					auto p = Math::Vec3f(
						it.x,
						it.y,
						p1.z * bcPoint.x + p2.z * bcPoint.y + p3.z * bcPoint.z
					);

					ColorContext context;
					context.t = {(it.x - min[0]) / static_cast<float>(max[0] - min[0]), (it.y - min[1]) / static_cast<float>(max[1] - min[1])};
					auto color = colorFunction(context);
					TrySet(p, color);
				}
			}
		}
	}

	void Canvas::Render(const Model & model, const Texture & diffuseTexture, const Math::Vec3f & light)
	{
		const uint32_t w = Width(), h = Height();
		if (w == 0 || h == 0)
		{
			std::cerr << "Canvas is not initialized." << std::endl;
			return;
		}

		const bool diffuseTextureDisabled = diffuseTexture.Height() == 0 || diffuseTexture.Width() == 0;

		if (light.x > 1.0f || light.y > 1.0f || light.z > 1.0f)
		{
			std::cerr << "Light must be a normilized vector." << std::endl;
			return;
		}

		for (const auto & face : model.Faces())
		{
			Math::Vec3f screenCoords[3];
			Math::Vec3f worldCoords[3];
			for (int i = 0; i < 3; i++)
			{
				const auto & vertex = model.Vertex(face.vertices[i]);
				screenCoords[i] = {
					(vertex.x + 1.f) / 2.f * (w - 1),
					(vertex.y + 1.f) / 2.f * (h - 1),
					(vertex.z + 1.f) / 2.f,
				};
				worldCoords[i] = vertex;
			}

			Math::Vec3f normal = Math::CrossProduct(worldCoords[1] - worldCoords[0], worldCoords[2] - worldCoords[0]).normalize();
			const float intensity = Math::ScalarProduct(light, normal);

			if (diffuseTextureDisabled)
			{
				const auto color = Color(
					Math::lerp(0, 255, intensity),
					Math::lerp(0, 255, intensity),
					Math::lerp(0, 255, intensity),
					255);
				Triangle(screenCoords[0], screenCoords[1], screenCoords[2], color);
			}
			else
			{
				auto tv0 = face.textureVertices[0];
				auto tv1 = face.textureVertices[1];
				auto tv2 = face.textureVertices[2];
				auto bbox = Math::BoundingBoxT(model.TextureVertex(tv0), model.TextureVertex(tv1), model.TextureVertex(tv2));
				
				ColorFunction getColor = [&](const ColorContext & context)
				{
					const float u = Math::lerp(bbox.Min().x, bbox.Max().x, context.t.x);
					const float v = Math::lerp(bbox.Min().y, bbox.Max().y, context.t.y);
					auto color = GetDiffuseColor(diffuseTexture, u, v);
					color.a *= intensity;
					color.r *= intensity;
					color.g *= intensity;
					color.b *= intensity;
					return color;
				};
				
				Triangle(screenCoords[0], screenCoords[1], screenCoords[2], getColor);
			}
		}
	}

	bool Canvas::WriteToTga(string_view filename) const
	{
		const uint32_t w = Width(), h = Height();
		auto image = TgaImage(w, h, TgaImage::RGBA);

		for (uint32_t y = 0, yEnd = h / 2; y != yEnd; ++y)
		{
			for (uint32_t x = 0, xEnd = w; x != xEnd; ++x)
			{
				{
					const auto & color = _texture.Get(x, h - y - 1);
					image.Set(x, y, TGAColor(color.r, color.g, color.b, color.a));
				}
				{
					const auto & color = _texture.Get(x, y);
					image.Set(x, h - y - 1, TGAColor(color.r, color.g, color.b, color.a));
				}
			}
		}
		if (h % 2 == 1)
		{
			uint32_t y = h - h / 2 - 1;
			for (uint32_t x = 0, xEnd = w; x != xEnd; ++x)
			{
				const auto & color = _texture.Get(x, y);
				image.Set(x, y, TGAColor(color.r, color.g, color.b, color.a));
			}
		}

		return image.WriteTgaFile(filename.data());
	}

	void Canvas::CheckPointIsInside(const Math::Vec3u& p)
	{
		if (p.x >= Width() || p.y >= Height())
		{
			Utils::OutOfRange("Point [" + std::to_string(p.x) + ", " + std::to_string(p.y) + ", " + std::to_string(p.z) + "] is outside of canvas!");
		}
	}

	void Canvas::TrySet(const Math::Vec3f & point, const Color & color)
	{
		uint32_t pos = point.x + point.y * _texture.Width();
		WUSIKO_ASSERT(pos < _zBuffer.size());
		float & z = _zBuffer[pos];
		if (z < point.z)
		{
			z = point.z;
			auto adjustedColor = Color(
				color.r,
				color.g,
				color.b,
				255 //Math::lerp(0, 255, z)
			);
			_texture.Set(point.x, point.y, adjustedColor);
		}
	}

	Color Canvas::GetDiffuseColor(const Texture& diffuseTexture, float u, float v)
	{
		const int w = diffuseTexture.Width();
		const int h = diffuseTexture.Height();
		if (w == 0 || h == 0)
		{
			return {};
		}

		const int x = static_cast<int>(w * u);
		const int y = static_cast<int>(h * v);
		if (x < w && y < h)
		{
			return diffuseTexture.Get(x, y);
		}
		return {};
	}
}
