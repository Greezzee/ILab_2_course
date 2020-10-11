#pragma once

#include "Coordinate.h"
#include <vector>

namespace Collider {
	class PolygonCollider
	{
	public:

		PolygonCollider();
		PolygonCollider(std::vector<Vector::Vector3<double>>& points);

		void Init();

		void Init(std::vector<Vector::Vector3<double>>& points);

		unsigned GetPointsCount() const;

		Vector::Vector3<double> GetPoint(unsigned i) const;

	private:

		std::vector<Vector::Vector3<double>> _points;
	};
}
