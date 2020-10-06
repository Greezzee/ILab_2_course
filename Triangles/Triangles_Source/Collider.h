#pragma once
#include "PolygonCollider.h"
#include "Coordinate.h"
const float EPS = 0.00001f;
namespace Collider
{
	//! Check if two polygons collide
	bool IsCollide(const PolygonCollider& a, const PolygonCollider& b);
}
