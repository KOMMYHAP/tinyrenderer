#pragma once

#include <assert.h>

namespace mymath
{
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
