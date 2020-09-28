#pragma once

#include "Color.h"
#include "Texture.h"
#include "Vec2.h"
#include "Vec3.h"

namespace Graphics
{
	class Model;

	class Canvas
	{
	public:
		Canvas() = default;
		Canvas(uint32_t sizeX, uint32_t sizeY)
			: _texture(sizeX, sizeY)
			, _zBuffer(sizeX * sizeY, -std::numeric_limits<float>::infinity())
		{}
		Canvas(const Math::Vec2<uint32_t> & size)
			: Canvas(size.x, size.y)
		{}

		void Line(const Math::Vec3f & p1, const Math::Vec3f & p2, const Color & color);
		void Triangle(const Math::Vec3f & p1, const Math::Vec3f & p2, const Math::Vec3f & p3, const Color & color);
		void Model(unique_ptr<Graphics::Model> model);

		bool WriteToTga(string_view filename) const;

		uint32_t Width() const { return _texture.Width(); }
		uint32_t Height() const { return _texture.Height(); }

	private:
		void CheckPointIsInside(const Math::Vec3<uint32_t>& p);
		void TrySet(const Math::Vec3f & point, const Color & color);

		Texture				_texture;
		vector<float>		_zBuffer;
	};
}
