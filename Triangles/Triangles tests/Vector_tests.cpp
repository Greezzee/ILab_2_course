#include "pch.h"
#include "Coordinate.h"

TEST(CreateVector, Vector3FTest)
{
	Vector3F vec1;
	ASSERT_TRUE(vec1.x == 0.f && vec1.y == 0.f && vec1.z == 0.f);

	float a = 12.6, b = 0.4, c = -0.000001;
	Vector3F vec2(a, b, c);
	ASSERT_TRUE(vec2.x == a && vec2.y == b && vec2.z == c);

	Vector3F vec3 = { a, b, c };
	ASSERT_TRUE(vec3.x == a && vec3.y == b && vec3.z == c);

	Vector3F vec4 = Vector3F( a, b, c );
	ASSERT_TRUE(vec4.x == a && vec4.y == b && vec4.z == c);

	Vector3F vec5 = Vector3F(vec4);
	ASSERT_TRUE(vec5.x == a && vec5.y == b && vec5.z == c);
}

TEST(VectorFunctions, Vector3FTest)
{
	float a = 2.f, b = 2.f, c = -1.f;
	float EPS = 0.000001f;
	Vector3F vec = { a, b, c };

	EXPECT_LE(fabsf(vec.Magnitude() - 3.f), EPS);
	EXPECT_LE(fabsf(vec.SqrMagnitude() - 9.f), EPS);

	Vector3F norm_vec = { a / 3.f, b / 3.f, c / 3.f };
	EXPECT_TRUE(fabsf(vec.Normalized().x - norm_vec.x) <= EPS, fabsf(vec.Normalized().y - norm_vec.y) <= EPS, fabsf(vec.Normalized().z - norm_vec.z) <= EPS);
}

TEST(ZeroVectorFunctions, Vector3FTest)
{
	Vector3F vec = { 0.f, 0.f, 0.f };
	float EPS = 0.000001f;

	EXPECT_LE(fabsf(vec.Magnitude()), EPS);
	EXPECT_LE(fabsf(vec.SqrMagnitude()), EPS);

	EXPECT_TRUE(fabsf(vec.Normalized().x) < EPS && fabsf(vec.Normalized().y) < EPS && fabsf(vec.Normalized().z) < EPS);
}

TEST(VectorMultiplications, Vector3FTest)
{
	Vector3F vec1(1, 2, -1), vec2(-4, 2, -5);
	Vector3F vec3(-4, -8, 4), vec4(0, 0, 0);
	float EPS = 0.000001f;

	float vec_scal = Vector3F::ScalarMult(vec1, vec2);
	Vector3F vec_vec = Vector3F::VectorMult(vec1, vec2);

	EXPECT_LE(fabsf(vec_scal - 5.f), EPS);
	EXPECT_TRUE(fabsf(vec_vec.x + 8.f) < EPS && fabsf(vec_vec.y - 9.f) < EPS && fabsf(vec_vec.z - 10.f) < EPS);

	vec_vec = Vector3F::VectorMult(vec1, vec3);
	EXPECT_TRUE(fabsf(vec_vec.x) < EPS && fabsf(vec_vec.y) < EPS && fabsf(vec_vec.z) < EPS);

	vec_scal = Vector3F::ScalarMult(vec1, vec4);
	EXPECT_LE(fabsf(vec_scal), EPS);
}

TEST(VectorOperations, Vector3Test)
{
	float a, b, c, d, e, f;
	a = 2.3; b = 2.7; c = -6.9;
	d = -8.2; e = 5543545.662; f = 0.000002;

	Vector3F vec1(a, b, c), vec2(d, e, f);

	Vector3F vec3 = vec1;

	EXPECT_EQ(vec1, vec3);
	EXPECT_NE(vec1, vec2);
	EXPECT_EQ(vec1 + vec2, Vector3F(a + d, b + e, c + f));
	EXPECT_EQ(vec1 - vec2, Vector3F(a - d, b - e, c - f));
	EXPECT_EQ(vec1 * vec2, Vector3F(a * d, b * e, c * f));
	EXPECT_EQ(vec1 / vec2, Vector3F(a / d, b / e, c / f));
	float k = 12.5f;
	EXPECT_EQ(vec1 * k, Vector3F(a * k, b * k, c * k));
	EXPECT_EQ(vec1 / k, Vector3F(a / k, b / k, c / k));
	EXPECT_EQ(k * vec1, Vector3F(a * k, b * k, c * k));

	vec1 += vec2;
	EXPECT_EQ(vec1, Vector3F(a + d, b + e, c + f));

	vec1 -= 2 * vec2;
	EXPECT_EQ(vec1, Vector3F(a - d, b - e, c - f));
}