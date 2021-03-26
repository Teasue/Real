#pragma once
#include <stdint.h>

using namespace std;

class Color {
public:
	float r, g, b, a;

	Color() : r(0), g(0), b(0), a(0) {};
	Color(float r, float g, float b, float a = 1) {
		r = r;
		g = g;
		b = b;
		a = a;
	};
	Color(const Color& color) {
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	};
	~Color() {};

	uint8_t  ToUInt32() const;
	inline Color operator + (const Color& c) const {
		return Color(r + c.r, g + c.g, b + c.b, a + c.a);
	};
	inline Color operator - (const Color& c) const {
		return Color(r - c.r, g - c.g, b - c.b, a - c.a);
	};
	Color operator * (float f) const
	{
		return Color(r * f, g * f, b * f, a * f);

	}
};