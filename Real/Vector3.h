#pragma once
#include <math.h>
#include "Point.h"

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
	~Vector3();

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
};