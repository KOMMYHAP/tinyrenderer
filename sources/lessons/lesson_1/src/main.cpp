#include "tgaimage.h"

int main(int argc, char ** argv)
{
	int w = 100, h = 100;
	TGA::Image image {w, h, 3};

	int step_x = 10;
	for (int x = 0; x < w; x += step_x)
	{
		int step_y = 3;
		for (int y = 0; y < h; y += step_y)
		{
			image.set(x, y, TGA::red);
		}
	}

	image.write_tga_file("test.tga");

	return 0;
}
