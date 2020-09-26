#include "Space.h"

Space::Space() :
	min_point_(Vector3F(INFINITY, INFINITY, INFINITY)), max_point_(Vector3F(-INFINITY, -INFINITY, -INFINITY)),
	triangle_count_(0), quadric_space_size_(0), quadric_side_(Vector3F(0, 0, 0)) {}

void Space::AddTriangle(PolygonCollider col) {
	Triangle new_tri;
	new_tri.collider = col;
	new_tri.is_collide_flag = false;
	new_tri.max_point = Vector3F(-INFINITY, -INFINITY, -INFINITY);
	new_tri.min_point = Vector3F(INFINITY, INFINITY, INFINITY);

	for (int i = 0; i < col.GetPointsCount(); i++) {
		auto point = col.GetPoint(i);
		min_point_.x = std::min(min_point_.x, point.x);
		min_point_.y = std::min(min_point_.y, point.y);
		min_point_.z = std::min(min_point_.z, point.z);

		max_point_.x = std::max(max_point_.x, point.x);
		max_point_.y = std::max(max_point_.y, point.y);
		max_point_.z = std::max(max_point_.z, point.z);

		new_tri.min_point.x = std::min(new_tri.min_point.x, point.x);
		new_tri.min_point.y = std::min(new_tri.min_point.y, point.y);
		new_tri.min_point.z = std::min(new_tri.min_point.z, point.z);

		new_tri.max_point.x = std::max(new_tri.max_point.x, point.x);
		new_tri.max_point.y = std::max(new_tri.max_point.y, point.y);
		new_tri.max_point.z = std::max(new_tri.max_point.z, point.z);
	}

	triangles_.push_back(new_tri);
	triangle_count_++;
}

void Space::CreateSpace() {
	quadric_space_size_ = (int)(powf((float)triangle_count_, 0.33333f)) + 1;

	quadric_side_.x = std::max((max_point_.x - min_point_.x) / (float)quadric_space_size_, EPS);
	quadric_side_.y = std::max((max_point_.x - min_point_.x) / (float)quadric_space_size_, EPS);
	quadric_side_.z = std::max((max_point_.x - min_point_.x) / (float)quadric_space_size_, EPS);

	for (int i = 0; i < triangle_count_; i++) {
		Triangle* sp_tri = &(triangles_[i]);

		sp_tri->min_space_point.x = (int)((sp_tri->min_point.x - min_point_.x - EPS) / quadric_side_.x);
		sp_tri->min_space_point.y = (int)((sp_tri->min_point.y - min_point_.y - EPS) / quadric_side_.y);
		sp_tri->min_space_point.z = (int)((sp_tri->min_point.z - min_point_.z - EPS) / quadric_side_.z);

		sp_tri->max_space_point.x = (int)((sp_tri->max_point.x - min_point_.x + EPS) / quadric_side_.x);
		sp_tri->max_space_point.y = (int)((sp_tri->max_point.y - min_point_.y + EPS) / quadric_side_.y);
		sp_tri->max_space_point.z = (int)((sp_tri->max_point.z - min_point_.z + EPS) / quadric_side_.z);

		for (int x = sp_tri->min_space_point.x; x <= sp_tri->max_space_point.x; x++)
			for (int y = sp_tri->min_space_point.y; y <= sp_tri->max_space_point.y; y++)
				for (int z = sp_tri->min_space_point.z; z <= sp_tri->max_space_point.z; z++)
					AddElem(sp_tri, x, y, z);
	}
}

void Space::FindAndPrintCollidingTriangles() {
	for (int i = 0; i < triangle_count_; i++) {
		if (triangles_[i].is_collide_flag) {
			std::cout << i << " ";
			continue;
		}

		Triangle* sp_tri = &triangles_[i];
		for (int x = sp_tri->min_space_point.x; x <= sp_tri->max_space_point.x; x++)
			for (int y = sp_tri->min_space_point.y; y <= sp_tri->max_space_point.y; y++)
				for (int z = sp_tri->min_space_point.z; z <= sp_tri->max_space_point.z; z++)
					CheckCollisionInQuadric(sp_tri, x, y, z);

		if (triangles_[i].is_collide_flag) {
			std::cout << i << " ";
			continue;
		}
	}
}

void Space::ClearTriangles() {
	ClearSpace();
	min_point_ = Vector3F(INFINITY, INFINITY, INFINITY);
	max_point_ = Vector3F(-INFINITY, -INFINITY, -INFINITY);
	triangle_count_ = 0;
	triangles_.clear();
}

void Space::ClearSpace() {
	quadric_space_.clear();
	quadric_space_size_ = 0;
	quadric_side_ = { 0, 0, 0 };
}

void Space::AddElem(Triangle* new_obj, int x, int y, int z) {
	quadric_space_[x][y][z].insert(new_obj);
}

void Space::CheckCollisionInQuadric(Triangle* obj, int x, int y, int z) {
	auto a = quadric_space_.find(x);
	if (a == quadric_space_.end())
		return;
	auto b = a->second.find(y);
	if (b == a->second.end())
		return;
	auto c = b->second.find(z);
	if (c == b->second.end())
		return;
	auto quadric = c->second;

	for (auto x = quadric.begin(); x != quadric.end(); x++) {
		if (*x != obj) {
			if (obj->collided_triangles.find(*x) == obj->collided_triangles.end())
				if (Collider::IsCollide((*x)->collider, obj->collider)) {
					(*x)->is_collide_flag = true;
					obj->is_collide_flag = true;
					obj->collided_triangles.insert(*x);
				}
		}
	}
}