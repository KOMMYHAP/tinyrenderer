#include "basic_defs.h"
#include "painter.h"
#include <cassert>

Painter::Painter(TGA::Image& canvas)
	: m_image(canvas)
	, m_zBuffer(m_image.get_width() * m_image.get_height(), std::numeric_limits<float>::min())
{
}

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

void Painter::DoTriangle(array<geometry::Vec3i, 3> points_xyz)
{
	geometry::Vec2i bbox_min {m_image.get_width() - 1, m_image.get_height() - 1};
	geometry::Vec2i bbox_max {0, 0};
	
	array<geometry::Vec2i, 3> points_xy {
		geometry::NarrowDim(points_xyz[0]),
		geometry::NarrowDim(points_xyz[1]),
		geometry::NarrowDim(points_xyz[2])
	};

	for (auto && point : points_xyz)
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

			auto u = geometry::ConvertToBarycentric(points_xy[0], points_xy[1], points_xy[2], p);

			if (u[0] >= 0.0f && u[1] >= 0.0f && u[2] >= 0.0f)
			{
				float z = 0.0f;
				for (int i = 0; i < 3; ++i)
				{
					int point_z = points_xyz[i][2];
					float barycentric_coef = u[i];
					z += point_z * barycentric_coef;
				}

				auto & refZ = m_zBuffer[x + y * m_image.get_width()];
				if (refZ < z)
				{
					refZ = z;
					m_image.set(x, y, m_color);	
				}
			}
		}	
	}
}
