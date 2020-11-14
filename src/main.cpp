#include "Canvas.h"
#include "model.h"

int main(int argc, char** argv)
{
	auto model = make_unique<Graphics::Model>();
	string_view objectFile;
	if (argc == 2)
	{
		objectFile = argv[1];
	}
	else
	{
		objectFile = "../resources/african_head/african_head.obj";
	}

	if (!model->Load(objectFile))
	{
		std::cerr << "Cannot load model!" << std::endl;
		return 1;
	}

	auto canvas = Graphics::Canvas(800, 600);
	try
	{
		canvas.Render(*model, Math::Vec3f(0, 0, 1));
	}
	catch (const std::out_of_range & e)
	{
		std::cerr << "Specified model is corrupted! Details: " << e.what() << std::endl;
	}

	if (!canvas.WriteToTga("output.tga"))
	{
		return 2;
	}

	return 0;
}
