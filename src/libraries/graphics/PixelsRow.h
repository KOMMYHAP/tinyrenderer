#pragma once

#include "Color.h"

namespace Graphics
{
	class PixelsRow
	{
	public:
		PixelsRow() = default;
		PixelsRow(uint32_t size)
			: _pixels(size)
		{}

		const Color & Get(uint32_t x) const;
		Color & Get(uint32_t x);

		const Color & operator[](uint32_t x) const { assert(x < _pixels.size()); return _pixels[x]; }
		Color & operator[](uint32_t x) { assert(x < _pixels.size()); return _pixels[x]; }

		uint32_t Length() const { return _pixels.size(); }

	private:
		vector<Color>	_pixels;
	};
}
