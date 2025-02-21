#pragma once
#include <memory>

struct Coord;

class Offset
{
	std::unique_ptr<Coord> offset;
public:
	Offset(std::unique_ptr<Coord> offset = std::make_unique<Coord>(0, 0));
	~Offset() = default;

	void SetOffset(std::unique_ptr<Coord> offset);
	void Clear();

	Coord* GetOffset();

	void operator +=(Coord& coord);
	void operator -=(Coord& coord);
};