#include <cmath>
#include <utility>

#include "tgaimage.h"

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

	for (int x = x0; x <= x1; ++x)
	{
		float t = (x - x0) / static_cast<float>(x1 - x0);
		int y = y0 + t * (y1 - y0);

		if (isSteep)
		{
			image.set(y, x, color);
		}
		else
		{
			image.set(x, y, color);
		}
	}
}

int main(int argc, char ** argv)
{
	int w = 100, h = 100;
	TGA::Image image {w, h, 3};

	DoLine(0, 0, w, h, image, TGA::red);
	DoLine(33, 22, 77, 42, image, TGA::green);
	DoLine(w / 2, 0, w / 2 + 1, h, image, TGA::blue);

	if (!image.write_tga_file("test.tga"))
	{
		return 1;
	}

	return 0;
}
