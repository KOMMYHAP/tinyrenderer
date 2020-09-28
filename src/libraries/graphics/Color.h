#pragma once
#include <cassert>

namespace Graphics
{
	struct Color
	{
		Color()
			: Color(0, 0, 0, 0)
		{}

		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
			: r(r), g(g), b(b), a(a)
		{}

		uint8_t		operator[](int i) const { assert(i < 4); return data[i]; }
		uint8_t &	operator[](int i)		{ assert(i < 4); return data[i]; }

		union
		{
			struct
			{
				uint8_t r, g, b, a;
			};
			uint8_t data[4];
		};
	};

}