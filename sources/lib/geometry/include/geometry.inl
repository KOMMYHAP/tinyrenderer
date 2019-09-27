#pragma once

namespace geometry
{
	template <class Type, size_t Dim>
	constexpr Vec<Type, Dim> & Vec<Type, Dim>::operator+=(const Vec & other)
	{
		for (size_t i = 0; i < Dim; ++i)
		{
			m_data[i] += other.m_data[i];
		}
		return *this;
	}

	template <class Type, size_t Dim>
	constexpr auto Vec<Type, Dim>::operator+ (const Vec & other) const noexcept
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
			m_data[i] -= other.m_data[i];
		}
		return *this;
	}

	template <class Type, size_t Dim>
	constexpr auto Vec<Type, Dim>::operator- (const Vec & other) const noexcept
	{
		auto res = *this;
		res -= other;
		return res;
	}
	
	template <class Type, size_t Dim>
	constexpr Vec<Type, Dim> & Vec<Type, Dim>::operator*=(Type value)
	{
		for (size_t i = 0; i < Dim; ++i)
		{
			m_data[i] *= value;
		}
		return *this;
	}

	template <class Type, size_t Dim>
	constexpr auto Vec<Type, Dim>::operator* (Type value) const noexcept
	{
		auto res = *this;
		res *= value;
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

	template <typename Type, size_t Dim>
	constexpr float ScalarProduct(const Vec<Type, Dim> & v1, const Vec<Type, Dim> & v2)
	{
		Type result = 0;
		for (size_t i = 0; i < Dim; ++i)
		{
			result += v1[i] * v2[i];
		}
		return result;
	}

	template <typename Type>
	constexpr Vec3f ConvertToBarycentric(Vec<Type, 2> p0, Vec<Type, 2> p1, Vec<Type, 2> p2, Vec<Type, 2> p)
	{
		auto ab = p1 - p0;
		auto ac = p2 - p0;
		auto pa = p0 - p;

		auto v1 = Vec3f {float(ab[0]), float(ac[0]), float(pa[0])};
		auto v2 = Vec3f {float(ab[1]), float(ac[1]), float(pa[1])};

		auto u = CrossProduct(v1, v2);

		if (std::abs(u[2]) < 1.0f)
		{
			return Vec3f {1.0f, 1.0f, -1.0f};
		}
		
		u[0] /= u[2];
		u[1] /= u[2];
		u[2]  = 1.0f;

		return Vec3f {1.0f - (u[0] + u[1]), u[0], u[1]};
	}

	template <typename Type, size_t Dim>
	constexpr Vec<float, Dim> Normalize(const Vec<Type, Dim> & v)
	{
		float coef = 1.0f / Length(v);
		return v * coef;
	}

	template <typename Type, size_t Dim>
	constexpr Type LengthSqr(const Vec<Type, Dim>& v)
	{
		Type res = 0;
		for (int i = 0; i < Dim; ++i)
		{
			res += v[i] * v[i];
		}
		return res;
	}

	template <typename Type, size_t Dim>
	constexpr Type Length(const Vec<Type, Dim>& v)
	{
		return std::sqrt(LengthSqr(v));
	}
} // namespace geometry