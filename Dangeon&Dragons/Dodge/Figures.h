#pragma once

#include <GLFW/glfw3.h>
#include <corecrt_math_defines.h>
#include <cmath>

void drawCircle(float cx, float cy, float r, int num_segments);

void drawRectangle(float x1, float y1, float x2, float y2);

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
