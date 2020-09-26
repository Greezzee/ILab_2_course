#pragma once
struct Vector3F
{
	float x, y, z;
	
	//! Make vector (0, 0, 0)
	Vector3F();

	//! Make vector (a, b, c)
	Vector3F(float a, float b, float c);

	Vector3F(const Vector3F& that);

	//! Return magnitude (lenght) of vector
	float Magnitude() const;

	//! Return square of magnitude (lenght) of vector
	float SqrMagnitude() const;

	//! Return normalized vector. Don't change this vector
	Vector3F Normalized() const;

	//! Arithmetic operations is like ordinary vector operation in math.
	/*!
	* Added special operation: Vector3F * Vector3F and Vector3F / Vector3F
	* (a1, b1, c1) * (a2, b2, c2) = (a1 * a2, b1 * b2, c1 * c2)
	* (a1, b1, c1) / (a2, b2, c2) = (a1 / a2, b1 / b2, c1 / c2)
	*/
	const Vector3F& operator=(const Vector3F& that);
	const Vector3F& operator+=(const Vector3F& that);
	const Vector3F& operator-=(const Vector3F& that);

	//! Scalar (dot) production
	static float ScalarMult(const Vector3F& a, const Vector3F& b);

	//! Vector (cross) production
	static Vector3F VectorMult(const Vector3F& a, const Vector3F& b);
};

const Vector3F& operator+(const Vector3F& that);
const Vector3F operator-(const Vector3F& that);
const Vector3F operator+(const Vector3F& a, const Vector3F& b);
const Vector3F operator*(const Vector3F& a, const Vector3F& b);
const Vector3F operator/(const Vector3F& a, const Vector3F& b);
const Vector3F operator-(const Vector3F& a, const Vector3F& b);
const Vector3F operator*(float a, const Vector3F& b);
const Vector3F operator*(const Vector3F& a, float b);
const Vector3F operator/(const Vector3F& a, float b);
const bool operator==(const Vector3F& a, const Vector3F& b);
const bool operator!=(const Vector3F& a, const Vector3F& b);


struct Vector3I
{
	int x, y, z;

	//! Make vector (0, 0, 0)
	Vector3I();

	//! Make vector (a, b, c)
	Vector3I(int a, int b, int c);

	Vector3I(const Vector3I& that);

	//! Arithmetic operations is like ordinary vector operation in math.
	/*!
	* Added special operation: Vector3F * Vector3F and Vector3F / Vector3F
	* (a1, b1, c1) * (a2, b2, c2) = (a1 * a2, b1 * b2, c1 * c2)
	* (a1, b1, c1) / (a2, b2, c2) = (a1 / a2, b1 / b2, c1 / c2)
	*/
	const Vector3I& operator=(const Vector3I& that);
	const Vector3I& operator+=(const Vector3I& that);
	const Vector3I& operator-=(const Vector3I& that);
};

const Vector3I& operator+(const Vector3I& that);
const Vector3I operator-(const Vector3I& that);
const Vector3I operator+(const Vector3I& a, const Vector3I& b);
const Vector3I operator*(const Vector3I& a, const Vector3I& b);
const Vector3I operator/(const Vector3I& a, const Vector3I& b);
const Vector3I operator-(const Vector3I& a, const Vector3I& b);
const Vector3I operator*(float a, const Vector3I& b);
const Vector3I operator*(const Vector3I& a, float b);
const Vector3I operator/(const Vector3I& a, float b);
const bool operator==(const Vector3I& a, const Vector3I& b);
const bool operator!=(const Vector3I& a, const Vector3I& b);