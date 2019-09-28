#pragma once

inline void Painter::SetColor(TGA::Color color)
{
	m_color = color;
}

inline void Painter::DoLine(geometry::Vec2i p0, geometry::Vec2i p1)
{
	DoLine(p0[0], p0[1], p1[0], p1[1]);
}

inline void Painter::DoTriangle(geometry::Vec3i p0, geometry::Vec3i p1, geometry::Vec3i p2)
{
	DoTriangle({p0, p1, p2});
}