#include "Frame.h"

Frame::Frame()
{
	tileId = -1;
	duration = 0;
}

Frame::Frame(int tileId, float duration)
{
	this->tileId = tileId;
	this->duration = duration;
}

bool Frame::operator==(const Frame& other) const
{
	return tileId == other.tileId && duration == other.duration;
}

bool Frame::operator!=(const Frame& other) const
{
	return !(*this == other);
}

Frame& Frame::operator=(const Frame& other)
{
	if (this != &other)
	{
		tileId = other.tileId;
		duration = other.duration;
	}
	return *this;
}
