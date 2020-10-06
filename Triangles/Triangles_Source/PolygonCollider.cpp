#include "PolygonCollider.h"
#include <cmath>
Collider::PolygonCollider::PolygonCollider()
{
	Init();
}

Collider::PolygonCollider::PolygonCollider(std::vector<Vector3F>& points)
{
	Init(points);
}

void Collider::PolygonCollider::Init()
{
	_points.resize(0);
}

void Collider::PolygonCollider::Init(std::vector<Vector3F>& points)
{
	_points = points;
}


unsigned Collider::PolygonCollider::GetPointsCount() const
{
	return _points.size();
}
Vector3F Collider::PolygonCollider::GetPoint(unsigned i) const
{
	return _points[i];
}