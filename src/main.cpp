#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "BoundingBox.h"
#include "Vector.h"

constexpr TGAColor white = TGAColor(255, 255, 255, 255);
constexpr TGAColor red = TGAColor(255, 0, 0, 255);
unique_ptr<Model> model;
constexpr int width = 800;
constexpr int height = 800;

using namespace mymath;

void line(int x0, int y0, int x1, int y1, TgaImage& image, TGAColor color)
{
	bool steep = false;
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

	for (int x = x0; x <= x1; x++)
	{
		float t = static_cast<float>(x - x0) / static_cast<float>(x1 - x0);
		int y = static_cast<int>(static_cast<float>(y0) * (1.0f - t) + static_cast<float>(y1) * t);
		if (steep)
		{
			image.Set(y, x, color);
		}
		else
		{
			image.Set(x, y, color);
		}
	}
}

Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P)
{
	Vec3f s[2];
	for (int i = 2; i--;)
	{
		s[i][0] = C[i] - A[i]; // x
		s[i][1] = B[i] - A[i]; // y
		s[i][2] = A[i] - P[i]; // z
	}
	// Vec3f u = cross(s[0], s[1]);
	// if (std::abs(u[2]) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
		// return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
	return Vec3f(-1, 1, 1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}

void triangle(Vec3f* pts, vector<float> & zbuffer, TgaImage& image, TGAColor color)
{
	mymath::BoundingBox bbox {pts[0], pts[1], pts[2]};
	const auto & [min, max] = bbox.MinMax();
	
	Vec3f P;
	for (P.x = min[0]; P.x <= max[0]; ++P.x)
	{
		for (P.y = min[1]; P.y <= max[1]; ++P.y)
		{
			Vec3f bc_screen = barycentric(pts[0], pts[1], pts[2], P);
			if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0)
			{
				continue;
			}
			
			P.z = 0;
			for (int i = 0; i < 3; i++)
			{
				P.z += pts[i][2] * bc_screen[i];
			}
			
			if (zbuffer[int(P.x + P.y * width)] < P.z)
			{
				zbuffer[int(P.x + P.y * width)] = P.z;
				image.Set(P.x, P.y, color);
			}
		}
	}
}

Vec3f world2screen(Vec3f v)
{
	return Vec3f(lround((v.x + 1.f) * width / 2.f), lround((v.y + 1.f) * height / 2.f), v.z);
}

int main(int argc, char** argv)
{
	auto model = make_unique<Model>();
	if (argc == 2)
	{
		model->Load(argv[1]);
	}
	else
	{
		model->Load("obj/african_head/african_head.obj");
	}

	auto zbuffer = vector<float>(width * height, std::numeric_limits<float>::min());

	TgaImage image(width, height, TgaImage::RGB);
	for (auto & face : model->Faces())
	{
		Vec3f pts[3];
		for (int i = 0; i < 3; i++)
		{
			pts[i] = world2screen(model->Vert(face[i]));
		}

		auto color = TGAColor(rand() % 255, rand() % 255, rand() % 255, 255);
		triangle(pts, zbuffer, image, color);
	}

	image.FlipVertically(); // i want to have the origin at the left bottom corner of the image
	if (!image.WriteTgaFile("output.tga"))
	{
		return -1;
	}
	return 0;
}