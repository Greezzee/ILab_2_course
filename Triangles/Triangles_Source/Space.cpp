#include "Space.h"
#include <cmath>

void Collider::Space::AddTriangle(Collider::PolygonCollider col) {
	Triangle new_tri;
	new_tri.collider = col;
	new_tri.is_collide_flag = false;
	new_tri.max_point = Vector::Vector3<double>{-INFINITY, -INFINITY, -INFINITY};
	new_tri.min_point = Vector::Vector3<double>{INFINITY, INFINITY, INFINITY};
	new_tri.id = triangles_.size();

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

void Collider::Space::CreateSpace() {
	quadric_space_size_ = (int)(powf((double)triangle_count_, 0.33333f)) + 1;

	quadric_side_.x = std::max((max_point_.x - min_point_.x) / (double)quadric_space_size_, EPS);
	quadric_side_.y = std::max((max_point_.x - min_point_.x) / (double)quadric_space_size_, EPS);
	quadric_side_.z = std::max((max_point_.x - min_point_.x) / (double)quadric_space_size_, EPS);

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
					AddElem(sp_tri, Vector::Vector3<int>{x, y, z});
	}
}

void Collider::Space::FindAndPrintCollidingTriangles() {
	for (int i = 0; i < triangle_count_; i++) {
		if (triangles_[i].is_collide_flag) {
			std::cout << i << "\n{";
			for (auto j = triangles_[i].collided_triangles.begin(); j != triangles_[i].collided_triangles.end(); ++j) {
				std::cout << (*j)->id << " ";
			}
			std::cout << "}\n";
			continue;
		}

		Triangle* sp_tri = &triangles_[i];
		for (int x = sp_tri->min_space_point.x; x <= sp_tri->max_space_point.x; x++)
			for (int y = sp_tri->min_space_point.y; y <= sp_tri->max_space_point.y; y++)
				for (int z = sp_tri->min_space_point.z; z <= sp_tri->max_space_point.z; z++)
					CheckCollisionInQuadric(sp_tri, Vector::Vector3<int>{x, y, z});

		if (triangles_[i].is_collide_flag) {
			std::cout << i << "\n{";
			for (auto j = triangles_[i].collided_triangles.begin(); j != triangles_[i].collided_triangles.end(); ++j) {
				std::cout << (*j)->id << " ";
			}
			std::cout << "}\n";
		}
	}
}

void Collider::Space::ClearSpace() {
	quadric_space_.clear();
	quadric_space_size_ = 0;
	quadric_side_ = { 0, 0, 0 };
}

void Collider::Space::CheckCollisionInQuadric(Triangle* obj, Vector::Vector3<int> pos) {
	auto a = quadric_space_.find(pos.x);
	if (a == quadric_space_.end())
		return;
	auto b = a->second.find(pos.y);
	if (b == a->second.end())
		return;
	auto c = b->second.find(pos.z);
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
					(*x)->collided_triangles.insert(obj);
				}
		}
	}
}
