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
		Canvas();
		Canvas(uint32_t sizeX, uint32_t sizeY);

		void Line(const Math::Vec3f & p1, const Math::Vec3f & p2, const Color & color);
		void Triangle(const Math::Vec3f & p1, const Math::Vec3f & p2, const Math::Vec3f & p3, const Color & color);
		void Render(const Model & model, const Math::Vec3f & light);

		bool WriteToTga(string_view filename) const;

		uint32_t Width() const { return _texture.Width(); }
		uint32_t Height() const { return _texture.Height(); }

	private:
		void CheckPointIsInside(const Math::Vec3u& p);
		void TrySet(const Math::Vec3f & point, const Color & color);

		Texture				_texture;
		vector<float>		_zBuffer;
	};
}
