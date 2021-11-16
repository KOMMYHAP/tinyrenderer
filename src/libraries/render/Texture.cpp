#include "Texture.h"


#include "geometry.h"
#include "tgaimage.h"

namespace Graphics
{
	Texture Texture::From(const TgaImage& image)
	{
		const auto w = image.Width();
		const auto h = image.Height();
		Texture texture(w, h);
		
		for (int y = 0; y < image.Height(); ++y)
		{
			for (int x = 0; x < image.Width(); ++x)
			{
				auto tgaColor = image.get(x, y);
				const auto [b, g, r, a] = tgaColor.bgra;
				texture.Set(x, y, Color(r, g, b, a));
			}
		}

		return texture;
	}

	Texture::Texture() = default;

	Texture::Texture(uint32_t sizeX, uint32_t sizeY)
		: _rows(sizeY, PixelsRow(sizeX))
	{}
	
	Texture::Texture(vec2 size)
		: Texture(size.x, size.y)
	{
	}

	void Texture::Set(uint32_t x, uint32_t y, Color color)
	{
		Get(x, y) = color;
	}

	const Color& Texture::Get(uint32_t x, uint32_t y) const
	{
		if (y < _rows.size())
		{
			return _rows[y][x];
		}
		throw std::out_of_range("Cannot get pixel by specified index " + std::to_string(x) + " " + std::to_string(y) + "!");
	}

	Color& Texture::Get(uint32_t x, uint32_t y)
	{
		if (y < _rows.size())
		{
			return _rows[y].Get(x);
		}
		throw std::out_of_range("Cannot get pixel by specified index " + std::to_string(x) + " " + std::to_string(y) + "!");
	}
}
