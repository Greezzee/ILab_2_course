#include "Collider.h"
#include "Space.h"
#include <iostream>
#include <fstream>

struct CollidableTriangle {
	PolygonCollider collider;
	bool is_collide_with_others = false;
};

int main()
{
	std::ifstream file;
	file.open("10000.1.txt");

	size_t triangle_count = 0;
	file >> triangle_count;

	Space space;
	for (size_t i = 0; i < triangle_count; i++) {
		Vector3F a, b, c;
		file >> a.x >> a.y >> a.z;
		file >> b.x >> b.y >> b.z;
		file >> c.x >> c.y >> c.z;
		std::vector<Vector3F> triangle_points = {a, b, c};
		PolygonCollider collider;
		collider.Init(triangle_points);
		space.AddTriangle(collider);
	}
	file.close();
	space.CreateSpace();
	space.FindAndPrintCollidingTriangles();

	return 0;
}