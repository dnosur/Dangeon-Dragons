#include "Character.h"

Character::Character()
{
	textureId = -1;
	advance = -1;
}

Character::Character(GLuint textureId, Size size, Size bearing, GLuint advance)
{
	this->textureId = textureId;
	this->size = size;
	this->bearing = bearing;
	this->advance = advance;
}

Character::~Character()
{
}

bool Character::operator==(const Character& other) const
{
	return textureId == other.textureId && size == other.size && 
		bearing == other.bearing && advance == other.advance;
}

bool Character::operator!=(Character& other)
{
	return !(*this == other);
}

Character& Character::operator=(Character& other)
{
	if (this == &other) return *this;
	textureId = other.textureId;
	size = other.size;
	bearing = other.bearing;
	advance = other.advance;
	return *this;
}
