#include "Collider.h"
#include "Space.h"
#include <iostream>
#include <fstream>

int main()
{
	size_t triangle_count = 0;
	std::cin >> triangle_count;

	Collider::Space space;
	for (size_t i = 0; i < triangle_count; i++) {
		Vector::Vector3<double> a, b, c;
		std::cin >> a.x >> a.y >> a.z;
		std::cin >> b.x >> b.y >> b.z;
		std::cin >> c.x >> c.y >> c.z;
		std::vector<Vector::Vector3<double>> triangle_points = {a, b, c};
		Collider::PolygonCollider collider;
		collider.Init(triangle_points);
		space.AddTriangle(collider);
	}
	space.CreateSpace();
	space.FindAndPrintCollidingTriangles();

	return 0;
}
