#pragma once

class TgaImage;

namespace Graphics
{
	class Color;
	class Texture;

	class TextureView
	{
	public:
		TextureView();
		TextureView(const std::byte * data, uint32_t w, uint32_t h, uint8_t bpp);

		uint8_t Channels() const { return _bpp; }
		Color Get(uint32_t x, uint32_t y) const;

	private:
		const std::byte *	_data = nullptr;
		uint32_t			_width = 0;
		uint32_t			_height = 0;
		uint8_t				_bpp = 0;
	};
}
