#pragma once
#include "IAnimation.h"

class AnimationController
{
<<<<<<< Updated upstream
	std::vector<IAnimation*> animations;
	char* prevAnim;

	IAnimation* GetByTitle(const char* title);
	IAnimation* GetByTitle(const char* title, int& index);
=======
	std::vector<std::shared_ptr<IAnimation>> animations;
	std::string prevAnim;

	std::weak_ptr<IAnimation> GetByTitle(std::string_view title);
	std::weak_ptr<IAnimation> GetByTitle(std::string_view title, int& index);
>>>>>>> Stashed changes

	IAnimation* GetByIndex(int index);

	void DropPrevAnim(IAnimation* currentAnim);

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

	bool Play(std::string_view title);
	void Play(std::string_view title, Coord pos, Size size);
	void PlayOnEnd(std::string_view title);
	void PlayOnEnd(std::string_view title, Coord pos, Size size);

	void PlayAll();

	int GetSize();

	int GetCurrentIndex();

	bool IsAnimationEnd();

<<<<<<< Updated upstream
	IAnimation* operator[](const char* title);
	IAnimation* operator[](int index);
};

=======
	std::weak_ptr<IAnimation> operator[](std::string_view title);
	std::weak_ptr<IAnimation> operator[](int index);
};
>>>>>>> Stashed changes
