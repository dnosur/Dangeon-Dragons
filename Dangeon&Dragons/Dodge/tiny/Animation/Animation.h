#pragma once
#include <tinyxml2.h>
#include <vector>

#include "Frame.h"

class Animation
{
	std::vector<Frame> frames;
public:
	Animation();
	Animation(std::vector<Frame> frames);
	Animation(tinyxml2::XMLElement* animtion);
	~Animation();

	static void LoadAnimations(tinyxml2::XMLElement* animtion, std::vector<Frame>& frames);

	std::vector<Frame>::iterator begin();
	std::vector<Frame>::iterator end();

	void AddFrame(Frame frame);
	void SetFrames(std::vector<Frame> frames);

	int FrameCount();

	Frame* operator[](int index);
};