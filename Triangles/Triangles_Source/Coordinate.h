#pragma once
#include <cmath>
namespace Vector {

	const double EPS = 0.000001;

	template <typename T>
	struct Vector3
	{
		T x, y, z;
	
		//! Make vector (0, 0, 0)
		Vector3(): 
			x(0), y(0), z(0) {}

		//! Make vector (a, b, c)
		Vector3(T a, T b, T c):
			x(a), y(b), z(c) {}

		Vector3(const Vector3& that):
			x(that.x), y(that.y), z(that.z) {}

		//! Return magnitude (lenght) of vector
		T Magnitude() const {
			return std::sqrt(SqrMagnitude());
		}

		//! Return square of magnitude (lenght) of vector
		T SqrMagnitude() const {
			return x * x + y * y + z * z;
		}

		//! Return normalized vector. Don't change this vector
		Vector3 Normalized() const {
			T magn = Magnitude();
			return std::abs(magn) <= EPS ? *this : *this / magn;
		}

		const Vector3& operator+=(const Vector3& that) {
			x += that.x;
			y += that.y;
			z += that.z;
			return *this;
		}
		const Vector3& operator-=(const Vector3& that) {
			*this += -that;
			return *this;
		}
	};

	//! Scalar (dot) production
	template <typename T> T ScalarMult(const Vector3<T>& a, const Vector3<T>& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	//! Vector (cross) production
	template <typename T> Vector3<T> VectorMult(const Vector3<T>& a, const Vector3<T>& b) {
		T x = a.y * b.z - b.y * a.z;
		T y = b.x * a.z - a.x * b.z;
		T z = a.x * b.y - b.x * a.y;
		return Vector3<T>(x, y, z);
	}

	//! Arithmetic operations is like ordinary vector operation in math.
	/*!
	* Added special operation: Vector3 * Vector3 and Vector3 / Vector3
	* (a1, b1, c1) * (a2, b2, c2) = (a1 * a2, b1 * b2, c1 * c2)
	* (a1, b1, c1) / (a2, b2, c2) = (a1 / a2, b1 / b2, c1 / c2)
	*/

	template <typename T> const Vector3<T> operator-(const Vector3<T>& that) {
			Vector3<T> new_vec(-that.x, -that.y, -that.z);
			return new_vec;
	}

	template <typename T> const Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b) {
		return Vector3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	template <typename T> const Vector3<T> operator*(const Vector3<T>& a, const Vector3<T>& b) {
		return Vector3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
	}
	template <typename T> const Vector3<T> operator/(const Vector3<T>& a, const Vector3<T>& b) {
		return Vector3<T>(a.x / b.x, a.y / b.y, a.z / b.z);
	}
	template <typename T> const Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b) {
		return Vector3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	template <typename T> const Vector3<T> operator*(T a, const Vector3<T>& b) {
		return Vector3<T>(a * b.x, a * b.y, a * b.z);
	}
	template <typename T> const Vector3<T> operator*(const Vector3<T>& a, T b) {
		return b * a;
	}
	template <typename T> const Vector3<T> operator/(const Vector3<T>& a, T b) {
		return Vector3<T>(a.x / b, a.y / b, a.z / b);
	}
	template <typename T> const bool operator==(const Vector3<T>& a, const Vector3<T>& b) {
		return a.x == b.x && a.y == b.y && a.z == b.z;
	}
	template <typename T> const bool operator!=(const Vector3<T>& a, const Vector3<T>& b) {
		return !(a == b);
	}
}