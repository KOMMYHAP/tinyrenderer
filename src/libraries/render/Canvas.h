#pragma once

#include <functional>

#include "Color.h"
#include "geometry.h"
#include "Texture.h"

namespace Graphics
{
	class Model;

	class Canvas
	{
	public:
		Canvas();
		Canvas(uint32_t sizeX, uint32_t sizeY);

		void Line(const vec3 & p1, const vec3 & p2, const Color & color);
		void Triangle(const vec3 & p1, const vec3 & p2, const vec3 & p3, const Color & color);

		struct ColorContext
		{
			vec2		t;
		};
		using ColorFunction = std::function<Color(const ColorContext &)>;
		void Triangle(const vec3 & p1, const vec3 & p2, const vec3 & p3, ColorFunction colorFunction);
		void Render(const Model & model, const Texture & diffuseTexture, const vec3 & light);

		bool WriteToTga(string_view filename) const;

		uint32_t Width() const { return _texture.Width(); }
		uint32_t Height() const { return _texture.Height(); }

	private:
		void CheckPointIsInside(const vec3& p);
		void TrySet(const vec3 & point, const Color & color);
		Color GetDiffuseColor(const Texture & diffuseTexture, float u, float v);

		Texture				_texture;
		vector<float>		_zBuffer;
	};
}
