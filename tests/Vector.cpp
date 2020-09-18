#include "Vector.h"
#include <array>

using namespace mymath;

int main()
{
	// compileness check of Vec3
	{
		Vec3f _vec3f_1 = {1, 2, 3};
		Vec3f _vec3f_2 = std::array<float, 3>{1, 2, 3};
		float data[3] = {};
		Vec3f _vec3f_3 = data;
	}

	{
		auto vec3f = Vec3f(1, 2, 3);
		if (vec3f != Vec3f(1, 2, 3))
		{
			return 1;
		}

		vec3f = Vec3f();
		if (vec3f[0] != 0.0f || vec3f[1] != 0.0f || vec3f[2] != 0.0f)
		{
			return 1;
		}

		float data[3] = {1.0f, 2.0f, 3.0f};
		vec3f = Vec3f(data);
		if (vec3f[0] != 1 || vec3f[1] != 2 || vec3f[2] != 3)
		{
			return 1;
		}
		
		std::array _array = {1.0f, 2.0f, 3.0f};
	}

	// compileness check Vec2
	{
		Vec2f _vec2f_1 = {1, 2};
		Vec2f _vec2f_2 = std::array<float, 2>{1, 2};
		float data[2] = {};
		Vec2f _vec2f_3 = data;
	}
}