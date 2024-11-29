#pragma once
#include <vector>

#include "FrameSound.h"

class FrameSoundsController
{
	std::vector<FrameSound> frameSounds;

public:
	FrameSoundsController();
	FrameSoundsController(std::vector<FrameSound> frameSounds);

	void Update(int currentFrame);

	void SetFrameSounds(std::vector<FrameSound> frameSounds);

	std::vector<FrameSound> GetFrameSounds();
	int GetFrameSoundsSize();

	void Restart();
	void Clear();
};