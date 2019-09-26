#include <cmath>
#include <utility>
#include <iostream>

#include "tgaimage.h"
#include "model.h"

void DoLine(int x0, int y0, int x1, int y1, TGA::Image & image, TGA::Color color);
void DoLine(Vec2i p0, Vec2i p1, TGA::Image & image, TGA::Color color);
void DoTriangle(Vec2i p0, Vec2i p1, Vec2i p2, TGA::Image & image, TGA::Color color);

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

void DoLine(Vec2i p0, Vec2i p1, TGA::Image & image, TGA::Color color)
{
	DoLine(p0.x, p0.y, p1.x, p1.y, image, std::move(color));
}

void DoTriangle(Vec2i p0, Vec2i p1, Vec2i p2, TGA::Image & image, TGA::Color color)
{
	using std::swap, std::min, std::max;

	// sort vertexes by Y: p0 < p1 < p2
	if (p0.y > p1.y)
	{
		swap(p0, p1);
	}
	if (p0.y > p2.y)
	{
		swap(p0, p2);
	}
	if (p1.y > p2.y)
	{
		swap(p1, p2);
	}
	
	auto ComputeX = [](Vec2i p0, Vec2i p1, int y)
	{
		if (p1.y == p0.y)
		{
			return float(p1.x);
		}
		return (p1.x - p0.x) * (y - p0.y) / static_cast<float>(p1.y - p0.y) + p0.x;
	};

	std::array<Vec2i, 3> pivots {p0, p1, p2};

	int ymin = p0.y, ymax = p2.y;

	for (int y = ymin; y <= ymax; ++y)
	{
		if (y == p1.y)
		{
			pivots = {p2, p0, p1};
		}
		int x1 = ComputeX(pivots[0], pivots[1], y);
		int x2 = ComputeX(pivots[0], pivots[2], y);
		DoLine(x1, y, x2, y, image, color);
	}
}

int main(int argc, char ** argv)
{
	auto model = ObjModel::LoadFromFile("../../models/african_head.obj");
	if (!model)
	{
		std::cerr << "Cannot load model from file!" << std::endl;
		return 1;
	}

	int w = 1000, h = 1000;
	TGA::Image image {w, h, 3};

	auto ConvertToModelPos = [w, h](const Vec3f & v)
	{
		return Vec2i {
			static_cast<int>((v.x + 1.0f) / 2 * (w - 1)),
			static_cast<int>((v.y + 1.0f) / 2 * (h - 1))
		};
	};

	for (auto && face : model->faces)
	{
		auto p0 = ConvertToModelPos(model->vertexes[face[0]]);
		auto p1 = ConvertToModelPos(model->vertexes[face[1]]);
		auto p2 = ConvertToModelPos(model->vertexes[face[2]]);
		DoTriangle(p0, p1, p2, image, TGA::white);
	}

	image.flip_vertically();
	if (!image.write_tga_file("lesson_4_result.tga"))
	{
		std::cerr << "Cannot write result tga file!" << std::endl;
		return 1;
	}

	return 0;
}
