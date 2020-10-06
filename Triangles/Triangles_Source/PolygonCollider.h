#pragma once

#include "Coordinate.h"
#include <vector>

namespace Collider {
	class PolygonCollider
	{
	public:

		PolygonCollider();
		PolygonCollider(std::vector<Vector3F>& points);

		void Init();

		void Init(std::vector<Vector3F>& points);

		unsigned GetPointsCount() const;

		Vector3F GetPoint(unsigned i) const;

	protected:

		std::vector<Vector3F> _points;
	};
}
