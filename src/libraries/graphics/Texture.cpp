#include "Texture.h"

#include <Utils.h>

namespace Graphics
{
	void Texture::Set(uint32_t x, uint32_t y, Color color)
	{
		Get(x, y) = color;
	}

	const Color& Texture::Get(uint32_t x, uint32_t y) const
	{
		if (y < _rows.size())
		{
			return _rows[y].Get(x);
		}
		Utils::OutOfRange("Cannot get pixel by specified index " + std::to_string(x) + " " + std::to_string(y) + "!");
	}

	Color& Texture::Get(uint32_t x, uint32_t y)
	{
		if (y < _rows.size())
		{
			return _rows[y].Get(x);
		}
		Utils::OutOfRange("Cannot get pixel by specified index " + std::to_string(x) + " " + std::to_string(y) + "!");
	}
}
