//#include "pch.h"
#include "Collider.h"

#include <cmath>

#include "Coordinate.h"
#include "math.h"

bool Collider::IsCollide(const PolygonCollider& a, const PolygonCollider& b)
{
	unsigned a_s = a.GetPointsCount();
	unsigned b_s = b.GetPointsCount();
	if (a_s < 3 || b_s < 3) //check, if it is a polygon (not a line, dot or empty)
		return false;

	std::vector<Vector3F> axis_a(a_s + 1);
	std::vector<Vector3F> axis_b(b_s + 1);
	axis_a[0] = Vector3F::VectorMult(a.GetPoint(0) - a.GetPoint(1), a.GetPoint(2) - a.GetPoint(1)); //find normal to plane of 1st polygon
	axis_b[0] = Vector3F::VectorMult(b.GetPoint(0) - b.GetPoint(1), b.GetPoint(2) - b.GetPoint(1)); //find normal to plane of 2nd polygon
	for (size_t i = 0; i < a_s; i++) 
		axis_a[i + 1] = Vector3F::VectorMult(axis_a[0], a.GetPoint(i) - a.GetPoint((i + 1) % a_s));
	for (size_t i = 0; i < b_s; i++)
		axis_b[i + 1] = Vector3F::VectorMult(axis_b[0], b.GetPoint(i) - b.GetPoint((i + 1) % b_s));
	
	std::vector<Vector3F> test_axes((a_s + 1) * (b_s + 1));
	for (size_t i = 0; i < a_s + 1; i++)
		for (size_t j = 0; j < b_s + 1; j++)
			test_axes[i * (b_s + 1) + j] = Vector3F::VectorMult(axis_a[i], axis_b[j]);

	test_axes.insert(test_axes.end(), axis_a.begin(), axis_a.end());
	test_axes.insert(test_axes.end(), axis_b.begin(), axis_b.end());

	size_t axes_count = test_axes.size();
	for (size_t i = 0; i < axes_count; i++) {
		if (test_axes[i].SqrMagnitude() > EPS && !AxisIntersect(a, b, test_axes[i]))
			return false;
	}
	if (!AxisIntersect(a, b, {1, 1, 1}))
		return false;
	return true;
}


bool Collider::AxisIntersect(const PolygonCollider& a, const PolygonCollider& b, const Vector3F& norm)
{
	float min_a, min_b, max_a, max_b;
	min_a = max_a = Vector3F::ScalarMult(a.GetPoint(0), norm);
	min_b = max_b = Vector3F::ScalarMult(b.GetPoint(0), norm);
	unsigned a_s = a.GetPointsCount();
	unsigned b_s = b.GetPointsCount();
	for (unsigned j = 1; j < a_s; j++) //find all other projections
	{
		float len_a = Vector3F::ScalarMult(a.GetPoint(j), norm);
		if (len_a < min_a)
			min_a = len_a;
		if (len_a > max_a)
			max_a = len_a;
	}

	for (unsigned j = 1; j < b_s; j++)
	{
		float len_b = Vector3F::ScalarMult(b.GetPoint(j), norm);
		if (len_b < min_b)
			min_b = len_b;
		if (len_b > max_b)
			max_b = len_b;
	}

	return !(max_a - min_b <= -EPS || max_b - min_a <= -EPS);
}
