#pragma once
#include <windows.h>

struct Coord
{
    Coord();
    Coord(const double X, const double Y);
    Coord(COORD coord);

    double X, Y;

    bool operator==(const Coord& other) const;
    bool operator!=(const Coord& other) const;

    bool operator==(const COORD& other) const;
    bool operator!=(const COORD& other) const;

    Coord& operator=(const Coord& other);
    Coord& operator=(const COORD& other);

    Coord operator-(const Coord& other);
	Coord operator+(const Coord& other);

    Coord& operator+=(const Coord& other);
	Coord& operator-=(const Coord& other);
};