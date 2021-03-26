#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Color.h"
#include "Const.h"

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
	void DrawLine(int x0, int y0, int x1, int y1, Color c = C_WRITE);
};

