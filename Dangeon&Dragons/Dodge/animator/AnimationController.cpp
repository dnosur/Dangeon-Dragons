#include "AnimationController.h"

IAnimation* AnimationController::GetByTitle(const char* title)
{
	for (IAnimation*& animation : animations) {
		if (!strcmp(animation->GetTitle(), title)) {
			return animation;
		}
	}
	return nullptr;
}

IAnimation* AnimationController::GetByTitle(const char* title, int& index)
{
	index = 0;
	for (IAnimation*& animation : animations) {
		if (!strcmp(animation->GetTitle(), title)) {
			return animation;
		}
		index++;
	}
	index = -1;
	return nullptr;
}

IAnimation* AnimationController::GetByIndex(int index)
{
	if (index < 0 || index >= animations.size()) {
		return nullptr;
	}
	return animations[index];
}

void AnimationController::DropPrevAnim(IAnimation* currentAnim)
{
	return;

	if (prevAnim == nullptr) {
		copyStr(currentAnim->GetTitle(), prevAnim);
		return;
	}

	if (strcmp(currentAnim->GetTitle(), prevAnim)) {
		animations[currentIndex]->Stop();
		copyStr(currentAnim->GetTitle(), prevAnim);
	}
}

AnimationController::AnimationController()
{
	prevAnim = nullptr;
	currentIndex = -1;
}

AnimationController::AnimationController(boost::container::vector<IAnimation*> animations)
{
	this->animations = animations;
	prevAnim = nullptr;
	currentIndex = -1;
}

void AnimationController::AddAnimation(IAnimation* animation)
{
	IAnimation* same = GetByTitle(animation->GetTitle());
	if (same == nullptr) {
		animations.push_back(animation);
		return;
	}

	same = animation->Clone();
}

void AnimationController::AddAnimations(boost::container::vector<IAnimation*> animations)
{
	for (IAnimation*& animation : animations) {
		AddAnimation(animation);
	}
}

void AnimationController::Play(int index)
{
	IAnimation* animation = GetByIndex(index);

	if (animation != nullptr) {
		DropPrevAnim(animation);
		animation->Play();
		currentIndex = index;
	}
}

void AnimationController::Play(int index, Coord pos, Size size)
{
	IAnimation* animation = GetByIndex(index);

	if (animation != nullptr) {
		DropPrevAnim(animation);
		animation->Play(pos, size);
		currentIndex = index;
	}
}

void AnimationController::PlayOnEnd(int index)
{
	if (!IsAnimationEnd()) {
		return;
	}

	Play(index);
}

void AnimationController::PlayOnEnd(int index, Coord pos, Size size)
{
	if (!IsAnimationEnd()) {
		return;
	}

	Play(index, pos, size);
}

bool AnimationController::Play(const char* title)
{
	int newIndex = 0;
	IAnimation* animation = GetByTitle(title, newIndex);

	if (animation != nullptr) {
		DropPrevAnim(animation);

		if (animation->IsEnd()) {
			animation->Restart();
			return true;
		}

		animation->Play();
		currentIndex = newIndex;
		return true;
	}
	return false;
}

void AnimationController::Play(const char* title, Coord pos, Size size)
{
	int newIndex = 0;
	IAnimation* animation = GetByTitle(title, newIndex);

	if (animation != nullptr) {
		DropPrevAnim(animation);
		animation->Play(pos, size);
		currentIndex = newIndex;
	}
}

void AnimationController::PlayOnEnd(const char* title)
{
	if (!IsAnimationEnd()) {
		return;
	}

	Play(title);
}

void AnimationController::PlayOnEnd(const char* title, Coord pos, Size size)
{
	if (!IsAnimationEnd()) {
		return;
	}

	Play(title, pos, size);
}

void AnimationController::PlayAll()
{
	for (IAnimation*& animation : animations) {
		animation->Play();
	}
}

int AnimationController::GetSize()
{
	return animations.size();
}

int AnimationController::GetCurrentIndex()
{
	return currentIndex;
}

bool AnimationController::IsAnimationEnd()
{
	return currentIndex < 0 || !animations.size() || animations.operator[](currentIndex)->IsEnd();
}

IAnimation* AnimationController::operator[](const char* title)
{
	return GetByTitle(title);
}

IAnimation* AnimationController::operator[](int index)
{
	return GetByIndex(index);
}
