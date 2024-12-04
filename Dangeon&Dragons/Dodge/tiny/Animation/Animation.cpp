#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(std::vector<Frame> frames)
{
	this->frames = frames;
}

Animation::Animation(tinyxml2::XMLElement* animtion)
{
	LoadAnimations(animtion, frames);
}

Animation::~Animation()
{
}

void Animation::LoadAnimations(tinyxml2::XMLElement* animtion, std::vector<Frame>& frames)
{
	if (animtion == nullptr) {
		return;
	}

	for (
		tinyxml2::XMLElement* frame = animtion->FirstChildElement("frame"); 
		frame; 
		frame = frame->NextSiblingElement("frame")
		)
	{
		Frame frameData;
		frameData.tileId = frame->IntAttribute("tileid");
		frameData.duration = frame->IntAttribute("duration");
		frames.push_back(frameData);
	}
}

std::vector<Frame>::iterator Animation::begin()
{
	return frames.begin();
}

std::vector<Frame>::iterator Animation::end()
{
	return frames.end();
}

void Animation::AddFrame(Frame frame)
{
	frames.push_back(frame);
}

void Animation::SetFrames(std::vector<Frame> frames)
{
	if (frames.size()) {
		this->frames.clear();
	}
	this->frames = frames;
}

int Animation::FrameCount()
{
	return frames.size();
}

Frame* Animation::operator[](int index)
{
	if (index < frames.size()) {
		return &frames[index];
	}
	return nullptr;
}
