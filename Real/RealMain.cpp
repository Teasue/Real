
#include "RenderDevice.h"
#include "Rasterizer.h"
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

			//for (int i = 0; i < SCREEN_HEIGHT; i++)
				//rd.DrawPixel(SCREEN_WIDTH / 2, i);

			Point p0 = Point(0, 0);
			Point p1 = Point(120, 220);
			Point p2 = Point(700, 400);
			Point p3 = Point(700, 700);
			//rd.DrawLine(&p0, &p1);
			//rd.DrawLine(&p2, &p1);
			//rd.DrawLine(&p2, &p0);
			//rd.DrawLine(&p3, &p0);
			//rd.ScanLineDrawTriangle(&p2, &p1, &p0);
			//rd.BarycentricTriangle(&p2, &p1, &p0);
			rd.LoadObjFile();

			SDL_RenderPresent(rd.gRenderer);
		}
	}

	rd.SDLClose();

	return 0;
}