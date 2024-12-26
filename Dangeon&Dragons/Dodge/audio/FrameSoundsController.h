#pragma once
#include <vector>

#include "FrameSound.h"

class FrameSoundsController
{
	boost::container::vector<FrameSound> frameSounds;

public:
	FrameSoundsController();
	FrameSoundsController(boost::container::vector<FrameSound> frameSounds);

	void Update(int currentFrame);

	void SetFrameSounds(boost::container::vector<FrameSound> frameSounds);

	boost::container::vector<FrameSound> GetFrameSounds();
	int GetFrameSoundsSize();

	void Restart();
	void Clear();
};