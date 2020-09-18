#include "Coordinate.h"
#include <cmath>
float Vector3F::ScalarMult(const Vector3F& a, const Vector3F& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3F Vector3F::VectorMult(const Vector3F& a, const Vector3F& b)
{
	float x = a.y * b.z - b.y * a.z;
	float y = b.x * a.z - a.x * b.z;
	float z = a.x * b.y - b.x * a.y;

	return { x, y, z };
}

Vector3F::Vector3F()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3F::Vector3F(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

Vector3F::Vector3F(const Vector3F& that)
{
	x = that.x;
	y = that.y;
	z = that.z;
}

float Vector3F::SqrMagnitude() const
{
	return x * x + y * y + z * z;
}

float Vector3F::Magnitude() const
{
	return sqrtf(SqrMagnitude());
}

const Vector3F operator/(const Vector3F& a, float b)
{
	return Vector3F(a.x / b, a.y / b, a.z / b);
}

Vector3F Vector3F::Normalized() const
{
	float len = Magnitude();
	if (len == 0)
		return *this;
	return *this / len;
}

const Vector3F& Vector3F::operator=(const Vector3F& that)
{
	x = that.x;
	y = that.y;
	z = that.z;
	return *this;
}

const Vector3F& operator+(const Vector3F& that)
{
	return that;
}
const Vector3F operator-(const Vector3F& that)
{
	return Vector3F(-that.x, -that.y, -that.z);
}

const Vector3F& Vector3F::operator+=(const Vector3F& that)
{
	x += that.x;
	y += that.y;
	z += that.z;
	return *this;
}

const Vector3F& Vector3F::operator-=(const Vector3F& that)
{
	x -= that.x;
	y -= that.y;
	z -= that.z;
	return *this;
}

const Vector3F operator+(const Vector3F& a, const Vector3F& b)
{
	return Vector3F(a.x + b.x, a.y + b.y, a.z + b.z);
}

const Vector3F operator*(const Vector3F& a, const Vector3F& b)
{
	return Vector3F(a.x * b.x, a.y * b.y, a.z * b.z);
}

const Vector3F operator/(const Vector3F& a, const Vector3F& b)
{
	return Vector3F(a.x / b.x, a.y / b.y, a.z / b.z);
}

const Vector3F operator-(const Vector3F& a, const Vector3F& b)
{
	return Vector3F(a.x - b.x, a.y - b.y, a.z - b.z);
}

const Vector3F operator*(float a, const Vector3F& b)
{
	return Vector3F(a * b.x, a * b.y, a * b.z);
}

const Vector3F operator*(const Vector3F& a, float b)
{
	return Vector3F(a.x * b, a.y * b, a.z * b);
}

const bool operator==(const Vector3F& a, const Vector3F& b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

const bool operator!=(const Vector3F& a, const Vector3F& b)
{
	return !(a == b);
}

