#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "RenderDevice.h"
#include "Const.h"


int main(int argc, char* args[]){
	RenderDevice rd;

	if (!rd.SDLInit()){
		printf("Failed to initialize!\n");
	}
	else{
		bool quit = false;
		SDL_Event e;

		while (!quit){
			while (SDL_PollEvent(&e) != 0){
				if (e.type == SDL_QUIT)
					quit = true;
			}

			SDL_SetRenderDrawColor(rd.gRenderer, 0, 0, 0, 0xFF);
			SDL_RenderClear(rd.gRenderer);

			for (int i = 0; i < SCREEN_HEIGHT; i++)
				rd.DrawPixel(SCREEN_WIDTH / 2, i);

			rd.DrawLine(0, 0, 100, 200);
			rd.DrawLine(200, 200, 600, 400);

			SDL_RenderPresent(rd.gRenderer);
		}
	}

	rd.SDLClose();

	return 0;
}