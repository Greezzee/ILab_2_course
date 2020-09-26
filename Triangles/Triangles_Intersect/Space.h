#include "PolygonCollider.h"
#include "Collider.h"
#include <unordered_map>
#include <set>
#include <iostream>
class Space
{
public:
	Space();

	void AddTriangle(PolygonCollider col);

	void CreateSpace();
	void FindAndPrintCollidingTriangles();
	void ClearTriangles();
	void ClearSpace();

private:

	struct Triangle
	{
		PolygonCollider collider;
		bool is_collide_flag = false;
		Vector3F min_point, max_point;
		Vector3I min_space_point, max_space_point;

		std::set<Triangle*> collided_triangles;
	};

	size_t triangle_count_;
	Vector3F min_point_, max_point_;
	std::vector<Triangle> triangles_;

	unsigned quadric_space_size_;
	Vector3F quadric_side_;

	std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, std::set<Triangle*>>>> quadric_space_;

	void AddElem(Triangle* new_obj, int x, int y, int z);
	void CheckCollisionInQuadric(Triangle* obj, int x, int y, int z);
};