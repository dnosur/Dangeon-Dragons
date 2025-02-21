#include "Offset.h"
#include "../Coord.h"

Offset::Offset(std::unique_ptr<Coord> offset)
	: offset(std::move(offset))
{
}

void Offset::SetOffset(std::unique_ptr<Coord> offset)
{
	this->offset = std::move(offset);
}

void Offset::Clear()
{
	offset->X = offset->Y = 0;
}

Coord* Offset::GetOffset()
{
	return offset.get();
}

void Offset::operator+=(Coord& coord)
{
	*offset += coord;
}

void Offset::operator-=(Coord& coord)
{
	*offset -= coord;
}
