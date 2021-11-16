#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "BoundingBox.h"

namespace Math
{
	template <class T,
		std::enable_if_t<std::is_integral_v<T>, int> = 0>
	bool equal(const T & left, const T & right)
	{
		return left == right;
	}

	template <class T,
		std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
	bool equal(const T & left, const T & right)
	{
		if (left == right)
		{
			return true;
		}
		auto diff = std::abs(left - right);
		auto norm = std::min(std::abs(left) + std::abs(right), std::numeric_limits<T>::max());
		constexpr auto epsilon = 128 * std::numeric_limits<T>::epsilon();
		constexpr auto relth = std::numeric_limits<T>::min();
		return diff < std::max(relth, epsilon * norm);
	}

	template <class T>
	Vec3<T> vec_upcast(const Vec2<T> & vec)
	{
		return Vec3<T>(vec.x, vec.y, T{});
	}

	template <class T>
	Vec2<T> vec_downcast(const Vec3<T> & vec)
	{
		return Vec2<T>(vec.x, vec.y);
	}

	inline Vec3f barycentric(const Vec3f & A, const Vec3f & B, const Vec3f & C, const Vec3f & P)
	{
		Vec3f s[2];
		for (int i = 0; i < 2; ++i)
		{
			s[i].x = C[i] - A[i]; // x
			s[i].y = B[i] - A[i]; // y
			s[i].z = A[i] - P[i]; // z
		}

		Vec3f u = CrossProduct(s[0], s[1]);
		if (std::abs(u.z) > 1e-2)
		{
			return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
		}
		return Vec3f(-1, -1, -1);
	}
	
	template <class T>
	T lerp(const T & a, const T & b, float t)
	{
		return static_cast<float>(a) + (b - a) * t;
	}
}
