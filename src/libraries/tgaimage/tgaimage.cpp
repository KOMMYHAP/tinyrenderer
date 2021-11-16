#include "tgaimage.h"

#include <fstream>
#include <iostream>

TgaImage::TgaImage(int w, int h, int bpp)
	: _width(w)
	, _height(h)
	, _bytespp(bpp)
{
	_bytes.resize(_width * _height * _bytespp);
}

bool TgaImage::ReadTgaFile(const char* filename)
{
	std::ifstream in;
	in.open(filename, std::ios::binary);
	if (!in.is_open())
	{
		std::cerr << "can't open file " << filename << "\n";
		in.close();
		return false;
	}
	TGA_Header header{};
	in.read(reinterpret_cast<char*>(&header), sizeof(header));
	if (!in.good())
	{
		in.close();
		std::cerr << "an error occured while reading the header\n";
		return false;
	}
	auto w = header.width;
	auto h = header.height;
	auto bytespp = header.bitsperpixel >> 3;
	if (w <= 0 || h <= 0 || (bytespp != GRAYSCALE && bytespp != RGB && bytespp != RGBA))
	{
		in.close();
		std::cerr << "bad bpp (or width/height) value\n";
		return false;
	}

	auto nbytes = w * h * bytespp;
	auto image = TgaImage(w, h, bytespp);
	
	if (3 == header.datatypecode || 2 == header.datatypecode)
	{
		in.read(reinterpret_cast<char*>(image._bytes.data()), nbytes);
		if (!in.good())
		{
			in.close();
			std::cerr << "an error occured while reading the data\n";
			return false;
		}
	}
	else if (10 == header.datatypecode || 11 == header.datatypecode)
	{
		if (!image.load_rle_data(in))
		{
			in.close();
			std::cerr << "an error occured while reading the data\n";
			return false;
		}
	}
	else
	{
		in.close();
		std::cerr << "unknown file format " << static_cast<int>(header.datatypecode) << "\n";
		return false;
	}
	if (!(header.imagedescriptor & 0x20))
	{
		FlipVertically();
	}
	if (header.imagedescriptor & 0x10)
	{
		FlipHorizontally();
	}
	std::cerr << w << "x" << h << "/" << bytespp * 8 << "\n";
	in.close();
	std::swap(*this, image);
	return true;
}

bool TgaImage::load_rle_data(std::ifstream& in)
{
	unsigned long pixelcount = _width * _height;
	unsigned long currentpixel = 0;
	unsigned long currentbyte = 0;
	TGAColor colorbuffer;
	do
	{
		unsigned char chunkheader = in.get();
		if (!in.good())
		{
			std::cerr << "an error occured while reading the data\n";
			return false;
		}
		if (chunkheader < 128)
		{
			chunkheader++;
			for (int i = 0; i < chunkheader; i++)
			{
				in.read(reinterpret_cast<char*>(colorbuffer.bgra.data()), _bytespp);
				if (!in.good())
				{
					std::cerr << "an error occured while reading the header\n";
					return false;
				}
				for (int t = 0; t < _bytespp; t++)
					_bytes[currentbyte++] = colorbuffer.bgra[t];
				currentpixel++;
				if (currentpixel > pixelcount)
				{
					std::cerr << "Too many pixels read\n";
					return false;
				}
			}
		}
		else
		{
			chunkheader -= 127;
			in.read(reinterpret_cast<char*>(colorbuffer.bgra.data()), _bytespp);
			if (!in.good())
			{
				std::cerr << "an error occured while reading the header\n";
				return false;
			}
			for (int i = 0; i < chunkheader; i++)
			{
				for (int t = 0; t < _bytespp; t++)
					_bytes[currentbyte++] = colorbuffer.bgra[t];
				currentpixel++;
				if (currentpixel > pixelcount)
				{
					std::cerr << "Too many pixels read\n";
					return false;
				}
			}
		}
	}
	while (currentpixel < pixelcount);
	return true;
}

bool TgaImage::WriteTgaFile(const char* filename, bool rle) const
{
	unsigned char developer_area_ref[4] = {0, 0, 0, 0};
	unsigned char extension_area_ref[4] = {0, 0, 0, 0};
	std::string_view footer = "TRUEVISION-XFILE.";

	std::ofstream out;
	out.open(filename, std::ios::binary);
	if (!out.is_open())
	{
		std::cerr << "can't open file " << filename << "\n";
		out.close();
		return false;
	}
	TGA_Header header{};
	memset(static_cast<void*>(&header), 0, sizeof(header));
	header.bitsperpixel = static_cast<char>(_bytespp << 3);
	header.width = static_cast<short>(_width);
	header.height = static_cast<short>(_height);
	header.datatypecode = static_cast<char>(_bytespp == GRAYSCALE ? (rle ? 11 : 3) : (rle ? 10 : 2));
	header.imagedescriptor = 0x20; // top-left origin
	out.write(reinterpret_cast<const char*>(&header), sizeof(header));
	if (!out.good())
	{
		out.close();
		std::cerr << "can't dump the tga file\n";
		return false;
	}
	if (!rle)
	{
		out.write(reinterpret_cast<const char*>(_bytes.data()), std::streamsize(_width) * _height * _bytespp);
		if (!out.good())
		{
			std::cerr << "can't unload raw data\n";
			out.close();
			return false;
		}
	}
	else
	{
		if (!unload_rle_data(out))
		{
			out.close();
			std::cerr << "can't unload rle data\n";
			return false;
		}
	}
	out.write(reinterpret_cast<const char*>(developer_area_ref), sizeof(developer_area_ref));
	if (!out.good())
	{
		std::cerr << "can't dump the tga file\n";
		out.close();
		return false;
	}
	out.write(reinterpret_cast<const char*>(extension_area_ref), sizeof(extension_area_ref));
	if (!out.good())
	{
		std::cerr << "can't dump the tga file\n";
		out.close();
		return false;
	}
	out.write(footer.data(), footer.size());
	if (!out.good())
	{
		std::cerr << "can't dump the tga file\n";
		out.close();
		return false;
	}
	out.close();
	return true;
}

// TODO: it is not necessary to break a raw chunk for two equal pixels (for the matter of the resulting size)
bool TgaImage::unload_rle_data(std::ofstream& out) const
{
	const unsigned char max_chunk_length = 128;
	unsigned long npixels = _width * _height;
	unsigned long curpix = 0;

	auto data = _bytes.data();
	while (curpix < npixels)
	{
		unsigned long chunkstart = curpix * _bytespp;
		unsigned long curbyte = curpix * _bytespp;
		unsigned char run_length = 1;
		bool raw = true;
		while (curpix + run_length < npixels && run_length < max_chunk_length)
		{
			bool succ_eq = true;
			for (int t = 0; succ_eq && t < _bytespp; t++)
			{
				succ_eq = data[curbyte + t] == data[curbyte + t + _bytespp];
			}
			curbyte += _bytespp;
			if (1 == run_length)
			{
				raw = !succ_eq;
			}
			if (raw && succ_eq)
			{
				run_length--;
				break;
			}
			if (!raw && !succ_eq)
			{
				break;
			}
			run_length++;
		}
		curpix += run_length;
		out.put(raw ? run_length - 1 : run_length + 127);
		if (!out.good())
		{
			std::cerr << "can't dump the tga file\n";
			return false;
		}
		out.write(reinterpret_cast<const char*>(data + chunkstart), (raw ? run_length * _bytespp : _bytespp));
		if (!out.good())
		{
			std::cerr << "can't dump the tga file\n";
			return false;
		}
	}
	return true;
}

TGAColor TgaImage::get(int x, int y) const
{
	if (x >= 0 && y >= 0 && x < _width && y < _height)
	{
		return TGAColor(_bytes.data() + (x + y * _width) * _bytespp, _bytespp);
	}
	return TGAColor();
}

void TgaImage::Set(int x, int y, const TGAColor& c)
{
	if ( x >= 0 && y >= 0 && x < _width && y < _height)
	{
		memcpy(static_cast<void *>(_bytes.data() + (x + y * _width) * _bytespp), static_cast<void const*>(c.bgra.data()), _bytespp);
	}
}

void TgaImage::FlipHorizontally()
{
	int half = _width >> 1;
	for (int i = 0; i < half; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			TGAColor c1 = get(i, j);
			TGAColor c2 = get(_width - 1 - i, j);
			Set(i, j, c2);
			Set(_width - 1 - i, j, c1);
		}
	};
}

void TgaImage::FlipVertically()
{
	unsigned long bytes_per_line = _width * _bytespp;
	auto* line = new unsigned char[bytes_per_line];
	int half = _height >> 1;
	for (int j = 0; j < half; j++)
	{
		unsigned long l1 = j * bytes_per_line;
		unsigned long l2 = (_height - 1 - j) * bytes_per_line;
		memmove(static_cast<void*>(line), static_cast<void*>(_bytes.data() + l1), bytes_per_line);
		memmove(static_cast<void*>(_bytes.data() + l1), static_cast<void*>(_bytes.data() + l2), bytes_per_line);
		memmove(static_cast<void*>(_bytes.data() + l2), static_cast<void*>(line), bytes_per_line);
	}
	delete [] line;
}

void TgaImage::Clear()
{
	memset(Buffer(), 0, _width * _height * _bytespp);
}

bool TgaImage::Scale(int w, int h)
{
	if (w <= 0 || h <= 0)
	{
		return false;
	}
	TgaImage image(w, h, _bytespp);
	int nscanline = 0;
	int oscanline = 0;
	int erry = 0;
	int nlinebytes = w * _bytespp;
	int olinebytes = _width * _bytespp;
	
	for (int j = 0; j < _height; j++)
	{
		int errx = _width - w;
		int nx = -_bytespp;
		int ox = -_bytespp;
		for (int i = 0; i < _width; i++)
		{
			ox += _bytespp;
			errx += w;
			while (errx >= static_cast<int>(_width))
			{
				errx -= _width;
				nx += _bytespp;
				memcpy(image.Buffer() + nscanline + nx, Buffer() + oscanline + ox, _bytespp);
			}
		}
		erry += h;
		oscanline += olinebytes;
		while (erry >= static_cast<int>(_height))
		{
			if (erry >= static_cast<int>(_height) << 1) // it means we jump over a scanline
				memcpy(image.Buffer() + nscanline + nlinebytes, image.Buffer() + nscanline, nlinebytes);
			erry -= _height;
			nscanline += nlinebytes;
		}
	}
	
	std::swap(*this, image);
	return true;
}
