#include "TextureView.h"

#include "Color.h"

namespace Graphics
{
	TextureView::TextureView() = default;

	TextureView::TextureView(const std::byte* data, uint32_t w, uint32_t h, uint8_t bpp)
		: _data(data)
		, _width(w)
		, _height(h)
		, _bpp(bpp)
	{
	}

	Color TextureView::Get(uint32_t x, uint32_t y) const
	{
		WUSIKO_ASSERT(_width != 0 && _height != 0 && _bpp != 0 && _bpp <= 4);
		
		if (x < _width && y < _height && _bpp > 0 && _bpp <= 4)
		{
			const uint32_t value = static_cast<uint32_t>(_data[x + y * _width]);
			uint8_t r = 0, g = 0, b = 0, a = 0;
			switch (_bpp)
			{
			case 4:
				a = value & 0x00'00'00'FF;
			case 3:
				b = value & 0x00'00'FF'00;
			case 2:
				g = value & 0x00'FF'00'00;
			case 1:
				r = value & 0xFF'00'00'00;
			default:
				break;
			}
			return Color(r, g, b, a);
		}
		return Color();
	}
}
