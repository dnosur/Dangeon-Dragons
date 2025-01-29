#include "AnimationController.h"
#include "SpriteAnimation.h"

std::weak_ptr<IAnimation> AnimationController::GetByTitle(std::string_view title)
{
	for (std::shared_ptr<IAnimation>& animation : animations) {
		if (animation->GetTitle() == title) {
			return animation;
		}
	}
	return std::weak_ptr<SpriteAnimation>();
}

std::weak_ptr<IAnimation> AnimationController::GetByTitle(std::string_view title, int& index)
{
	index = 0;
	for (std::shared_ptr<IAnimation>& animation : animations) {
		if (animation->GetTitle() == title) {
			return animation;
		}
		index++;
	}
	index = -1;
	return std::weak_ptr<SpriteAnimation>();
}

std::weak_ptr<IAnimation> AnimationController::GetByIndex(int index)
{
	if (index < 0 || index >= animations.size()) {
		return std::weak_ptr<SpriteAnimation>();
	}
	return animations[index];
}

void AnimationController::DropPrevAnim(std::shared_ptr<IAnimation> currentAnim)
{
	return;

	if (prevAnim.empty()) {
		prevAnim = currentAnim->GetTitle();
		return;
	}

	if (currentAnim->GetTitle() != prevAnim) {
		animations[currentIndex]->Stop();
		prevAnim = currentAnim->GetTitle();
	}
}

AnimationController::AnimationController()
{
	currentIndex = -1;
}

AnimationController::AnimationController(std::vector<std::shared_ptr<IAnimation>> animations)
{
	this->animations = animations;
	currentIndex = -1;
}

void AnimationController::AddAnimation(std::shared_ptr<IAnimation> animation)
{
	const std::weak_ptr<IAnimation>& weakSame = GetByTitle(animation->GetTitle());
	std::shared_ptr<IAnimation> same = weakSame.lock();

	if (same == nullptr || weakSame.expired()) {
		animations.push_back(animation);
		return;
	}

	same = animation;
}

void AnimationController::AddAnimations(std::vector<std::shared_ptr<IAnimation>> animations)
{
	for (std::shared_ptr<IAnimation>& animation : animations) {
		AddAnimation(animation);
	}
}

void AnimationController::Play(int index)
{
	std::weak_ptr<IAnimation> weakAnimation = GetByIndex(index);
	std::shared_ptr<IAnimation> animation = weakAnimation.lock();

	if (animation == nullptr || weakAnimation.expired()) {
		return;
	}

	DropPrevAnim(animation);
	animation->Play();
	currentIndex = index;
}

void AnimationController::Play(int index, Coord pos, Size size)
{
	std::weak_ptr<IAnimation> weakAnimation = GetByIndex(index);
	std::shared_ptr<IAnimation> animation = weakAnimation.lock();

	if (animation == nullptr || weakAnimation.expired()) {
		return;
	}

	DropPrevAnim(animation);
	animation->Play(pos, size);
	currentIndex = index;
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
	std::weak_ptr<IAnimation> weakAnimation = GetByTitle(title, newIndex);
	std::shared_ptr<IAnimation> animation = weakAnimation.lock();

	if (animation == nullptr || weakAnimation.expired()) {
		return false;
	}

	DropPrevAnim(animation);

	if (animation->IsEnd()) {
		animation->Restart();
		return true;
	}

	animation->Play();
	currentIndex = newIndex;
	return true;
}

void AnimationController::Play(std::string_view title, Coord pos, Size size)
{
	int newIndex = 0;
	std::weak_ptr<IAnimation> weakAnimation = GetByTitle(title, newIndex);
	std::shared_ptr<IAnimation> animation = weakAnimation.lock();

	if (animation == nullptr || weakAnimation.expired()) {
		return;
	}

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
	for (std::shared_ptr<IAnimation>& animation : animations) {
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

std::weak_ptr<IAnimation> AnimationController::operator[](std::string_view title)
{
	return GetByTitle(title);
}

std::weak_ptr<IAnimation> AnimationController::operator[](int index)
{
	return GetByIndex(index);
}