#include "painter.h"

void Painter::DoLine(int x0, int y0, int x1, int y1)
{
	using std::abs;
	using std::swap;

	bool isSteep = false;
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		isSteep = true;
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}
	
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror = abs(dy) * 2;
	int error = 0;

	int y = y0;

	for (int x = x0; x <= x1; ++x)
	{
		if (isSteep)
		{
			m_image.set(y, x, m_color);
		}
		else
		{
			m_image.set(x, y, m_color);
		}

		error += derror;
		if (error > dx)
		{
			y += (y1 > y0) ? 1 : -1;
			error -= dx * 2;
		}
	}
}

void Painter::DoTriangle(std::array<geometry::Vec2i, 3> points)
{
	geometry::Vec2i bbox_min {m_image.get_width() - 1, m_image.get_height() - 1};
	geometry::Vec2i bbox_max {0, 0};

	for (auto && point : points)
	{
		for (int i = 0; i < 2; ++i)
		{
			bbox_min[i] = std::min(bbox_min[i], point[i]);
			bbox_max[i] = std::max(bbox_max[i], point[i]);
		}
	}
	
	for (int y = bbox_min[1]; y <= bbox_max[1]; ++y)
	{
		for (int x = bbox_min[0]; x <= bbox_max[0]; ++x)
		{
			geometry::Vec2i p {x, y};
			auto u = geometry::ConvertToBarycentric(points[0], points[1], points[2], p);

			if (u[0] >= 0.0f && u[1] >= 0.0f && u[2] >= 0.0f)
			{
				m_image.set(x, y, m_color);
			}
		}	
	}
}
