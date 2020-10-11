#pragma once
#include "PolygonCollider.h"
#include "Coordinate.h"
const double EPS = 0.0000001;
namespace Collider
{
	//! Check if two polygons collide
	bool IsCollide(const PolygonCollider& a, const PolygonCollider& b);
}
