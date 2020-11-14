#pragma once

namespace Math
{
	template <class T>
	struct Vec3
	{
		Vec3() noexcept = default;

		template <class U>
		explicit Vec3(const Vec3<U> & other)
			: Vec3(
				static_cast<T>(other.x),
				static_cast<T>(other.y),
				static_cast<T>(other.z)
			)
		{}
		
		Vec3(const T & x, const T & y, const T & z) noexcept
			: x(x), y(y), z(z)
		{}

		Vec3(const T (&raw)[3]) noexcept
			: Vec3(raw[0], raw[1], raw[2])
		{}

		Vec3(const std::array<T, 3> & raw) noexcept
			: Vec3(raw[0], raw[1], raw[2])
		{}

		Vec3 & normalize()
		{
			float n = std::sqrt(x * x + y * y + z * z);
			x /= n;
			y /= n;
			z /= n;
			return *this;
		}
		
		T	operator[](int i) const noexcept { WUSIKO_ASSERT(i < 3); return *((&x) + i); }
		T &	operator[](int i)		noexcept { WUSIKO_ASSERT(i < 3); return *((&x) + i); }
		
		bool operator==(const Vec3 & other) const { return x == other.x && y == other.y && z == other.z; }
		bool operator!=(const Vec3 & other) const { return !(*this == other); }

		T x, y, z;
	};

	template <class T>
	Vec3<T> operator+(const Vec3<T> & a, const Vec3<T> &b)
	{
		return {a.x + b.x, a.y + b.y, a.z + b.z};
	}

	template <class T>
	Vec3<T> operator-(const Vec3<T> & a, const Vec3<T> &b)
	{
		return {a.x - b.x, a.y - b.y, a.z - b.z};
	}

	template <class T>
	T ScalarProduct(const Vec3<T> & a, const Vec3<T> & b)
	{
		return {a.x * b.x + a.y * b.y + a.z * b.z};
	}

	template <class T>
	Vec3<T> CrossProduct(const Vec3<T> & a, const Vec3<T> & b)
	{
		return {
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		};
	}

	using Vec3f = Vec3<float>;
	using Vec3d = Vec3<double>;
	using Vec3i = Vec3<int32_t>;
	using Vec3u = Vec3<uint32_t>;
	using Vec3l = Vec3<int64_t>;
	using Vec3ul = Vec3<uint64_t>;
}
