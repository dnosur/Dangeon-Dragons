#include "Tile.h"

Tile::Tile()
{
	id = -1;
	collision = nullptr;
}

Tile::Tile(int id, std::shared_ptr<ICollision> collision, std::shared_ptr<Animation> animation)
{
	this->id = id;
	this->collision = collision;
	this->animation = animation;
}

int Tile::GetId()
{
	return id;
}

std::weak_ptr<ICollision> Tile::GetCollision()
{
	return collision;
}

std::weak_ptr<Animation> Tile::GetAnimation()
{
	return animation;
}

TilesetPropertiesController* Tile::GetTilesetProperties()
{
	return &tilesetProperties;
}

void Tile::SetTilesetProperties(TilesetPropertiesController tilesetProperties)
{
	this->tilesetProperties = tilesetProperties;
}

bool Tile::Undefined()
{
	return id == -1 && collision == nullptr;
}

bool Tile::operator==(const Tile& other) const
{
	return id == other.id && collision == other.collision && 
		animation == other.animation;
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
	animation = other.animation;
	return *this;
}
