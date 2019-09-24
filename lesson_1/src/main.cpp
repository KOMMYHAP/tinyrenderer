#include "tgaimage.h"
#include <iostream>

int main(int argc, char ** argv)
{
	using std::string;

	bool needHelp = true;
	string imageFilename;

	if (argc == 3)
	{
		string _argv {argv[1]};
		if (_argv == "--input" || _argv == "-i")
		{
			imageFilename = argv[2];
			needHelp = false;
		}
	}

	if (needHelp)
	{
		std::cout << "Lesson #1\n"
			<< "--help | -h						prints this help message.\n"
			<< "--input | -i					specifies filename for .tga image." << std::endl;
		return 1;	
	}

	TGA::Image image;
	if (!image.read_tga_file(imageFilename.c_str()))
	{
		return 1;	
	}

	return 0;
}
