#include "MathLib.h"

using namespace Math;

int main()
{
	Vec3f p1 {0, 0, 0};
	Vec3f p2 {1, 1, 1};
	Vec3f p3 {2, 2, 2};
	BoundingBox bbox {p1, p2, p3};

	if (!(bbox.Min() == p1) || !(bbox.Max() == p3))
	{
		return 1;
	}

}
