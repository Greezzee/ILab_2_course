#pragma once
#include "PolygonCollider.h"
#include "Coordinate.h"
class Collider
{
public:
	//! Check if two polygons collide
	static bool IsCollide(const PolygonCollider& a, const PolygonCollider& b);

private:

	//! Check if projections of two polygons to axis norm collide 
	static bool AxisIntersect(const PolygonCollider& a, const PolygonCollider& b, const Vector3F& norm);

};
