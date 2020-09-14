#pragma once

#include <limits>
#include <utility>
#include <algorithm>

#include "geometry.h"

namespace mymath
{
	template <class T>
	class BoundingBoxT
	{
	public:
		BoundingBoxT() = default;

		BoundingBoxT(const vec<3, T> & pointA, const vec<3, T> & pointB, const vec<3, T> & pointC)
		{
			auto & [min, max] = _minmax;
			for (int i = 0; i < 3; ++i)
			{
				auto [a, b] = std::minmax({pointA[i], pointB[i], pointC[i]});
				min[i] = a;
				max[i] = b;
			}
		}

		const auto & MinMax() const { return _minmax; }
		bool Invalid() const { return _minmax.first == _maxPoint && _minmax.second == _minPoint; }

	private:
		constexpr static auto _maxValue {std::numeric_limits<T>::max()};
		constexpr static auto _minValue {std::numeric_limits<T>::min()};

		inline const static Vec3f _maxPoint {_maxValue, _maxValue, _maxValue};
		inline const static Vec3f _minPoint {_minValue, _minValue, _minValue};

		std::pair<vec<3, T>, vec<3, T>>		_minmax {_maxPoint, _minPoint};
	};

	using BoundingBox = BoundingBoxT<float>;

}
