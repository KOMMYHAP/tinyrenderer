#include "Math.h"
#include "Vec2.h"
#include "Vec3.h"

int main()
{
	// compileness check of Vec3
	{
		Math::Vec3f _vec3f_1 = {1, 2, 3};
		Math::Vec3f _vec3f_2 = std::array<float, 3>{1, 2, 3};
		float data[3] = {};
		Math::Vec3f _vec3f_3 = data;
	}

	{
		auto vec3f = Math::Vec3f(1, 2, 3);
		if (vec3f != Math::Vec3f(1, 2, 3))
		{
			return 1;
		}

		vec3f = Math::Vec3f();
		if (vec3f[0] != 0.0f || vec3f[1] != 0.0f || vec3f[2] != 0.0f)
		{
			return 1;
		}

		float data[3] = {1.0f, 2.0f, 3.0f};
		vec3f = Math::Vec3f(data);
		if (vec3f[0] != 1 || vec3f[1] != 2 || vec3f[2] != 3)
		{
			return 1;
		}

		std::array _array = {1.0f, 2.0f, 3.0f};
	}

	// compileness check Vec2
	{
		Math::Vec2f _vec2f_1 = {1, 2};
		Math::Vec2f _vec2f_2 = std::array<float, 2>{1, 2};
		float data[2] = {};
		Math::Vec2f _vec2f_3 = data;
	}
}
