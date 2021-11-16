#pragma once

#include "geometry.h"

namespace Utils
{
	template <class T>
	class BoundingBoxT
	{
	public:
		BoundingBoxT() = default;

		BoundingBoxT(const vec3 & pointA, const vec3 & pointB, const vec3 & pointC)
		{
			for (int i = 0; i < 3; ++i)
			{
				auto [a, b] = std::minmax({pointA[i], pointB[i], pointC[i]});
				_min[i] = a;
				_max[i] = b;
			}
		}

		const vec3 & Min() const { return _min; }
		const vec3 & Max() const { return _max; }

	private:
		constexpr static auto _maxValue {std::numeric_limits<T>::max()};
		constexpr static auto _minValue {std::numeric_limits<T>::min()};

		inline const static vec3	_maxPoint {_maxValue, _maxValue, _maxValue};
		inline const static vec3	_minPoint {_minValue, _minValue, _minValue};

		vec3 _min {_maxPoint};
		vec3 _max {_minPoint};
	};

	using BoundingBox = BoundingBoxT<float>;

}
