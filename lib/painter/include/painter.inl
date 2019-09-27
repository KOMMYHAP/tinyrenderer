#pragma once

inline Painter::Painter(TGA::Image & canvas)
	: m_image(canvas)
{
	
}

inline void Painter::SetColor(TGA::Color color)
{
	m_color = color;
}

inline void Painter::DoLine(geometry::Vec2i p0, geometry::Vec2i p1)
{
	DoLine(p0[0], p0[1], p1[0], p1[1]);
}

inline void Painter::DoTriangle(geometry::Vec2i p0, geometry::Vec2i p1, geometry::Vec2i p2)
{
	DoTriangle({p0, p1, p2});
}

inline void Painter::DoTriangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	DoTriangle({x0, y0}, {x1, y1}, {x2, y2});
}