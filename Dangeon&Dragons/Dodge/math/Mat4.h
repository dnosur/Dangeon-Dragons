#pragma once
#include "Vec2.h"
#include "../Coord.h"

struct Mat4 {
    float elements[16];

    Mat4();

    static Mat4 Identity();

    static Mat4 Translate(const Vec2& position);
    static Mat4 Translate(const Coord& position);

    static Mat4 Ortho(float left, float right, float bottom, float top);
};