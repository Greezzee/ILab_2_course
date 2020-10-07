#pragma once
#include <gtest/gtest.h>
#include "../Triangles_Source/Collider.h"

TEST(ColliderCreation, ColliderTest) {
	Collider::PolygonCollider col1;
	ASSERT_EQ(col1.GetPointsCount(), 0);

	Vector3F a(0.2, 4, 0.88821312), b(1, 1, 1), c(56, 321, 423746.23463284);
	std::vector<Vector3F> points = {a, b, c};
	Collider::PolygonCollider col2(points);
	ASSERT_EQ(col2.GetPointsCount(), 3);
	ASSERT_EQ(col2.GetPoint(0), a);
	ASSERT_EQ(col2.GetPoint(1), b);
	ASSERT_EQ(col2.GetPoint(2), c);
}

TEST(ColliderReInit, ColliderTest) {
	Collider::PolygonCollider col1;
	ASSERT_EQ(col1.GetPointsCount(), 0);

	Vector3F a(0.2, 4, 0.88821312), b(1, 1, 1), c(56, 321, 423746.23463284);
	std::vector<Vector3F> points = { a, b, c };
	col1.Init(points);
	ASSERT_EQ(col1.GetPointsCount(), 3);
	ASSERT_EQ(col1.GetPoint(0), a);
	ASSERT_EQ(col1.GetPoint(1), b);
	ASSERT_EQ(col1.GetPoint(2), c);

	std::vector<Vector3F> lots_of_points;
	for (size_t i = 0; i < 1000; i++)
		lots_of_points.push_back({ (float)i, 2 * (float)i, 3 * (float)i });

	col1.Init(lots_of_points);
	ASSERT_EQ(col1.GetPointsCount(), 1000);
	for (size_t i = 0; i < 1000; i++)
		ASSERT_EQ(col1.GetPoint(i), Vector3F((float)i, 2 * (float)i, 3 * (float)i ));
}

TEST(OnePlaneTrue, ColliderTest)
{
	std::vector<Vector3F> points_a, points_b;
	points_a = { {0, 0, 0}, {1, 0, 0}, {1, 1, 0} };
	points_b = { {0, 1, 0}, {1, -1, 0}, {-1, -1, 0} };
	Collider::PolygonCollider a(points_a), b(points_b);
	EXPECT_TRUE(Collider::IsCollide(a, b));
}

TEST(OnePlaneFalse, ColliderTest)
{
	std::vector<Vector3F> points_a, points_b;
	points_a = { {0, 0, 0}, {1, 0, 0}, {1, 1, 0} };
	points_b = { {0, 2, 0}, {1, 2, 0}, {2, 1, 0} };
	Collider::PolygonCollider a(points_a), b(points_b);
	EXPECT_FALSE(Collider::IsCollide(a, b));
}

TEST(OnePlaneTrueEdge, ColliderTest)
{
	std::vector<Vector3F> points_a, points_b;
	points_a = { {0, 0, 0}, {1, 0, 0}, {1, 1, 0} };
	points_b = { {1, 1, 0}, {1, 0, 0}, {256, 415, 0} };
	Collider::PolygonCollider a(points_a), b(points_b);
	EXPECT_TRUE(Collider::IsCollide(a, b));
}

TEST(OnePlaneTruePoint, ColliderTest)
{
	std::vector<Vector3F> points_a, points_b;
	points_a = { {0, 0, 0}, {1, 0, 0}, {1, 1, 0} };
	points_b = { {1, 1, 0}, {1, 156, 0}, {256, 415, 0} };
	Collider::PolygonCollider a(points_a), b(points_b);
	EXPECT_TRUE(Collider::IsCollide(a, b));
}

TEST(ZeroTriangles, ColliderTest)
{
	std::vector<Vector3F> points_a, points_b;
	points_a = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	points_b = { {-1, 0, 0}, {1, 1, 0}, {1, -1, 0} };
	Collider::PolygonCollider a(points_a), b(points_b);
	EXPECT_TRUE(Collider::IsCollide(a, b));
}

TEST(TwoZeroTriangles, ColliderTest)
{
	std::vector<Vector3F> points_a, points_b;
	points_a = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	points_b = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	Collider::PolygonCollider a(points_a), b(points_b);
	EXPECT_TRUE(Collider::IsCollide(a, b));
}

TEST(TwoZeroTrianglesFalse, ColliderTest)
{
	std::vector<Vector3F> points_a, points_b;
	points_a = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	points_b = { {1, 1, 0}, {1, 1, 0}, {1, 1, 0} };
	Collider::PolygonCollider a(points_a), b(points_b);
	EXPECT_FALSE(Collider::IsCollide(a, b));
}

TEST(TwoLines, ColliderTest)
{
	std::vector<Vector3F> points_a, points_b;
	points_a = { {0, 0, 0}, {1, 1, 0}, {0, 0, 0} };
	points_b = { {0, 1, 0}, {1, 0, 0}, {0, 1, 0} };
	Collider::PolygonCollider a(points_a), b(points_b);
	EXPECT_TRUE(Collider::IsCollide(a, b));
}

TEST(TwoLinesFalse, ColliderTest)
{
	std::vector<Vector3F> points_a, points_b;
	points_a = { {0, 0, 0}, {1, 1, 0}, {0, 0, 0} };
	points_b = { {0, 1, 0}, {1, 2, 0}, {0, 1, 0} };
	Collider::PolygonCollider a(points_a), b(points_b);
	EXPECT_TRUE(Collider::IsCollide(a, b));
}

TEST(SpaceTrue, ColliderTest)
{
	std::vector<Vector3F> points_a, points_b;
	points_a = { {0, 0, 0}, {1, 0, 1}, {0, 1, 0} };
	points_b = { {0, 1, 1}, {1, 0, 0}, {0.5, 1, 1} };
	Collider::PolygonCollider a(points_a), b(points_b);
	EXPECT_TRUE(Collider::IsCollide(a, b));
} 
