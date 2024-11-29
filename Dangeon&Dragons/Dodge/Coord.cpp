#include "Coord.h"

Coord::Coord(): X(-1), Y(-1)
{
}

Coord::Coord(const double X, const double Y): X(X), Y(Y)
{
}

Coord::Coord(COORD coord): X(coord.X), Y(coord.Y)
{
}

bool Coord::operator==(const Coord& other) const
{
	return (X == other.X) && (Y == other.Y);
}

bool Coord::operator!=(const Coord& other) const
{
	return !(*this == other);
}

bool Coord::operator==(const COORD& other) const
{
    return (X == other.X) && (Y == other.Y);
}

bool Coord::operator!=(const COORD& other) const
{
    return !(*this == other);
}

Coord& Coord::operator=(const Coord& other)
{
    if (this != &other) {
        X = other.X;
        Y = other.Y;
    }
    return *this;
}

Coord& Coord::operator=(const COORD& other)
{
    X = other.X;
    Y = other.Y;
    return *this;
}

Coord Coord::operator-(const Coord& other)
{
    return Coord(this->X - other.X, this->Y - other.Y);
}

Coord Coord::operator+(const Coord& other)
{
    return Coord(this->X + other.X, this->Y + other.Y);
}

Coord& Coord::operator+=(const Coord& other)
{
	X += other.X;
	Y += other.Y;
	return *this;
}

Coord& Coord::operator-=(const Coord& other)
{
	X -= other.X;
	Y -= other.Y;
	return *this;
}
