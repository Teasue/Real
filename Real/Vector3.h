#pragma once
#include <math.h>

using namespace std;

class Vector3 {
public:
	float x;
	float y;
	float z;

public:
	Vector3() { x = 0.0f; y = 0.0f; z = 0.0f; }
	Vector3(float X, float Y, float Z){
		x = X; y = Y; z = Z;
	}

	Vector3(const Vector3& v) {
		x = v.x; y = v.y; z = v.z;
	}

	~Vector3() {};

	inline Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	inline Vector3 operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline Vector3 operator*(float num) const {
		return Vector3(x * num, y * num, z * num);
	}

	inline Vector3 operator/(float num) const {
		return Vector3(x / num, y / num, z / num);
	}

	inline float Length() const{
		return sqrt(x * x + y * y + z * z);
	}

	inline Vector3 Normalize() const{
		float len = this->Length();
		return Vector3(x / len, y / len, z / len);
	}


	static inline float diastance(const Vector3& v1, const Vector3& v2) {
		return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2));
	}

	static inline Vector3 Cross(const Vector3& v1, const Vector3& v2) {
		return Vector3(v1.y * v2.z - v1.z * v2.x,
				v1.z * v2.x - v1.x * v2.z,
				v1.x * v2.y - v1.y * v2.x);
	}

	static inline float Dot(const Vector3& v1, const Vector3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	static inline Vector3 Lerp(const Vector3& v1, const Vector3& v2, float factor) {
		return v1 + (v2 - v1) * factor;
	}
};