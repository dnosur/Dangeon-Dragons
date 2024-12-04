#pragma once
#include <iostream>
#include <filesystem>

#include "IAnimation.h"

#include "../FrameSoundsController.h"
#include "../ImagesController.h"

#include "../functions.h"

namespace fs = std::filesystem;

class SpriteAnimation 
	: public IAnimation
{
	ImagesController sprites;
	FrameSoundsController frameSounds;

	Window* window;

	Image* currentFrameTitle;
	Image* rootTile;

	Timer timer;

	char* title;

	char* folder;
	int frameRate;

	float timePassed;

	int currentSpriteIndex;

	bool repeat;
	bool stopOnEnd;
	bool play, pause;
	bool reverse;

	bool end;

	Coord pos;
	Size size;

	void LoadSpritesFromFolder();
public:
	SpriteAnimation();

	SpriteAnimation(const char* title, const char* folder, int frameRate, Window* window, bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>());
	SpriteAnimation(const char* title, Coord pos, Size size, const char* folder, int frameRate, Window* window, bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>());
	SpriteAnimation(const char* title, std::vector<Image> sprites, int frameRate, Window* window, bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>());
	SpriteAnimation(const char* title, Coord pos, Size size, std::vector<Image> sprites, int frameRate, Window* window, bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>());

	void SetWindow(Window* window);

	void SetTitle(char* title);
	char* GetTitle();

	std::vector<Image> GetSprites();
	void SetSprites(std::vector<Image> sprites);

	char* GetFolder();
	void LoadFromFolder(char* folder);

	int GetFrameRate();
	void SetFrameRate(int frameRate);

	bool IsRepeat();
	void SetRepeat(bool repeat);

	bool IsStopOnEnd();
	void SetStopOnEnd(bool stopOnEnd);

	void SetCurrentSprite(int spriteIndex);
	int GetCurrentSpriteIndex();

	void Play();
	void Play(Coord coord, Size size);

	bool IsEnd();

	bool IsPlay();
	bool IsReverse();

	void Pause();
	void Stop();

	void Restart();
	void Reverse();

	void SetRootTile(Image* image);

	Image* GetCurrentyFrame();
	Image* GetRootTile();

	IAnimation* Clone();

	bool operator =(const SpriteAnimation& other);
};