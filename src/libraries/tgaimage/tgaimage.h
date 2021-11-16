#pragma once

#pragma pack(push,1)
struct TGA_Header
{
	char idlength;
	char colormaptype;
	char datatypecode;
	short colormaporigin;
	short colormaplength;
	char colormapdepth;
	short x_origin;
	short y_origin;
	short width;
	short height;
	char bitsperpixel;
	char imagedescriptor;
};
#pragma pack(pop)

struct TGAColor
{
	array<unsigned char, 4> bgra{};
	unsigned char bytespp;

	TGAColor()
		: bytespp(1)
	{
	}

	TGAColor(unsigned char R, unsigned char G, unsigned char B, unsigned char A = 255)
		: bytespp(4)
	{
		bgra[0] = B;
		bgra[1] = G;
		bgra[2] = R;
		bgra[3] = A;
	}

	TGAColor(unsigned char v)
		: bytespp(1)
	{
		bgra[0] = v;
	}


	TGAColor(const unsigned char* p, unsigned char bpp)
		: bytespp(bpp)
	{
		for (int i = 0; i < static_cast<int>(bpp); i++)
		{
			bgra[i] = p[i];
		}
		for (int i = bpp; i < 4; i++)
		{
			bgra[i] = 0;
		}
	}

	unsigned char& operator[](const int i) { return bgra[i]; }

	TGAColor operator *(float intensity) const
	{
		TGAColor res = *this;
		intensity = (intensity > 1.f ? 1.f : (intensity < 0.f ? 0.f : intensity));
		for (int i = 0; i < 4; i++)
		{
			res.bgra[i] = static_cast<unsigned char>(static_cast<float>(bgra[i]) * intensity);
		}
		return res;
	}
};

class TgaImage
{
public:
	enum Format
	{
		GRAYSCALE=1,
		RGB=3,
		RGBA=4
	};

	TgaImage() = default;
	TgaImage(int w, int h, int bpp);
	
	bool ReadTgaFile(const char* filename);
	bool WriteTgaFile(const char* filename, bool rle = true) const;
	
	void FlipHorizontally();
	void FlipVertically();
	
	bool Scale(int w, int h);
	void Clear();
	
	void Set(int x, int y, const TGAColor & c);
	
	[[nodiscard]] TGAColor get(int x, int y) const;
	[[nodiscard]] auto Width() const { return _width; }
	[[nodiscard]] auto Height() const{ return _height; }
	[[nodiscard]] auto BytesPerPoint() const { return _bytespp; }
	[[nodiscard]] auto Buffer() const { return _bytes.data(); }
	[[nodiscard]] auto Buffer()  { return _bytes.data(); }
	
private:
	bool load_rle_data(ifstream & in);
	bool unload_rle_data(ofstream & out) const;
	
	vector<unsigned char> _bytes;
	int _width = 0;
	int _height = 0;
	int _bytespp = 0;

};
