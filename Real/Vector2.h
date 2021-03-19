#pragma once
#include <math.h>

using namespace std;

class Vector2 {
public:
	float x;
	float y;

public:
	Vector2() { x = 0.0f; y = 0.0f; }
	Vector2(float X, float Y) { x = X; y = Y; }
	Vector2(const Vector2& p) { x = p.x; y = p.y; }
	~Vector2() {};

	inline Vector2 operator+(const Vector2& p) const {
		return Vector2(x + p.x, y + p.y);
	}

	inline Vector2 operator-(const Vector2& p) const {
		return Vector2(x - p.x, y - p.y);
	}

	inline Vector2 operator*(float num) const {
		return Vector2(x * num, y * num);
	}

	inline Vector2 operator/(float num) const {
		return Vector2(x / num, y / num);
	}


	static inline float diastance(const Vector2& p1, const Vector2& p2) {
		return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	}

	static inline float Cross(const Vector2& p1, const Vector2& p2) {
		return p1.x * p2.y - p1.y * p2.x;
	}

	static inline float Dot(const Vector2& p1, const Vector2& p2) {
		return p1.x * p2.x + p1.y * p2.y;
	}

	static inline Vector2 Lerp(const Vector2& p1, const Vector2& p2, float factor) {
		return p1 + (p2 - p1) * factor;
	}
};
