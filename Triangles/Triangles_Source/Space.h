#include "PolygonCollider.h"
#include "Collider.h"
#include <unordered_map>
#include <set>
#include <iostream>
#include <cmath>
namespace Collider {
	class Space
	{
	public:
		Space():
			min_point_(Vector::Vector3<double>(INFINITY, INFINITY, INFINITY)), max_point_(Vector::Vector3<double>(-INFINITY, -INFINITY, -INFINITY)),
			triangle_count_(0), quadric_space_size_(0), quadric_side_(Vector::Vector3<double>{0, 0, 0}) {}

		void AddTriangle(Collider::PolygonCollider col);

		void CreateSpace();
		void FindAndPrintCollidingTriangles();
		void ClearSpace();

	private:

		struct Triangle
		{
			Collider::PolygonCollider collider;
			bool is_collide_flag = false;
			Vector::Vector3<double> min_point, max_point;
			Vector::Vector3<int> min_space_point, max_space_point;

			std::set<Triangle*> collided_triangles;

			int id;
		};

		size_t triangle_count_;
		Vector::Vector3<double> min_point_, max_point_;
		std::vector<Triangle> triangles_;

		unsigned quadric_space_size_;
		Vector::Vector3<double> quadric_side_;

		std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, std::set<Triangle*>>>> quadric_space_;

		void AddElem(Triangle* new_obj, Vector::Vector3<int> pos) {
			quadric_space_[pos.x][pos.y][pos.z].insert(new_obj);
		}
		void CheckCollisionInQuadric(Triangle* obj, Vector::Vector3<int> pos);
	};
}