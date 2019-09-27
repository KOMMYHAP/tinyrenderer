#include <cmath>
#include <utility>
#include <iostream>

#include "tgaimage.h"
#include "model.h"

void DoLine(int x0, int y0, int x1, int y1, TGA::Image & image, TGA::Color color);

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

	for (auto && face : model->faces)
	{
		for (int i = 0; i < 3; ++i)
		{
			auto v0 = model->vertexes[face[i]];
			auto v1 = model->vertexes[face[(i + 1) % 3]];
			
			int x0 = (v0.x + 1.0f) / 2 * (w - 1);
			int y0 = (v0.y + 1.0f) / 2 * (h - 1);
			int x1 = (v1.x + 1.0f) / 2 * (w - 1);
			int y1 = (v1.y + 1.0f) / 2 * (h - 1);

			DoLine(x0, y0, x1, y1, image, TGA::white);
		}
	}

	image.flip_vertically();
	if (!image.write_tga_file("lesson_3_result.tga"))
	{
		std::cerr << "Cannot write result tga file!" << std::endl;
		return 1;
	}

	return 0;
}
