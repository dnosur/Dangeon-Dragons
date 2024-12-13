#pragma once
#include "../Coord.h"
#include "../Size.h"

struct Coord;
struct Size;

struct Vec2
{
    float x, y;

    Vec2();
    Vec2(float x, float y);

    Vec2(Coord coord);
    Vec2(Size size);

    bool operator==(const Vec2& other) const;
    bool operator!=(const Vec2& other) const;

    bool operator==(const Coord& other) const;
    bool operator!=(const Coord& other) const;

    Vec2 operator-(const Vec2& other) const;

    Vec2 operator/(float value) const;

    Vec2 operator=(const Vec2& other);
    Vec2 operator=(const Coord& other);
};

