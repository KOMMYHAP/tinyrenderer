#pragma once

namespace geometry
{
	template <class Type, size_t Dim> struct Vec
	{
		Type data[Dim];

		constexpr Type operator[](size_t index) const { return data[index]; }
		Type &	operator[](size_t index) { return data[index]; }

		constexpr Vec<Type, Dim> & operator+=(const Vec<Type, Dim> & other);
		constexpr auto operator+ (const Vec<Type, Dim> & other) const;

		constexpr Vec<Type, Dim> & operator-=(const Vec<Type, Dim> & other);
		constexpr auto operator- (const Vec<Type, Dim> & other) const;
		
		constexpr Vec<Type, Dim> & operator*=(const Vec<Type, Dim> & other);
		constexpr auto operator* (const Vec<Type, Dim> & other) const;

		constexpr Vec<Type, Dim> & operator/=(Type divisor);
		constexpr auto operator/ (Type divisor) const;
	};
	
	using Vec2f = Vec<float, 2>;
	using Vec2i = Vec<int, 2>;

	using Vec3f = Vec<float, 3>;
	using Vec3i = Vec<int, 3>;

	template <typename Type>
	constexpr Vec3f ConvertToBarycentric(Vec<Type, 2> p0, Vec<Type, 2> p1, Vec<Type, 2> p2, Vec<Type, 2> p);

	template <typename Type>
	constexpr Vec3f CrossProduct(const Vec<Type, 3> & v1, const Vec<Type, 3> & v2);

} // namespace geometry

#include "geometry.inl"