#include "Collider.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>

struct CollidableTriangle {
	PolygonCollider collider;
	bool is_collide_with_others = false;
};

int main()
{
	size_t triangle_count = 0;
	std::cin >> triangle_count;

	CollidableTriangle* triangles = new CollidableTriangle[triangle_count];
	for (size_t i = 0; i < triangle_count; i++) {
		Vector3F a, b, c;
		std::cin >> a.x >> a.y >> a.z;
		std::cin >> b.x >> b.y >> b.z;
		std::cin >> c.x >> c.y >> c.z;
		std::vector<Vector3F> triangle_points = {a, b, c};
		triangles[i].collider.Init(triangle_points);
	}

	for (size_t i = 0; i < triangle_count; i++) {
		for (size_t j = i + 1; j < triangle_count; j++) {
			if (Collider::IsCollide(triangles[i].collider, triangles[j].collider)) {
				triangles[i].is_collide_with_others = true;
				triangles[j].is_collide_with_others = true;
			}
		}
		if (triangles[i].is_collide_with_others)
			std::cout << i << " ";
	}
	delete[] triangles;
	return 0;
}