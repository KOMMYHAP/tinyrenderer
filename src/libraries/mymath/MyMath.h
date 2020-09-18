#pragma once

#include <assert.h>
#include <array>
#include <limits>
#include <utility>
#include <algorithm>

#include "Vec2.h"
#include "Vec3.h"
#include "BoundingBox.h"

namespace mymath
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
	Vec3<T> cross(const Vec3<T> & left, const Vec3<T> & right)
	{
		return Vec3<T>(
			left.y * right.z - left.z * right.y, 
			left.z * right.x - left.x * right.z, 
			left.x * right.y - left.y * right.x
		);
	}
	
}
