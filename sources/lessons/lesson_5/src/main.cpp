#include "basic_defs.h"
#include <cmath>
#include <iostream>

#include "model.h"
#include "painter.h"

int main(int argc, char ** argv)
{
	auto model = model::LoadFromFile("../../models/african_head.obj");
	if (!model)
	{
		std::cerr << "Cannot load model from file!" << std::endl;
		return 1;
	}

	int w = 1000, h = 1000;
	TGA::Image image {w, h, 3};
	Painter painter(image);

	auto ConvertToModelPos = [w, h](const geometry::Vec3f & v)
	{
		return geometry::Vec2i {
			static_cast<int>((v[0] + 1.0f) * w / 2),
			static_cast<int>((v[1] + 1.0f) * h / 2)
		};
	};
	
	auto GetRandColor = []()
	{
		return TGA::Color{
			static_cast<unsigned char>(rand() % 255),
			static_cast<unsigned char>(rand() % 255),
			static_cast<unsigned char>(rand() % 255),
			static_cast<unsigned char>(255)
		};
	};

	auto ClampColor = [](TGA::Color value, TGA::Color min, TGA::Color max)
	{
		return TGA::Color {
			std::clamp(value.raw[0], min.raw[0], max.raw[0]),
			std::clamp(value.raw[1], min.raw[1], max.raw[1]),
			std::clamp(value.raw[2], min.raw[2], max.raw[2]),
			std::clamp(value.raw[3], min.raw[3], max.raw[3]),
		};
	};

	geometry::Vec3f light_pos {0.0f, 0.0f, -1.0f};

	for (auto && face : model->faces)
	{
		std::array<geometry::Vec2i, 3> screenVertexes;
		std::array<geometry::Vec3f, 3> worldVertexes;

		for (int i = 0; i < 3; ++i)
		{
			auto v = model->vertexes[face[i]];
			worldVertexes[i] = v;
			screenVertexes[i] = ConvertToModelPos(v);
		}

		auto crossProduct = geometry::CrossProduct(worldVertexes[2] - worldVertexes[0], worldVertexes[1] - worldVertexes[0]);
		auto n = geometry::Normalize(crossProduct);

		auto intensity = ScalarProduct(n, light_pos);
		if (intensity > 0.0f)
		{
			auto value = geometry::Vec3f {1.0f, 1.0f, 1.0f} * intensity;
			TGA::Color color {value.m_data, 3};
			auto clampedColor = ClampColor(color, TGA::black, TGA::white);
			painter.SetColor(clampedColor);

			painter.DoTriangle(screenVertexes);
		}
	}

	image.flip_vertically();
	if (!image.write_tga_file("lesson_5_result.tga"))
	{
		std::cerr << "Cannot write result tga file!" << std::endl;
		return 1;
	}

	return 0;
}
