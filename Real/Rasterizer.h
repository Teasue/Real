#pragma once
#include "Color.h"
#include "Vector2.h"
#include "RenderDevice.h"

using namespace std;

class Rasterizer {
private:

public:
	Rasterizer(RenderDevice* pcontext);
	~Rasterizer() {};

	void DrawPixel(int x, int y, Color& c);
	void DrawLine(const Color& c1, const Vector2& v1, const Color& c2, const Vector2& v2);
};