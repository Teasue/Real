#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Color.h"
#include "Const.h"
#include "Vector2.h"

class RenderDevice{
public:
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

public:
	RenderDevice() {
		gWindow = NULL;
		gRenderer = NULL;
	};
	~RenderDevice() {};

	bool SDLInit();
	void SDLClose();

	void DrawPixel(int x, int y, Color c = C_WRITE);
	void DrawLine(Point* p0, Point* p1, Color c = C_WRITE);
	bool CohenSutherlandLineClip(Point* p0, Point* p1, Color c = C_WRITE);
	int CohenSutherEncode(Point* p, Point* lb, Point* rt);
};

