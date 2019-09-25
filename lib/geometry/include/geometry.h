#pragma once
#include <cmath>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type> struct Vec2 {
	union {
		struct {Type u, v;};
		struct {Type x, y;};
		Type raw[2];
	};

	Vec2() : u(0), v(0) {}
	Vec2(Type _u, Type _v) : u(_u),v(_v) {}
	Vec2<Type> operator +(const Vec2<Type> &V) const { return Vec2<Type>(u+V.u, v+V.v); }
	Vec2<Type> operator -(const Vec2<Type> &V) const { return Vec2<Type>(u-V.u, v-V.v); }
	Vec2<Type> operator *(float f)          const { return Vec2<Type>(u*f, v*f); }
};

template <class Type> struct Vec3 {
	union {
		struct {Type x, y, z;};
		struct { Type ivert, iuv, inorm; };
		Type raw[3];
	};
	Vec3() : x(0), y(0), z(0) {}
	Vec3(Type _x, Type _y, Type _z) : x(_x),y(_y),z(_z) {}
	Vec3<Type> operator ^(const Vec3<Type> &v) const { return Vec3<Type>(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
	Vec3<Type> operator +(const Vec3<Type> &v) const { return Vec3<Type>(x+v.x, y+v.y, z+v.z); }
	Vec3<Type> operator -(const Vec3<Type> &v) const { return Vec3<Type>(x-v.x, y-v.y, z-v.z); }
	Vec3<Type> operator *(float f)          const { return Vec3<Type>(x*f, y*f, z*f); }
	Type       operator *(const Vec3<Type> &v) const { return x*v.x + y*v.y + z*v.z; }
	float norm () const { return std::sqrt(x*x+y*y+z*z); }
	Vec3<Type> & normalize(Type l=1) { *this = (*this)*(l/norm()); return *this; }
};

typedef Vec2<float> Vec2f;
typedef Vec2<int>   Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int>   Vec3i;