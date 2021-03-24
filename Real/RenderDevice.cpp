#include "RenderDevice.h"
#include "Const.h"



bool RenderDevice::SDLInit() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			printf("Warning: Linear texture filtering not enabled!");

		gWindow = SDL_CreateWindow("Real Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
		}
	}

	return success;
}

void RenderDevice::SDLClose(){
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	SDL_Quit();
}

void RenderDevice::DrawPixel(int x, int y, Color c = C_WRITE) {
	// 从左下角开始
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawPoint(gRenderer, x, SCREEN_HEIGHT - 1 - y);
}

void RenderDevice::DrawLine(int x0, int y0, int x1, int y1, Color c = C_WRITE){
	int x, y;

	if (x0 == x1) {
		int offset = y0 >= y1 ? -1 : 1;
		for (y = y0; y != y1; y += offset)
			DrawPixel(x0, y, c);

		DrawPixel(x1, y1, c);
	}
	else if (y0 == y1) {
		int offset = x0 >= x1 ? -1 : 1;
		for (x = x0; x != x1; x += offset)
			DrawPixel(x, y0, c);

		DrawPixel(x1, y1, c);
	}
	else {
		int dx = x0 > x1 ? x0 - x1 : x1 - x0;
		int dy = y0 > y1 ? y0 - y1 : y1 - y0;
	}
}
