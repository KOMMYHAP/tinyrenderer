#include "Canvas.h"
#include "model.h"
#include "tgaimage.h"

int main(int argc, char** argv)
{
	string_view objectFile;
	string_view diffuseTextureFile;
	if (argc == 3)
	{
		objectFile = argv[1];
		diffuseTextureFile = argv[2];
	}
	else
	{
		objectFile = "../resources/african_head/african_head.obj";
		diffuseTextureFile = "../resources/african_head/african_head_diffuse.tga";
	}

	auto model = make_unique<Graphics::Model>();
	if (!model->Load(objectFile))
	{
		std::cerr << "Cannot load model!" << std::endl;
		return 1;
	}

	auto diffuseImage = make_unique<TgaImage>();
	if (!diffuseImage->ReadTgaFile(diffuseTextureFile.data()))
	{
		std::cerr << "Cannot load diffuse texture!" << std::endl;
		return 2;
	}

	auto diffuseTexture = Graphics::Texture::From(*diffuseImage);

	auto canvas = Graphics::Canvas(800, 600);
	try
	{
		canvas.Render(*model, diffuseTexture, Math::Vec3f(0, 0, 1));
	}
	catch (const std::out_of_range & e)
	{
		std::cerr << "Specified model is corrupted! Details: " << e.what() << std::endl;
	}

	if (!canvas.WriteToTga("output.tga"))
	{
		return 3;
	}

	return 0;
}
