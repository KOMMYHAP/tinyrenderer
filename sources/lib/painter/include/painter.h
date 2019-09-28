#pragma once

#include "geometry.h"
#include "tgaimage.h"

class Painter
{
public:
	explicit Painter(TGA::Image & canvas);

	inline void SetColor(TGA::Color color);

	void DoLine(int x0, int y0, int x1, int y1);
	inline void DoLine(geometry::Vec2i p0, geometry::Vec2i p1);
	
	void DoTriangle(array<geometry::Vec3i, 3> points_xyz);
	inline void DoTriangle(geometry::Vec3i p0, geometry::Vec3i p1, geometry::Vec3i p2);

private:
	TGA::Image &				m_image;
	TGA::Color					m_color;
	vector<float>				m_zBuffer;
};

#include "painter.inl"