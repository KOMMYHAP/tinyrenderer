#include "basic_defs.h"
#include <iostream>

#include "model.h"
#include "painter.h"

int main(int /*argc*/, char ** /*argv*/)
{
	auto model = model::LoadFromFile("../../models/african_head.obj");
	if (!model)
	{
		std::cerr << "Cannot load model from file!" << std::endl;
		return 1;
	}

	int w = 600, h = 600, z = 1000;
	TGA::Image image {w, h, 3};
	Painter painter {image};

	auto ConvertToModelPos = [w, h, z](const geometry::Vec3f & v)
	{
		return geometry::Vec3i {
			static_cast<int>((v[0] + 1.0f) * (w - 1) / 2),
			static_cast<int>((v[1] + 1.0f) * (h - 1) / 2),
			static_cast<int>((v[2] + 1.0f) * (z - 1) / 2)
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

	geometry::Vec3f light_pos {0.0f, 0.0f, -1.0f};
	
	for (auto && face : model->faces)
	{
		array<geometry::Vec3i, 3> screenVertexes;
		array<geometry::Vec3f, 3> worldVertexes;

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
			intensity = std::clamp(intensity, 0.0f, 1.0f);
			TGA::Color color {255 * intensity, 255 * intensity, 255 * intensity};
			painter.SetColor(color);

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
