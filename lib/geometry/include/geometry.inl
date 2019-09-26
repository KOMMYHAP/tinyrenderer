#pragma once

namespace geometry
{
	template <class Type, size_t Dim>
	constexpr Vec<Type, Dim> & Vec<Type, Dim>::operator+=(const Vec & other)
	{
		for (size_t i = 0; i < Dim; ++i)
		{
			data[i] += other.data[i];
		}
		return *this;
	}

	template <class Type, size_t Dim>
	constexpr auto Vec<Type, Dim>::operator+ (const Vec & other) const
	{
		auto res = *this;
		res += other;
		return res;
	}

	template <class Type, size_t Dim>
	constexpr Vec<Type, Dim> & Vec<Type, Dim>::operator-=(const Vec & other)
	{
		for (size_t i = 0; i < Dim; ++i)
		{
			data[i] -= other.data[i];
		}
		return *this;
	}

	template <class Type, size_t Dim>
	constexpr auto Vec<Type, Dim>::operator- (const Vec & other) const
	{
		auto res = *this;
		res -= other;
		return res;
	}
	
	template <class Type, size_t Dim>
	constexpr Vec<Type, Dim> & Vec<Type, Dim>::operator*=(const Vec & other)
	{
		for (size_t i = 0; i < Dim; ++i)
		{
			data[i] *= other.data[i];
		}
		return *this;
	}

	template <class Type, size_t Dim>
	constexpr auto Vec<Type, Dim>::operator* (const Vec & other) const
	{
		auto res = *this;
		res *= other;
		return res;
	}
	
	template <class Type, size_t Dim>
	constexpr Vec<Type, Dim> & Vec<Type, Dim>::operator/=(Type divisor)
	{
		for (size_t i = 0; i < Dim; ++i)
		{
			data[i] /= divisor;
		}
		return *this;
	}

	template <class Type, size_t Dim>
	constexpr auto Vec<Type, Dim>::operator/ (Type divisor) const
	{
		auto res = *this;
		res /= divisor;
		return res;
	}

	template <typename Type>
	constexpr Vec3f CrossProduct(const Vec<Type, 3> & v1, const Vec<Type, 3> & v2)
	{
		return Vec3f {
			 v1[1] * v2[2] - v1[2] * v2[1],
			-v1[0] * v2[2] + v1[2] * v2[0],
			 v1[0] * v2[1] - v1[1] * v2[0]
		};
	}

	template <typename Type>
	constexpr Vec3f ConvertToBarycentric(Vec<Type, 2> p0, Vec<Type, 2> p1, Vec<Type, 2> p2, Vec<Type, 2> p)
	{
		auto ab = p1 - p0;
		auto ac = p2 - p0;
		auto pa = p0 - p;

		auto v1 = Vec3f {ab[0], ac[0], pa[0]};
		auto v2 = Vec3f {ab[1], ac[1], pa[1]};

		auto u = CrossProduct(v1, v2);

		if (std::abs(u[2]) < 1.0f)
		{
			return Vec3f {1.0f, 1.0f, -1.0f};
		}
		
		u[0] /= u[2];
		u[1] /= u[2];
		u[2]  = 1.0f;

		return Vec3f {1.0f - (u[0] + u[1]), u[0], u[1]};
	};

} // namespace geometry