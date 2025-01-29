#pragma once
#include "SpriteAnimation.h"

class SpriteAnimationController
{
	std::vector<SpriteAnimation> animations;

	SpriteAnimation* GetByTitle(std::string_view title);
	SpriteAnimation* GetByTitle(std::string_view title, int& index);

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

	void Play(std::string_view title);
	void Play(std::string_view title, Coord pos, Size size);
	void PlayOnEnd(std::string_view title);
	void PlayOnEnd(std::string_view title, Coord pos, Size size);

	void PlayAll();

	int GetSize();

	int GetCurrentIndex();

	bool IsAnimationEnd();

	SpriteAnimation* operator[](int index);
	SpriteAnimation* operator[](std::string_view title);
};

