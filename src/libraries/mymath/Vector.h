#pragma once

#include <assert.h>
#include <array>

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
	struct Vec2
	{
		Vec2() noexcept = default;
		
		Vec2(const T & x, const T & y) noexcept
			: x(x), y(y)
		{}
		Vec2(const T * raw) noexcept
			: Vec2(raw[0], raw[1])
		{}
		
		Vec2(const std::array<T, 2> raw) noexcept
			: Vec2(raw.data())
		{}

		T	operator[](int i) const noexcept { assert(i < 2); return raw[i]; }
		T &	operator[](int i)		noexcept { assert(i < 2); return raw[i]; }
		
		bool operator==(const Vec2 & other) const { return equal(x, other.x) && equal(y, other.y); }
		bool operator!=(const Vec2 & other) const { return !(*this == other); }

		union
		{
			struct
			{
				T x, y;
			};
			T raw[2] = {};
		};
	};

	using Vec2f = Vec2<float>;
	using Vec2d = Vec2<double>;
	using Vec2i = Vec2<int32_t>;
	using Vec2l = Vec2<int64_t>;
	
	template <class T>
	struct Vec3
	{
		Vec3() noexcept = default;
		
		Vec3(const T & x, const T & y, const T & z) noexcept
			: x(x), y(y), z(z)
		{}

		Vec3(const T * raw) noexcept
			: Vec3(raw[0], raw[1], raw[2])
		{}
		
		Vec3(const std::array<T, 3> raw) noexcept
			: Vec3(raw.data())
		{}

		T	operator[](int i) const noexcept { assert(i < 3); return raw[i]; }
		T &	operator[](int i)		noexcept { assert(i < 3); return raw[i]; }

		bool operator==(const Vec3 & other) const { return equal(x, other.x) && equal(y, other.y) && equal(z, other.z); }
		bool operator!=(const Vec3 & other) const { return !(*this == other); }
		
		union
		{
			struct
			{
				T x, y, z;
			};
			T raw[3] = {};
		};
	};

	using Vec3f = Vec3<float>;
	using Vec3d = Vec3<double>;
	using Vec3i = Vec3<int32_t>;
	using Vec3l = Vec3<int64_t>;
}
