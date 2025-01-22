#pragma once
#include <windows.h>

#include "math/Vec2.h"

struct Vec2;

struct alignas(16) Coord
{
    Coord();

    constexpr Coord(const double X, const double Y, const double Z = 0.0);
    constexpr Coord(COORD coord);

    double X, Y, Z;

    bool operator==(const Coord& other) const;
    bool operator!=(const Coord& other) const;

    bool operator==(const Vec2& other) const;
	bool operator!=(const Vec2& other) const;

    bool operator==(const COORD& other) const;
    bool operator!=(const COORD& other) const;

    Coord& operator=(const Coord& other);
    Coord& operator=(const COORD& other);

    Coord operator-(const Coord& other);
	Coord operator+(const Coord& other);

    Coord& operator+=(const Coord& other);
	Coord& operator-=(const Coord& other);

    Coord* operator*(const double& other);
};