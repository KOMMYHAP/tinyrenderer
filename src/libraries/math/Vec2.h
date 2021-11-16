#pragma once

namespace Math
{
	template <class T>
	struct Vec2
	{
		Vec2() noexcept = default;

		template <class U>
		Vec2(const Vec2<U> & vec)
			: Vec2<T>(
				static_cast<T>(vec.x),
				static_cast<T>(vec.y)
			)
		{}
		
		Vec2(const T & x, const T & y) noexcept
			: x(x), y(y)
		{}
		Vec2(const T * raw) noexcept
			: Vec2(raw[0], raw[1])
		{}

		Vec2(const std::array<T, 2> raw) noexcept
			: Vec2(raw.data())
		{}

		T	operator[](int i) const noexcept { WUSIKO_ASSERT(i < 2); return *(&x + i); }
		T &	operator[](int i)		noexcept { WUSIKO_ASSERT(i < 2); return *(&x + i); }

		bool operator==(const Vec2 & other) const { return x == other.x && y == other.y; }
		bool operator!=(const Vec2 & other) const { return !(*this == other); }

		T x, y;
	};

	template <class T>
	Vec2<T> operator+(const Vec2<T> & a, const Vec2<T> &b)
	{
		return {a.x + b.x, a.y + b.y};
	}

	template <class T>
	Vec2<T> operator-(const Vec2<T> & a, const Vec2<T> &b)
	{
		return {a.x - b.x, a.y - b.y};
	}

	template <class T>
	T ScalarProduct(const Vec2<T> & a, const Vec2<T> & b)
	{
		return {a.x * b.x + a.y * b.y};
	}

	using Vec2f = Vec2<float>;
	using Vec2u = Vec2<uint32_t>;
	using Vec2d = Vec2<double>;
	using Vec2i = Vec2<int32_t>;
	using Vec2l = Vec2<int64_t>;
}
