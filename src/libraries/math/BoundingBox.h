#pragma once

#include "Vec3.h"

namespace Math
{
	template <class T>
	class BoundingBoxT
	{
	public:
		BoundingBoxT() = default;

		BoundingBoxT(const Vec3<T> & pointA, const Vec3<T> & pointB, const Vec3<T> & pointC)
		{
			for (int i = 0; i < 3; ++i)
			{
				auto [a, b] = std::minmax({pointA[i], pointB[i], pointC[i]});
				_min[i] = a;
				_max[i] = b;
			}
		}

		const Vec3<T> & Min() const { return _min; }
		const Vec3<T> & Max() const { return _max; }
		
		bool Invalid() const { return Min() > Max(); }

	private:
		constexpr static auto _maxValue {std::numeric_limits<T>::max()};
		constexpr static auto _minValue {std::numeric_limits<T>::min()};

		inline const static Vec3<T>	_maxPoint {_maxValue, _maxValue, _maxValue};
		inline const static Vec3<T>	_minPoint {_minValue, _minValue, _minValue};

		Vec3<T> _min {_maxPoint};
		Vec3<T> _max {_minPoint};
	};

	using BoundingBox = BoundingBoxT<float>;

}
