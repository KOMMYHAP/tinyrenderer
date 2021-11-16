#pragma once

#include "geometry.h"

namespace Utils
{
	template <class T>
	vec3 vec_upcast(const vec2 & vec)
	{
		return vec3(vec.x, vec.y, T{});
	}

	template <class T>
	vec2 vec_downcast(const vec3 & vec)
	{
		return vec2(vec.x, vec.y);
	}

	inline vec3 barycentric(const vec3 & A, const vec3 & B, const vec3 & C, const vec3 & P)
	{
		vec3 s[2];
		for (int i = 0; i < 2; ++i)
		{
			s[i].x = C[i] - A[i]; // x
			s[i].y = B[i] - A[i]; // y
			s[i].z = A[i] - P[i]; // z
		}

		vec3 u = cross(s[0], s[1]);
		if (std::abs(u.z) > 1e-2)
		{
			return vec3(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
		}
		return vec3(-1, -1, -1);
	}
	
	template <class T>
	T lerp(const T & a, const T & b, float t)
	{
		return static_cast<float>(a) + (b - a) * t;
	}
}
