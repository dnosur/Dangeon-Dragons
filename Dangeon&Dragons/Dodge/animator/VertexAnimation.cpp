#include "VertexAnimation.h"
#include "../Material.h"

VertexAnimation::VertexAnimation(
	const char* title, int frameRate, bool repeat, bool stopOnEnd, 
	IGameObject* object,
	std::vector<std::pair<int, std::vector<Coord>>> frames
)
{
	copyStr(title, this->title);

	this->frameRate = frameRate;
	this->repeat = repeat;

	this->stopOnEnd = stopOnEnd;
	this->object = object;

	this->frames = frames;

	timer = new Timer();

	delay = timePassed = .0f;

	currentAnimationIndex = -1;
	play = pause = repeat = stopOnEnd = reverse = end = false;
}

void VertexAnimation::Play()
{
	Play(object->GetPos(), object->GetSize());
}

void VertexAnimation::Play(Coord coord, Size size)
{
	if (end) {
		Restart();
	}

	if (end || pause) {
		return;
	}

	timePassed += timer->GetDeltaTime();

	if (timePassed >= delay / 1000.0f) {
		timePassed = 0;

		if (!reverse) {
			currentAnimationIndex = (currentAnimationIndex + 1) % frames.size();

			if (currentAnimationIndex >= frames.size() - 1 && !repeat) {
				currentAnimationIndex = 0;
				play = false;
				end = true;
				return;
			}
		}
		else {
			if (currentAnimationIndex > 0) {
				currentAnimationIndex--;
			}
			else {
				if (!repeat) {
					play = false;
					end = true;
					return;
				}

				currentAnimationIndex = frames.size() - 1;
			}
		}

		frameSounds.Update(currentAnimationIndex);

		if (currentAnimationIndex >= 0 && currentAnimationIndex < frames.size())
		{
			// Используем ссылку на вектор, чтобы избежать создания копии
			object->GetMaterial().lock()->SetDiffuseMapVerticies(frames[currentAnimationIndex].second);
			delay = frames[currentAnimationIndex].first;
		}
	}


	play = true;
}

bool VertexAnimation::IsEnd()
{
	return end;
}

bool VertexAnimation::IsPlay()
{
	return play;
}

bool VertexAnimation::IsReverse()
{
	return reverse;
}

void VertexAnimation::Pause()
{
	pause = false;
}

void VertexAnimation::Stop()
{
	end = true;
	play = false;
	pause = false;
	currentAnimationIndex = 0;
}

void VertexAnimation::Restart()
{
	end = false;
	play = false;
	pause = false;

	currentAnimationIndex = 0;
	delay = timePassed = .0f;

	frameSounds.Restart();
}

void VertexAnimation::Reverse()
{
	reverse = !reverse;
}

char* VertexAnimation::GetFolder()
{
	return object->GetMaterial().lock()->GetDiffuseMap().lock()->path;
}

void VertexAnimation::LoadFromFolder(char* folder)
{
}

int VertexAnimation::GetFrameRate()
{
	return frameRate;
}

void VertexAnimation::SetFrameRate(int frameRate)
{
	this->frameRate = frameRate;
}

bool VertexAnimation::IsRepeat()
{
	return repeat;
}

void VertexAnimation::SetRepeat(bool repeat)
{
	this->repeat = repeat;
}

bool VertexAnimation::IsStopOnEnd()
{
	return stopOnEnd;
}

void VertexAnimation::SetStopOnEnd(bool stopOnEnd)
{
	this->stopOnEnd = stopOnEnd;
}

void VertexAnimation::SetTitle(char* title)
{
	this->title = title;
}

char* VertexAnimation::GetTitle()
{
	return title;
}

void VertexAnimation::AddFrame(int waitTime, std::vector<Coord> frames)
{
    this->frames.push_back(std::make_pair(waitTime, frames));
}

void VertexAnimation::AddFrame(std::pair<int, std::vector<Coord>> frame)
{
	this->frames.push_back(frame);
}

void VertexAnimation::ClearFrames()
{
	if (!frames.empty()) {
		this->frames.clear();
	}
}

int VertexAnimation::GetFramesCount()
{
	return frames.size();
}

IGameObject* VertexAnimation::GetGameObject()
{
	return object;
}

void VertexAnimation::SetGameObject(IGameObject* object)
{
	this->object = object;
}

IAnimation* VertexAnimation::Clone()
{
	return new VertexAnimation(*this);
}

std::pair<int, std::vector<Coord>>* VertexAnimation::operator[](int index)
{
	if (index >= 0 && index < frames.size()) {
		return &frames[index];
	}
	return nullptr;
}
