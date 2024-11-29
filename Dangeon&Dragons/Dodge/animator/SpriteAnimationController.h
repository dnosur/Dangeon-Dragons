#pragma once
#include "SpriteAnimation.h"

class SpriteAnimationController
{
	std::vector<SpriteAnimation> animations;

	SpriteAnimation* GetByTitle(const char* title);
	SpriteAnimation* GetByTitle(const char* title, int& index);

	SpriteAnimation* GetByIndex(int index);

	int currentIndex;
public:
	SpriteAnimationController();
	SpriteAnimationController(std::vector<SpriteAnimation> animations);

	void AddAnimation(SpriteAnimation animation);
	void AddAnimations(std::vector<SpriteAnimation> animations);

	void Play(int index);
	void Play(int index, Coord pos, Size size);
	void PlayOnEnd(int index);
	void PlayOnEnd(int index, Coord pos, Size size);

	void Play(const char* title);
	void Play(const char* title, Coord pos, Size size);
	void PlayOnEnd(const char* title);
	void PlayOnEnd(const char* title, Coord pos, Size size);

	void PlayAll();

	int GetSize();

	int GetCurrentIndex();

	bool IsAnimationEnd();

	SpriteAnimation* operator[](int index);
	SpriteAnimation* operator[](const char* title);
};

