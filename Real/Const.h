#pragma once
#include <stdint.h>
#include <string>
#include "Color.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const Color C_WRITE = Color(1, 1, 1, 1);

const int LINE_INSIDE = 0;
const int LINE_LEFT = 1;
const int LINE_RIGHT = 2;
const int LINE_BOTTOM = 4;
const int LINE_TOP = 8;

const float PROJECTION_VIEW_F = 1000;
const float PROJECTION_VIEW_N = 0.3;