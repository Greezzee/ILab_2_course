#include "PolygonCollider.h"
#include <cmath>
Collider::PolygonCollider::PolygonCollider()
{
	Init();
}

Collider::PolygonCollider::PolygonCollider(std::vector<Vector::Vector3<double>>& points)
{
	Init(points);
}

void Collider::PolygonCollider::Init()
{
	_points.resize(0);
}

void Collider::PolygonCollider::Init(std::vector<Vector::Vector3<double>>& points)
{
	_points = points;
}


unsigned Collider::PolygonCollider::GetPointsCount() const
{
	return _points.size();
}
Vector::Vector3<double> Collider::PolygonCollider::GetPoint(unsigned i) const
{
	return _points[i];
}