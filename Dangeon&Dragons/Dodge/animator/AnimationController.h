#pragma once
#include "IAnimation.h"
#include "unordered_map"

class AnimationController
{
	std::unordered_map<std::string, std::shared_ptr<IAnimation>> animations;

	std::string prevAnim;

	std::weak_ptr<IAnimation> GetByTitle(std::string_view title);
	std::weak_ptr<IAnimation> GetByTitle(std::string_view title, int& index);

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

	bool Play(std::string_view title);
	void Play(std::string_view title, Coord pos, Size size);
	void PlayOnEnd(std::string_view title);
	void PlayOnEnd(std::string_view title, Coord pos, Size size);

	void PlayAll();

	int GetSize();

	int GetCurrentIndex();

	bool IsAnimationEnd();

	std::weak_ptr<IAnimation> operator[](std::string_view title);
	std::weak_ptr<IAnimation> operator[](int index);
};
