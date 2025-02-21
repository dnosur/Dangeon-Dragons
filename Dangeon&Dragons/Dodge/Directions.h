#pragma once
struct Coord;

enum Directions {
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};

Directions GetDirection(Coord& direction);