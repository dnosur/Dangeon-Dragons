#include "FrameSound.h"

FrameSound::FrameSound()
{
	frame = playCount = repeatCount= -1;
	repeat = false;
}

FrameSound::FrameSound(int frame, Audio audio, bool repeat, int repeatCount)
{
	this->frame = frame;
	this->audio = audio;
	this->repeat = repeat;
	this->repeatCount = repeatCount;
	playCount = 0;
}

bool FrameSound::operator==(const FrameSound& other) const
{
	return frame == other.frame && audio == other.audio 
		&& repeat == other.repeat && playCount == other.playCount &&
		repeatCount == other.repeatCount;
}

bool FrameSound::operator!=(const FrameSound& other) const
{
	return !(*this == other);
}

FrameSound& FrameSound::operator=(const FrameSound& other)
{
	if (this != &other) {
		frame = other.frame;
		audio = other.audio;
		repeat = other.repeat;
		playCount = other.playCount;
		repeatCount = other.repeatCount;
	}
	return *this;
}
