#include "Coord.h"

Coord::Coord(): X(0), Y(0), Z(0)
{
}

constexpr Coord::Coord(const double X, const double Y, const double Z)
    : X(X), Y(Y), Z(Z)
{
}

constexpr Coord::Coord(COORD coord): X(coord.X), Y(coord.Y), Z(0)
{
}

bool Coord::operator==(const Coord& other) const
{
	return (X == other.X) && (Y == other.Y) && (Z == other.Z);
}

bool Coord::operator!=(const Coord& other) const
{
	return !(*this == other);
}

bool Coord::operator==(const Vec2& other) const
{
    return (X == other.x) && (Y == other.y);
}

bool Coord::operator!=(const Vec2& other) const
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
		Z = other.Z;
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
    return Coord(this->X - other.X, this->Y - other.Y, this->Z - other.Z);
}

Coord Coord::operator+(const Coord& other)
{
    return Coord(this->X + other.X, this->Y + other.Y, this->Z + other.Z);
}

Coord& Coord::operator+=(const Coord& other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
	return *this;
}

Coord& Coord::operator-=(const Coord& other)
{
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
	return *this;
}

Coord* Coord::operator*(const double& other)
{
    return new Coord(X * other, Y * other, Z * other);
}
