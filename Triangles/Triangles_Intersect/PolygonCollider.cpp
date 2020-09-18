#include "PolygonCollider.h"
#include <cmath>
PolygonCollider::PolygonCollider()
{
	Init();
}

PolygonCollider::PolygonCollider(std::vector<Vector3F>& points)
{
	Init(points);
}

void PolygonCollider::Init()
{
	_points.resize(0);
}

void PolygonCollider::Init(std::vector<Vector3F>& points)
{
	_points = points;
}


unsigned PolygonCollider::GetPointsCount() const
{
	return _points.size();
}
Vector3F PolygonCollider::GetPoint(unsigned i) const
{
	return _points[i];
}