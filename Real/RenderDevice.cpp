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

void RenderDevice::DrawPixel(int x, int y, Color c) {
	// 从左下角开始
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawPoint(gRenderer, x, SCREEN_HEIGHT - 1 - y);
}

void RenderDevice::DrawLine(Point* p0, Point* p1, Color c){
	if (!CohenSutherlandLineClip(p0, p1, c))
		return;

	int x, y, tem = 0;
	int x0 = p0->x;
	int y0 = p0->y;
	int x1 = p1->x;
	int y1 = p1->y;

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

		if (dx >= dy) {
			if (x0 > x1){
				swap(x0, x1);
				swap(y0, y1);
			}
			
			for (x = x0, y = y0; x <= x1; x++) {
				DrawPixel(x, y, c);
				tem += dy;
				if (tem >= dx) {
					tem -= dx;
					y += (y1 >= y0) ? 1 : -1;
				}
			}
		}
		else {
			if (y0 > y1) {
				swap(x0, x1);
				swap(y0, y1);
			}

			for (y = y0, x = x0; y <= y1; y++) {
				DrawPixel(x, y, c);
				tem += dx;
				if (tem >= dy) {
					tem -= dy;
					x += (x1 >= x0) ? 1 : -1;
				}
			}
		}

		DrawPixel(x1, y1, c);
	}
}

void RenderDevice::ScanLineDrawTriangle(Point* p0, Point* p1, Point* p2, Color c)
{
	if (p0->y < p1->y)
		swap(p0, p1);

	if (p0->y < p2->y)
		swap(p0, p2);
	
	if (p1->y < p2->y)
		swap(p1, p2);

	if (p1->y == p2->y)
		FillBottomTriangle(p0, p1, p2, c);
	else if (p0->y == p1->y)
		FillTopTriangle(p0, p1, p2, c);
	else {
		int x3 = p0->x + (float)(p1->y - p0->y) / (p2->y - p0->y) * (p2->x - p0->x);
		Point p3(x3, p1->y);
		FillBottomTriangle(p0, p1, &p3, c);
		FillTopTriangle(p1, &p3, p2, c);
	}
}

void RenderDevice::BarycentricTriangle(Point* p0, Point* p1, Point* p2, Color c){
	Vector2 bbmin(INFINITY, INFINITY);
	Vector2 bbmax(FLT_EPSILON, FLT_EPSILON);
	Vector2 clamp(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

	bbmin.x = fmax(0.f, fmin(bbmin.x, p0->x));
	bbmin.y = fmax(0.f, fmin(bbmin.y, p0->y));
	bbmax.x = fmin(clamp.x, fmax(bbmax.x, p0->x));
	bbmax.y = fmin(clamp.y, fmax(bbmax.y, p0->y));

	bbmin.x = fmax(0.f, fmin(bbmin.x, p1->x));
	bbmin.y = fmax(0.f, fmin(bbmin.y, p1->y));
	bbmax.x = fmin(clamp.x, fmax(bbmax.x, p1->x));
	bbmax.y = fmin(clamp.y, fmax(bbmax.y, p1->y));

	bbmin.x = fmax(0.f, fmin(bbmin.x, p2->x));
	bbmin.y = fmax(0.f, fmin(bbmin.y, p2->y));
	bbmax.x = fmin(clamp.x, fmax(bbmax.x, p2->x));
	bbmax.y = fmin(clamp.y, fmax(bbmax.y, p2->y));

	Point p;
	for (p.x = bbmin.x; p.x <= bbmax.x; p.x++) {
		for (p.y = bbmin.y; p.y <= bbmax.y; p.y++) {
			Vector3 _p = BarycentricPoint(p0, p1, p2, &p);
			if (_p.x < 0 || _p.y < 0 || _p.z < 0)
				continue;

			DrawPixel(p.x, p.y);
		}
	}
}

bool RenderDevice::CohenSutherlandLineClip(Point* p0, Point* p1, Color c){
	Point lb = Point(0, 0);
	Point rt = Point(SCREEN_WIDTH, SCREEN_HEIGHT);

	int x0 = p0->x;
	int y0 = p0->y;
	int x1 = p1->x;
	int y1 = p1->y;

	float k = float(y1 - y0) / (x1 - x0);

	int code0 = CohenSutherEncode(p0, &lb, &rt);
	int code1 = CohenSutherEncode(p1, &lb, &rt);

	bool flag = false;

	while (true) {
		if (!(code0 | code1)){
			flag = true;
			break;
		}
		else if(code0 & code1)
			break;
		else {
			float x, y;
			int code = code0 ? code0 : code1;
			
			if (code & LINE_LEFT) {
				x = lb.x;
				y = y0 + k * (x - x0);
			}
			else if (code & LINE_BOTTOM) {
				y = lb.y;
				x = x0 + (y - y0) / k;
			}
			else if (code & LINE_RIGHT) {
				x = rt.x;
				y = y0 + k * (x - x0);
			}
			else if (code & LINE_TOP) {
				y = rt.y;
				x = x0 + (y - y0) / k;
			}

			if (code == code0) {
				x0 = x;
				y0 = y;
				Point p(x0, y0);
				code0 = CohenSutherEncode(&p, &lb, &rt);
			}
			else {
				x1 = x;
				y1 = y;
				Point p(x1, y1);
				code1 = CohenSutherEncode(&p, &lb, &rt);
			}
		}
	}

	if (flag) {
		p0->x = x0;
		p0->y = y0;
		p1->x = x1;
		p1->y = y1;
	}

	return flag;
}

int RenderDevice::CohenSutherEncode(Point* p, Point* lb, Point* rt){
	int code = LINE_INSIDE;

	if (p->x < lb->x)
		code |= LINE_LEFT;
	else if (p->y < lb->y)
		code |= LINE_BOTTOM;
	else if (p->x > rt->x)
		code |= LINE_RIGHT;
	else if (p->y > rt->y)
		code |= LINE_TOP;

	return code;
}

void RenderDevice::FillBottomTriangle(Point* p0, Point* p1, Point* p2, Color c){
	float k01 = (float)(p0->x - p1->x) / (p0->y - p1->y);
	float k02 = (float)(p0->x - p2->x) / (p0->y - p2->y);

	float scanX0 = p0->x;
	float scanX1 = p0->x;
	Point _p0, _p1;

	for (int scanY = p0->y; scanY >= p1->y; scanY--) {
		_p0.x = (int)scanX0;
		_p0.y = scanY;
		_p1.x = (int)scanX1;
		_p1.y = scanY;
		DrawLine(&_p0, &_p1, c);
		scanX0 -= k01;
		scanX1 -= k02;
	}
}

void RenderDevice::FillTopTriangle(Point* p0, Point* p1, Point* p2, Color c){
	float k12 = (float)(p2->x - p1->x) / (p2->y - p1->y);
	float k02 = (float)(p0->x - p2->x) / (p0->y - p2->y);

	float scanX0 = p2->x;
	float scanX1 = p2->x;
	Point _p0, _p1;

	for (int scanY = p2->y; scanY <= p0->y; scanY++) {
		_p0.x = (int)scanX0;
		_p0.y = scanY;
		_p1.x = (int)scanX1;
		_p1.y = scanY;
		DrawLine(&_p0, &_p1, c);
		scanX1 += k12;
		scanX0 += k02;
	}
}

Vector3 RenderDevice::BarycentricPoint(Point* p0, Point* p1, Point* p2, Point* p){
	Vector3 s0(p2->x - p0->x, p1->x - p0->x, p0->x - p->x);
	Vector3 s1(p2->y - p0->y, p1->y - p0->y, p0->y - p->y);
	Vector3 u = Vector3::Cross(s0, s1);
	
	if (abs(u.z) < 1)
		return Vector3(-1, 1, 1);

	return Vector3(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

