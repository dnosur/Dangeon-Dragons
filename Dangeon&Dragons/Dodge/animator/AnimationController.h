#pragma once
#include "IAnimation.h"

class AnimationController
{
	std::vector<std::shared_ptr<IAnimation>> animations;
	char* prevAnim;

	std::weak_ptr<IAnimation> GetByTitle(const char* title);
	std::weak_ptr<IAnimation> GetByTitle(const char* title, int& index);

	std::weak_ptr<IAnimation> GetByIndex(int index);

	void DropPrevAnim(std::shared_ptr<IAnimation> currentAnim);

	int currentIndex;
public:
	AnimationController();
	AnimationController(std::vector<std::shared_ptr<IAnimation>> animations);

	void AddAnimation(std::shared_ptr<IAnimation> animation);
	void AddAnimations(std::vector<std::shared_ptr<IAnimation>> animations);

	void Play(int index);
	void Play(int index, Coord pos, Size size);
	void PlayOnEnd(int index);
	void PlayOnEnd(int index, Coord pos, Size size);

	bool Play(const char* title);
	void Play(const char* title, Coord pos, Size size);
	void PlayOnEnd(const char* title);
	void PlayOnEnd(const char* title, Coord pos, Size size);

	void PlayAll();

	int GetSize();

	int GetCurrentIndex();

	bool IsAnimationEnd();

	std::weak_ptr<IAnimation> operator[](const char* title);
	std::weak_ptr<IAnimation> operator[](int index);
};

