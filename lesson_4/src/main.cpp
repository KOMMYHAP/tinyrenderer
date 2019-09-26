#include <cmath>
#include <utility>
#include <iostream>

#include "tgaimage.h"
#include "geometry.h"
#include "model.h"

void DoLine(int x0, int y0, int x1, int y1, TGA::Image & image, TGA::Color color);
void DoLine(geometry::Vec2i p0, geometry::Vec2i p1, TGA::Image & image, TGA::Color color);
void DoTriangle(std::array<geometry::Vec2i, 3> points, TGA::Image & image, TGA::Color color);

void DoLine(int x0, int y0, int x1, int y1, TGA::Image & image, TGA::Color color)
{
	using std::abs;
	using std::swap;

	bool isSteep = false;
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		isSteep = true;
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}
	
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror = abs(dy) * 2;
	int error = 0;

	int y = y0;

	for (int x = x0; x <= x1; ++x)
	{
		if (isSteep)
		{
			image.set(y, x, color);
		}
		else
		{
			image.set(x, y, color);
		}

		error += derror;
		if (error > dx)
		{
			y += (y1 > y0) ? 1 : -1;
			error -= dx * 2;
		}
	}
}

void DoLine(geometry::Vec2i p0, geometry::Vec2i p1, TGA::Image & image, TGA::Color color)
{
	DoLine(p0[0], p0[1], p1[0], p1[1], image, std::move(color));
}

void DoTriangle(std::array<geometry::Vec2i, 3> points, TGA::Image & image, TGA::Color color)
{
	geometry::Vec2i bbox_min {image.get_width() - 1, image.get_height() - 1};
	geometry::Vec2i bbox_max {0, 0};

	for (auto && point : points)
	{
		for (int i = 0; i < 2; ++i)
		{
			bbox_min[i] = std::min(bbox_min[i], point[i]);
			bbox_max[i] = std::max(bbox_max[i], point[i]);
		}
	}
	
	for (int y = bbox_min[1]; y <= bbox_max[1]; ++y)
	{
		for (int x = bbox_min[0]; x <= bbox_max[0]; ++x)
		{
			geometry::Vec2i p {x, y};
			auto u = geometry::ConvertToBarycentric(points[0], points[1], points[2], p);

			if (u[0] >= 0.0f && u[1] >= 0.0f && u[2] >= 0.0f)
			{
				image.set(x, y, color);
			}
		}	
	}
}

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
		using namespace geometry;

		std::array<Vec2i, 3> screenVertexes;
		std::array<Vec3f, 3> worldVertexes;

		for (int i = 0; i < 3; ++i)
		{
			auto v = model->vertexes[face[i]];
			worldVertexes[i] = v;
			screenVertexes[i] = ConvertToModelPos(v);
		}

		auto n = Normalize(CrossProduct(worldVertexes[2] - worldVertexes[0], worldVertexes[1] - worldVertexes[0]));

		auto intensity = ScalarProduct(n, light_pos);
		if (intensity > 0.0f)
		{
			auto value = Vec3f {1.0f, 1.0f, 1.0f} * intensity;
			TGA::Color color {value.m_data, 3};
			DoTriangle(screenVertexes, image, ClampColor(color, TGA::black, TGA::white));
		}
		else
		{
			int a = 1;
		}
	}

	image.flip_vertically();
	if (!image.write_tga_file("lesson_4_result.tga"))
	{
		std::cerr << "Cannot write result tga file!" << std::endl;
		return 1;
	}

	return 0;
}
