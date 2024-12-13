#pragma once
#include "Audio.h"

struct FrameSound
{
	int frame, playCount, repeatCount;
	bool repeat;

	Audio audio;

	FrameSound();
	FrameSound(int frame, Audio audio, bool repeat = false, int repeatCount = 0);

	bool operator==(const FrameSound& other) const;
	bool operator!=(const FrameSound& other) const;

	FrameSound& operator=(const FrameSound& other);
};