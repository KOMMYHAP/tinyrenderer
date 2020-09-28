#pragma once

#include "Vec2.h"
#include "PixelsRow.h"

namespace Graphics
{
	class Texture
	{
	public:
		Texture() = default;

		Texture(uint32_t sizeX, uint32_t sizeY)
			: _rows(sizeY, PixelsRow(sizeX))
		{}

		explicit Texture(Math::Vec2<uint32_t> size)
			: Texture(size.x, size.y)
		{}

		void Set(uint32_t x, uint32_t y, Color color);

		const Color& Get(uint32_t x, uint32_t y) const;

		Color& Get(uint32_t x, uint32_t y);

		const PixelsRow & operator[](uint32_t y) const { assert(y < _rows.size()); return _rows[y]; }
		PixelsRow & operator[](uint32_t y) { assert(y < _rows.size()); return _rows[y]; }

		uint32_t Width() const { return !_rows.empty() ? _rows[0].Length() : 0; }
		uint32_t Height() const { return _rows.size(); }

	private:
		vector<PixelsRow>		_rows;
	};
}