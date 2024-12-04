#pragma once
#include "IAnimation.h"

class AnimationController
{
	std::vector<IAnimation*> animations;

	IAnimation* GetByTitle(const char* title);
	IAnimation* GetByTitle(const char* title, int& index);

	IAnimation* GetByIndex(int index);

	int currentIndex;
public:
	AnimationController();
	AnimationController(std::vector<IAnimation*> animations);

	void AddAnimation(IAnimation* animation);
	void AddAnimations(std::vector<IAnimation*> animations);

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

	IAnimation* operator[](int index);
	IAnimation* operator[](const char* title);
};

