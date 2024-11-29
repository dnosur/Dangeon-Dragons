#include "Tile.h"

Tile::Tile()
{
	id = -1;
	collision = nullptr;
}

Tile::Tile(int id, ICollision* collision)
{
	this->id = id;
	this->collision = collision;
}

int Tile::GetId()
{
	return id;
}

ICollision* Tile::GetCollision()
{
	return collision;
}

bool Tile::Undefined()
{
	return id == -1 && collision == nullptr;
}

bool Tile::operator==(const Tile& other) const
{
	return id == other.id && collision == other.collision;
}

bool Tile::operator!=(const Tile& other) const
{
	return !(*this == other);
}

Tile& Tile::operator=(const Tile& other)
{
	if (this == &other) {
		return *this;
	}

	id = other.id;
	collision = other.collision;
	return *this;
}
