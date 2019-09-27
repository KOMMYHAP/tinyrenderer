#pragma once

#include "geometry.h"
#include "tgaimage.h"

class Painter
{
public:
	Painter(TGA::Image & canvas);

	inline void SetColor(TGA::Color color);

	void DoLine(int x0, int y0, int x1, int y1);
	inline void DoLine(geometry::Vec2i p0, geometry::Vec2i p1);
	
	void DoTriangle(std::array<geometry::Vec2i, 3> points);
	inline void DoTriangle(geometry::Vec2i p0, geometry::Vec2i p1, geometry::Vec2i p2);
	inline void DoTriangle(int x0, int y0, int x1, int y1, int x2, int y2);

private:
	TGA::Image &		m_image;
	TGA::Color			m_color;
};

#include "painter.inl"