#include "tgaimage.h"

void DoLine(int x0, int y0, int x1, int y1, TGA::Image & image, TGA::Color color);

void DoLine(int x0, int y0, int x1, int y1, TGA::Image & image, TGA::Color color)
{
	for (float t = 0.0; t <= 1.0f; t += 0.001f)
	{
		int x = x0 + (x1 - x0) * t;
		int y = y0 + (y1 - y0) * t;
		image.set(x, y, color);
	}
}

int main(int argc, char ** argv)
{
	int w = 100, h = 100;
	TGA::Image image {w, h, 3};

	int step = 10;
	for (int x = 0; x < w; x += step)
	{
		DoLine(x, 0, x, h, image, TGA::red);
	}

	if (!image.write_tga_file("test.tga"))
	{
		return 1;
	}

	return 0;
}
