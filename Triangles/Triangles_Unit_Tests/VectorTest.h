#pragma once

#include <gtest/gtest.h>
#include "../Triangles_Source/Coordinate.h"
#include <cmath>

TEST(CreateVector, Vector3FTest)
{
	Vector::Vector3<double> vec1;
	ASSERT_TRUE(vec1.x == 0.f && vec1.y == 0.f && vec1.z == 0.f);

	double a = 12.6, b = 0.4, c = -0.000001;
	Vector::Vector3<double> vec2(a, b, c);
	ASSERT_TRUE(vec2.x == a && vec2.y == b && vec2.z == c);

	Vector::Vector3<double> vec3 = { a, b, c };
	ASSERT_TRUE(vec3.x == a && vec3.y == b && vec3.z == c);

	Vector::Vector3<double> vec4 = Vector::Vector3<double>( a, b, c );
	ASSERT_TRUE(vec4.x == a && vec4.y == b && vec4.z == c);

	Vector::Vector3<double> vec5 = Vector::Vector3<double>(vec4);
	ASSERT_TRUE(vec5.x == a && vec5.y == b && vec5.z == c);
}

TEST(VectorFunctions, Vector3FTest)
{
	double a = 2.0, b = 2.0, c = -1.0;
	double EPS = 0.000001;
	Vector::Vector3<double> vec = { a, b, c };

	EXPECT_LE(std::abs(vec.Magnitude() - 3.f), EPS);
	EXPECT_LE(std::abs(vec.SqrMagnitude() - 9.f), EPS);

	Vector::Vector3<double> norm_vec = { a / 3.f, b / 3.f, c / 3.f };
	std::cout << vec.Normalized().x << " " << vec.Normalized().y << " " << vec.Normalized().z << "\n";
	EXPECT_TRUE(std::abs(vec.Normalized().x - norm_vec.x) <= EPS && std::abs(vec.Normalized().y - norm_vec.y) <= EPS && std::abs(vec.Normalized().z - norm_vec.z) <= EPS);
}

TEST(ZeroVectorFunctions, Vector3FTest)
{
	Vector::Vector3<double> vec = { 0, 0, 0 };
	double EPS = 0.000001;

	EXPECT_LE(std::abs(vec.Magnitude()), EPS);
	EXPECT_LE(std::abs(vec.SqrMagnitude()), EPS);

	EXPECT_TRUE(std::abs(vec.Normalized().x) < EPS && std::abs(vec.Normalized().y) < EPS && std::abs(vec.Normalized().z) < EPS);
}

TEST(VectorMultiplications, Vector3FTest)
{
	Vector::Vector3<double> vec1(1, 2, -1), vec2(-4, 2, -5);
	Vector::Vector3<double> vec3(-4, -8, 4), vec4(0, 0, 0);
	float EPS = 0.000001f;

	float vec_scal = Vector::ScalarMult(vec1, vec2);
	Vector::Vector3<double> vec_vec = Vector::VectorMult(vec1, vec2);

	EXPECT_LE(fabsf(vec_scal - 5.f), EPS);
	EXPECT_TRUE(fabsf(vec_vec.x + 8.f) < EPS && fabsf(vec_vec.y - 9.f) < EPS && fabsf(vec_vec.z - 10.f) < EPS);

	vec_vec = Vector::VectorMult(vec1, vec3);
	EXPECT_TRUE(fabsf(vec_vec.x) < EPS && fabsf(vec_vec.y) < EPS && fabsf(vec_vec.z) < EPS);

	vec_scal = Vector::ScalarMult(vec1, vec4);
	EXPECT_LE(fabsf(vec_scal), EPS);
}

TEST(VectorOperations, Vector3Test)
{
	double a, b, c, d, e, f;
	a = 2.3; b = 2.7; c = -6.9;
	d = -8.2; e = 5543545.662; f = 0.000002;

	Vector::Vector3<double> vec1(a, b, c), vec2(d, e, f);

	Vector::Vector3<double> vec3 = vec1;

	EXPECT_EQ(vec1, vec3);
	EXPECT_NE(vec1, vec2);
	EXPECT_EQ(vec1 + vec2, Vector::Vector3<double>(a + d, b + e, c + f));
	EXPECT_EQ(vec1 - vec2, Vector::Vector3<double>(a - d, b - e, c - f));
	EXPECT_EQ(vec1 * vec2, Vector::Vector3<double>(a * d, b * e, c * f));
	EXPECT_EQ(vec1 / vec2, Vector::Vector3<double>(a / d, b / e, c / f));
	double k = 12.5;
	EXPECT_EQ(vec1 * k, Vector::Vector3<double>(a * k, b * k, c * k));
	EXPECT_EQ(vec1 / k, Vector::Vector3<double>(a / k, b / k, c / k));
	EXPECT_EQ(k * vec1, Vector::Vector3<double>(a * k, b * k, c * k));

	vec1 += vec2;
	a += d;
	b += e;
	c += f;
	EXPECT_EQ(vec1, Vector::Vector3<double>(a, b, c));

	vec1 -= 2.0 * vec2;
	a -= 2.0 * d;
	b -= 2.0 * e;
	c -= 2.0 * f;

	EXPECT_EQ(vec1, Vector::Vector3<double>(a, b, c));
} 