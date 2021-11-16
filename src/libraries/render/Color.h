#pragma once

namespace Graphics
{
	struct Color
	{
		Color()
			: Color(0, 0, 0, 0)
		{}

		Color(uint32_t rgba)
			: Color(
				rgba & (0xFF << 24),
				rgba & (0xFF << 16),
				rgba & (0xFF << 8),
				rgba & (0xFF << 0))
		{
		}
		
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
			: r(r), g(g), b(b), a(a)
		{}

		uint8_t		operator[](int i) const { WUSIKO_ASSERT(i < 4); return *(&r + i); }
		uint8_t &	operator[](int i)		{ WUSIKO_ASSERT(i < 4); return *(&r + i); }

		uint8_t r, g, b, a;
	};

}