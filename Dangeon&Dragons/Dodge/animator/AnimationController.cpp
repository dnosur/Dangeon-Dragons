#include "AnimationController.h"

<<<<<<< Updated upstream
IAnimation* AnimationController::GetByTitle(const char* title)
{
	for (IAnimation*& animation : animations) {
		if (!strcmp(animation->GetTitle(), title)) {
=======
std::weak_ptr<IAnimation> AnimationController::GetByTitle(std::string_view title)
{
	for (std::shared_ptr<IAnimation>& animation : animations) {
		if (animation->GetTitle() == title) {
>>>>>>> Stashed changes
			return animation;
		}
	}
	return nullptr;
}

<<<<<<< Updated upstream
IAnimation* AnimationController::GetByTitle(const char* title, int& index)
{
	index = 0;
	for (IAnimation*& animation : animations) {
		if (!strcmp(animation->GetTitle(), title)) {
=======
std::weak_ptr<IAnimation> AnimationController::GetByTitle(std::string_view title, int& index)
{
	index = 0;
	for (std::shared_ptr<IAnimation>& animation : animations) {
		if (animation->GetTitle() == title) {
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
	if (prevAnim == nullptr) {
		copyStr(currentAnim->GetTitle(), prevAnim);
=======
	if (prevAnim.empty()) {
		prevAnim = currentAnim->GetTitle();
>>>>>>> Stashed changes
		return;
	}

	if (currentAnim->GetTitle() != prevAnim) {
		animations[currentIndex]->Stop();
<<<<<<< Updated upstream
		copyStr(currentAnim->GetTitle(), prevAnim);
=======
		prevAnim = currentAnim->GetTitle();
>>>>>>> Stashed changes
	}
}

AnimationController::AnimationController()
{
	currentIndex = -1;
}

AnimationController::AnimationController(std::vector<IAnimation*> animations)
{
	this->animations = animations;
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

void AnimationController::AddAnimations(std::vector<IAnimation*> animations)
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

bool AnimationController::Play(std::string_view title)
{
	int newIndex = 0;
	IAnimation* animation = GetByTitle(title, newIndex);

<<<<<<< Updated upstream
	if (animation != nullptr) {
		DropPrevAnim(animation);
=======
	if (animation == nullptr || weakAnimation.expired()) {
		return false;
	}

	DropPrevAnim(animation);
>>>>>>> Stashed changes

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

void AnimationController::Play(std::string_view title, Coord pos, Size size)
{
	int newIndex = 0;
	IAnimation* animation = GetByTitle(title, newIndex);

	if (animation != nullptr) {
		DropPrevAnim(animation);
		animation->Play(pos, size);
		currentIndex = newIndex;
	}
}

void AnimationController::PlayOnEnd(std::string_view title)
{
	if (!IsAnimationEnd()) {
		return;
	}

	Play(title);
}

void AnimationController::PlayOnEnd(std::string_view title, Coord pos, Size size)
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

<<<<<<< Updated upstream
IAnimation* AnimationController::operator[](const char* title)
=======
std::weak_ptr<IAnimation> AnimationController::operator[](std::string_view title)
>>>>>>> Stashed changes
{
	return GetByTitle(title);
}

IAnimation* AnimationController::operator[](int index)
{
	return GetByIndex(index);
}