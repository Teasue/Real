#pragma once
#include <math.h>
#include "Vector3.h"

using namespace std;

class Vector4 {
public:
	float x;
	float y;
	float z;
	float w;
	Vector3 xyz;

public:
	Vector4() : x(0), y(0), z(0), w(0) {};

	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){
		xyz.x = x;
		xyz.y = y;
		xyz.z = z;
	};

	Vector4(Vector4& vec, float w) : x(vec.x), y(vec.y), z(vec.z), w(w){
		xyz.x = x;
		xyz.y = y;
		xyz.z = z;
	};

	~Vector4() {};

	inline Vector4 operator+(const Vector4& v) const {
		return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	inline Vector4 operator-(const Vector4& v) const {
		return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	inline Vector4 operator*(float num) const {
		return Vector4(x * num, y * num, z * num, w * num);
	}

	inline Vector4 operator/(float num) const {
		return Vector4(x / num, y / num, z / num, w / num);
	}


	static inline Vector4 Lerp(const Vector4& v1, const Vector4& v2, float factor)
	{
		return v1 + (v2 - v1) * factor;
	}
};