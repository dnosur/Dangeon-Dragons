#include "SpriteAnimationController.h"

SpriteAnimation* SpriteAnimationController::GetByTitle(std::string_view title)
{
	for (SpriteAnimation& animation : animations) {
		if (animation.GetTitle() == title) {
			return &animation;
		}
	}
	return nullptr;
}

SpriteAnimation* SpriteAnimationController::GetByTitle(std::string_view title, int& index)
{
	index = 0;
	for (SpriteAnimation& animation : animations) {
		if (animation.GetTitle() == title) {
			return &animation;
		}
		index++;
	}
	index = -1;
	return nullptr;
}

SpriteAnimation* SpriteAnimationController::GetByIndex(int index)
{
	if (index < 0 || index >= animations.size()) {
		return nullptr;
	}
	return &animations[index];
}

SpriteAnimationController::SpriteAnimationController()
{
	currentIndex = -1;
}

SpriteAnimationController::SpriteAnimationController(std::vector<SpriteAnimation> animations)
{
	this->animations = animations;
	currentIndex = -1;
}

void SpriteAnimationController::AddAnimation(SpriteAnimation animation)
{
	SpriteAnimation* same = GetByTitle(animation.GetTitle());
	if (same == nullptr) {
		animations.push_back(animation);
		return;
	}
	*same = animation;
}

void SpriteAnimationController::AddAnimations(std::vector<SpriteAnimation> animations)
{
	for (SpriteAnimation& animation : animations) {
		AddAnimation(animation);
	}
}

void SpriteAnimationController::Play(int index)
{
	SpriteAnimation* animation = GetByIndex(index);
	if (animation != nullptr) {
		animation->Play();
		currentIndex = index;
	}
}

void SpriteAnimationController::Play(int index, Coord pos, Size size)
{
	SpriteAnimation* animation = GetByIndex(index);
	if (animation != nullptr) {
		animation->Play(pos, size);
		currentIndex = index;
	}
}

void SpriteAnimationController::PlayOnEnd(int index)
{
	if (!IsAnimationEnd()) {
		return;
	}

	Play(index);
}

void SpriteAnimationController::PlayOnEnd(int index, Coord pos, Size size)
{
	if (!IsAnimationEnd()) {
		return;
	}

	Play(index, pos, size);
}

void SpriteAnimationController::Play(std::string_view title)
{
	SpriteAnimation* animation = GetByTitle(title, currentIndex);
	
	if (animation != nullptr) {
		animation->Play();
	}
}

void SpriteAnimationController::Play(std::string_view title, Coord pos, Size size)
{
	SpriteAnimation* animation = GetByTitle(title, currentIndex);

	if (animation != nullptr) {
		animation->Play(pos, size);
	}
}

void SpriteAnimationController::PlayOnEnd(std::string_view title)
{
	if (!IsAnimationEnd()) {
		return;
	}

	Play(title);
}

void SpriteAnimationController::PlayOnEnd(std::string_view title, Coord pos, Size size)
{
	if (!IsAnimationEnd()) {
		return;
	}

	Play(title, pos, size);
}

void SpriteAnimationController::PlayAll()
{
	for (SpriteAnimation& animation : animations) {
		animation.Play();
	}
}

int SpriteAnimationController::GetSize()
{
	return animations.size();
}

int SpriteAnimationController::GetCurrentIndex()
{
	return currentIndex;
}

bool SpriteAnimationController::IsAnimationEnd()
{
	return currentIndex < 0 || !animations.size() || animations[currentIndex].IsEnd();
}

SpriteAnimation* SpriteAnimationController::operator[](int index)
{
	return GetByIndex(index);
}

SpriteAnimation* SpriteAnimationController::operator[](std::string_view title)
{
	return GetByTitle(title);
}
