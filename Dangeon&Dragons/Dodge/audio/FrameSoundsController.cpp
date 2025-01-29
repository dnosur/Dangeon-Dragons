#include "FrameSoundsController.h"

FrameSoundsController::FrameSoundsController()
{
}

FrameSoundsController::FrameSoundsController(std::vector<FrameSound> frameSounds)
{
}

void FrameSoundsController::Update(int currentFrame)
{
	for (FrameSound& item : frameSounds) {
		if (item.frame != currentFrame) {
			continue;
		}

		if (!item.repeat && item.playCount > 0) {
			continue;
		}

		if (item.repeat && item.playCount >= item.repeatCount) {
			continue;
		}

		item.audio.Play();
	}
}

void FrameSoundsController::SetFrameSounds(std::vector<FrameSound> frameSounds)
{
	if (!frameSounds.size()) {
		return;
	}

	Clear();
	for (FrameSound& frame : frameSounds) {
		this->frameSounds.push_back(frame);
	}
}

std::vector<FrameSound> FrameSoundsController::GetFrameSounds()
{
	return frameSounds;
}

int FrameSoundsController::GetFrameSoundsSize()
{
	return frameSounds.size();
}

void FrameSoundsController::Restart()
{
	for (FrameSound& item : frameSounds) {
		item.playCount = 0;
	}
}

void FrameSoundsController::Clear()
{
	if (!frameSounds.size()) {
		return;
	}
	frameSounds.clear();
}
