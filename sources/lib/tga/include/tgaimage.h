#pragma once

namespace TGA
{
	struct Color {
		union {
			struct {
				unsigned char b, g, r, a;
			};
			unsigned char raw[4];
			unsigned int val;
		};
		int bytespp;

		constexpr Color() noexcept
			: val(0), bytespp(1) 
		{}
		
		template <typename U>
		constexpr Color(U r, U g, U b, U a) noexcept
			: b(static_cast<unsigned char>(b))
			, g(static_cast<unsigned char>(g))
			, r(static_cast<unsigned char>(r))
			, a(static_cast<unsigned char>(a))
			, bytespp(4) 
		{}

		template <typename U>
		constexpr Color(U r, U g, U b) noexcept
			: b(static_cast<unsigned char>(b))
			, g(static_cast<unsigned char>(g))
			, r(static_cast<unsigned char>(r))
			, bytespp(3) 
		{}

		constexpr Color(int v, int bpp) noexcept
			: val(v), bytespp(bpp) 
		{}
		
		template <typename U, size_t Dim, std::enable_if_t<Dim <= 4> * = nullptr>
		constexpr Color(const U (&data) [Dim]) noexcept
			: val(0), bytespp(Dim) 
		{
			for (int i = 0; i < Dim; ++i) 
			{
				raw[i] = static_cast<unsigned char>(data[i]);
				
			}
		}
		
		constexpr Color(const unsigned char *p, int bpp) noexcept
			: val(0), bytespp(bpp) 
		{
			for (int i = 0; i < bpp; ++i) 
			{
				raw[i] = p[i];
			}
		}
	};

	static constexpr Color white {255, 255, 255, 255};
	static constexpr Color black {0, 0, 0, 255};
	static constexpr Color red {255, 0, 0, 255};
	static constexpr Color green {0, 255, 0, 255};
	static constexpr Color blue {0, 0, 255, 255};

	class Image 
	{
	public:
		enum Format {
			GRAYSCALE=1, RGB=3, RGBA=4
		};

		Image();
		Image(int w, int h, int bpp = RGB, Color = black);
		Image(const Image &img);
		Image & operator =(const Image &img);
		Image(Image && img) noexcept;
		Image & operator =(Image && img) noexcept;
		~Image();

		void swap(Image & other) noexcept;

		bool read_tga_file(const char *filename);
		bool write_tga_file(const char *filename, bool rle = true) const;

		bool flip_horizontally();
		bool flip_vertically();
		bool scale(int w, int h);
		bool set(int x, int y, Color c);
		void clear();
		unsigned char *buffer() { return data; }
		
		Color get(int x, int y) const;
		int get_width() const;
		int get_height() const;
		int get_bytespp() const;
		const unsigned char *buffer() const { return data; }
		
	private:
		unsigned char* data;
		int width;
		int height;
		int bytespp;
	};
}