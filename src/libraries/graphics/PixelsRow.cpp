#include "PixelsRow.h"
#include <Utils.h>

namespace Graphics
{
	const Color& PixelsRow::Get(uint32_t x) const
	{
		if (x < _pixels.size())
		{
			return _pixels[x];
		}
		Utils::OutOfRange("Cannot get pixel by specified index " + std::to_string(x) + "!");
	}

	Color & PixelsRow::Get(uint32_t x)
	{
		if (x < _pixels.size())
		{
			return _pixels[x];
		}
		Utils::OutOfRange("Cannot get pixel by specified index " + std::to_string(x) + "!");
	}
}
