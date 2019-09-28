#pragma once

namespace geometry
{
	template <class Type, size_t Dim> struct Vec
	{
		static_assert(Dim >= 1 && "Dimension of vector must be more or equal 1!");

		Type		m_data[Dim];

		constexpr size_t size() const noexcept { return Dim; }

		constexpr Type operator[](size_t index) const noexcept { return m_data[index]; }
		Type &	operator[](size_t index) { return m_data[index]; }

		constexpr Vec<Type, Dim> & operator+=(const Vec<Type, Dim> & other);
		constexpr auto operator+ (const Vec<Type, Dim> & other) const noexcept;

		constexpr Vec<Type, Dim> & operator-=(const Vec<Type, Dim> & other);
		constexpr auto operator- (const Vec<Type, Dim> & other) const noexcept;
		
		constexpr Vec<Type, Dim> & operator*=(Type value);
		constexpr auto operator* (Type value) const noexcept;
	};
	
	using Vec2f = Vec<float, 2>;
	using Vec2i = Vec<int, 2>;

	using Vec3f = Vec<float, 3>;
	using Vec3i = Vec<int, 3>;

	template <typename Type, size_t Dim>
	constexpr Vec<Type, Dim - 1> NarrowDim(const Vec<Type, Dim> & v);

	template <typename Type>
	constexpr Vec3f ConvertToBarycentric(Vec<Type, 2> p0, Vec<Type, 2> p1, Vec<Type, 2> p2, Vec<Type, 2> p);
	
	template <typename Type>
	constexpr Vec3f CrossProduct(const Vec<Type, 3> & v1, const Vec<Type, 3> & v2);
	
	template <typename Type, size_t Dim>
	constexpr float ScalarProduct(const Vec<Type, Dim> & v1, const Vec<Type, Dim> & v2);

	template <typename Type, size_t Dim>
	constexpr Vec<float, Dim> Normalize(const Vec<Type, Dim> & v);

	template <typename Type, size_t Dim>
	constexpr Type LengthSqr(const Vec<Type, Dim>& v);

	template <typename Type, size_t Dim>
	constexpr Type Length(const Vec<Type, Dim>& v);
} // namespace geometry

#include "geometry.inl"