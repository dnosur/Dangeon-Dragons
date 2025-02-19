#include "AnimationController.h"
#include "SpriteAnimation.h"

std::weak_ptr<IAnimation> AnimationController::GetByTitle(std::string_view title)
{
	auto it = animations.find(std::string(title));
	if (it != animations.end()) {
		return it->second;
	}

	return std::weak_ptr<SpriteAnimation>();
}

std::weak_ptr<IAnimation> AnimationController::GetByTitle(std::string_view title, int& index)
{
	auto it = animations.find(std::string(title));
	if (it == animations.end()) {
		index = -1;
		return std::weak_ptr<IAnimation>(); 
	}

	index = std::distance(animations.begin(), it);

	return it->second; 
}

std::weak_ptr<IAnimation> AnimationController::GetByIndex(int index)
{
	auto it = animations.begin();
	std::advance(it, index);
	return it->second;
}

void AnimationController::DropPrevAnim(std::shared_ptr<IAnimation> currentAnim)
{
	return;

	if (prevAnim.empty()) {
		prevAnim = currentAnim->GetTitle();
		return;
	}

	std::shared_ptr<IAnimation> prev = GetByIndex(currentIndex).lock();

	if (currentAnim->GetTitle() != prevAnim && prev) {
		prev->Stop();
		prevAnim = currentAnim->GetTitle();
	}
}

AnimationController::AnimationController()
{
	currentIndex = -1;
}

AnimationController::AnimationController(std::vector<std::shared_ptr<IAnimation>> animations)
{
	for (std::shared_ptr<IAnimation>& animation : animations) {
		AddAnimation(animation);
	}
	currentIndex = -1;
}

void AnimationController::AddAnimation(std::shared_ptr<IAnimation> animation)
{
	const std::weak_ptr<IAnimation>& weakSame = GetByTitle(animation->GetTitle());
	std::shared_ptr<IAnimation> same = weakSame.lock();

	if (same == nullptr || weakSame.expired()) {
		animations[animation->GetTitleString()] = std::move(animation);
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

void AnimationController::Play(int index, Coord position, Size size)
{
	std::weak_ptr<IAnimation> weakAnimation = GetByIndex(index);
	std::shared_ptr<IAnimation> animation = weakAnimation.lock();

	if (animation == nullptr || weakAnimation.expired()) {
		return;
	}

	DropPrevAnim(animation);
	animation->Play(position, size);
	currentIndex = index;
}

void AnimationController::PlayOnEnd(int index)
{
	if (!IsAnimationEnd()) {
		return;
	}

	Play(index);
}

void AnimationController::PlayOnEnd(int index, Coord position, Size size)
{
	if (!IsAnimationEnd()) {
		return;
	}

	Play(index, position, size);
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

void AnimationController::Play(std::string_view title, Coord position, Size size)
{
	int newIndex = 0;
	std::weak_ptr<IAnimation> weakAnimation = GetByTitle(title, newIndex);
	std::shared_ptr<IAnimation> animation = weakAnimation.lock();

	if (animation == nullptr || weakAnimation.expired()) {
		return;
	}

	if (animation != nullptr) {
		DropPrevAnim(animation);
		animation->Play(position, size);
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

void AnimationController::PlayOnEnd(std::string_view title, Coord position, Size size)
{
	if (!IsAnimationEnd()) {
		return;
	}

	Play(title, position, size);
}

void AnimationController::PlayAll()
{
	for (auto& animation : animations) {
		animation.second->Play();
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
	std::shared_ptr<IAnimation> animation = GetByIndex(currentIndex).lock();
	if (animation == nullptr) {
		return true;
	}

	return currentIndex < 0 || !animations.size() || animation->IsEnd();
}

std::weak_ptr<IAnimation> AnimationController::operator[](std::string_view title)
{
	return GetByTitle(title);
}

std::weak_ptr<IAnimation> AnimationController::operator[](int index)
{
	return GetByIndex(index);
}