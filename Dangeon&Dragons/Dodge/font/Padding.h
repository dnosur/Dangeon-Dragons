#pragma once
#include "../Coord.h"

struct Padding
{
	float left, top, right, bottom;

	Padding();
	Padding(float left, float top, float right, float bottom);

	void Use(float& x, float& y);
	void Use(Coord& pos);
};