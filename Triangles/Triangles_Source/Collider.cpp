//#include "pch.h"
#include "Collider.h"

#include <cmath>

#include "Coordinate.h"
#include "math.h"
#include <iostream>
namespace {
	//! Check if projections of two polygons to axis norm collide 
	bool AxisIntersect(const Collider::PolygonCollider& a, const Collider::PolygonCollider& b, const Vector::Vector3<double>& norm)
	{
		double min_a, min_b, max_a, max_b;
		min_a = max_a = Vector::ScalarMult(a.GetPoint(0), norm);
		min_b = max_b = Vector::ScalarMult(b.GetPoint(0), norm);
		unsigned a_s = a.GetPointsCount();
		unsigned b_s = b.GetPointsCount();
		for (unsigned j = 1; j < a_s; j++) //find all other projections
		{
			float len_a = Vector::ScalarMult(a.GetPoint(j), norm);
			if (len_a < min_a)
				min_a = len_a;
			if (len_a > max_a)
				max_a = len_a;
		}

		for (unsigned j = 1; j < b_s; j++)
		{
			float len_b = Vector::ScalarMult(b.GetPoint(j), norm);
			if (len_b < min_b)
				min_b = len_b;
			if (len_b > max_b)
				max_b = len_b;
		}
		return !(max_a - min_b <= -EPS || max_b - min_a <= -EPS);
	}
}

bool Collider::IsCollide(const PolygonCollider& a, const PolygonCollider& b)
{
	unsigned a_s = a.GetPointsCount();
	unsigned b_s = b.GetPointsCount();
	if (a_s < 3 || b_s < 3) //check, if it is a polygon (not a line, dot or empty)
		return false;

	std::vector<Vector::Vector3<double>> axis_a{a_s + 1};
	std::vector<Vector::Vector3<double>> axis_b{b_s + 1};
	axis_a[0] = Vector::VectorMult(a.GetPoint(0) - a.GetPoint(1), a.GetPoint(2) - a.GetPoint(1)).Normalized(); //find normal to plane of 1st polygon
	axis_b[0] = Vector::VectorMult(b.GetPoint(0) - b.GetPoint(1), b.GetPoint(2) - b.GetPoint(1)).Normalized(); //find normal to plane of 2nd polygon
	for (size_t i = 0; i < a_s; i++) 
		axis_a[i + 1] = Vector::VectorMult(axis_a[0], a.GetPoint(i) - a.GetPoint((i + 1) % a_s)).Normalized();
	for (size_t i = 0; i < b_s; i++)
		axis_b[i + 1] = Vector::VectorMult(axis_b[0], b.GetPoint(i) - b.GetPoint((i + 1) % b_s)).Normalized();
	
	std::vector<Vector::Vector3<double>> test_axes;

	test_axes.insert(test_axes.end(), axis_a.begin(), axis_a.end());
	test_axes.insert(test_axes.end(), axis_b.begin(), axis_b.end());

	for (size_t i = 0; i < a_s; i++)
		for (size_t j = 0; j < b_s; j++)
			test_axes.push_back(Vector::VectorMult(a.GetPoint(i) - a.GetPoint((i + 1) % a_s), b.GetPoint(j) - b.GetPoint((j + 1) % b_s)).Normalized());


	size_t axes_count = test_axes.size();
	for (size_t i = 0; i < axes_count; i++) {
		if (test_axes[i].SqrMagnitude() > EPS * EPS && !AxisIntersect(a, b, test_axes[i]))
			return false;
	}
	if (!AxisIntersect(a, b, Vector::Vector3<double>{1, 1, 1}))
		return false;
	return true;
}
