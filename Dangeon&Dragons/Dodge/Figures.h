#pragma once

#include <corecrt_math_defines.h>
#include <cmath>

#include "Color.h"
#include "Coord.h"

#include "raycast/Ray.h"

void drawCircle(float cx, float cy, float r, int num_segments);

void drawRectangle(float x1, float y1, float x2, float y2);

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

void drawLine(Coord a, Coord b, Color color = Color(1, 1, 1), int lineWidth = 1);
void drawRay(Ray*& ray, Color& color);