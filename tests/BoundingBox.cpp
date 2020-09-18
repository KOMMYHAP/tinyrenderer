#include "MyMath.h"

using namespace mymath;

int main()
{
	Vec3f p1 {0, 0, 0};
	Vec3f p2 {1, 1, 1};
	Vec3f p3 {2, 2, 2};
	BoundingBox bbox {p1, p2, p3};

	const auto & [min, max] = bbox.MinMax();
	if (!(min == p1) || !(max == p3))
	{
		return 1;
	}

}
