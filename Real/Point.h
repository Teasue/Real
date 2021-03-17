#pragma once
#include <math.h>

using namespace std;

class Point{
public:
	float x;
	float y;

public:
	inline Point() { x = 0.0f; y = 0.0f; }
	inline Point(float X, float Y) { x = X; y = Y; }
	inline Point(const Point& p) { x = p.x; y = p.y; }
	virtual ~Point();

	inline Point operator+(const Point& p) const {
		return Point(x + p.x, y + p.y);
	}
	inline Point operator-(const Point& p) const {
		return Point(x - p.x, y - p.y);
	}
	inline Point operator*(float num) const {
		return Point(x * num, y * num);
	}
	inline Point operator/(float num) const {
		return Point(x / num, y / num);
	}

	static inline float diastance(const Point& p1, const Point& p2) {
		return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	}
	static inline float Cross(const Point& p1, const Point& p2) {
		return p1.x * p2.y - p1.y * p2.x;
	}
	static inline float Dot(const Point& p1, const Point& p2) {
		return p1.x * p2.x + p1.y * p2.y;
	}
	static inline Point Lerp(const Point& p1, const Point& p2, float factor) {
		return p1 + (p2 - p1) * factor;
	}
};
