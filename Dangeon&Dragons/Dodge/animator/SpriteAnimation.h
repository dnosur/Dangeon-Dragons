#pragma once
#include <iostream>
#include <filesystem>

#include "IAnimation.h"

#include "../audio/FrameSoundsController.h"
#include "../images/ImagesController.h"

#include "../functions.h"

namespace fs = std::filesystem;

class SpriteAnimation 
	: public IAnimation
{
	ImagesController sprites;
	FrameSoundsController frameSounds;

	Window* window;

	std::shared_ptr<Image> currentFrameTitle;
	std::shared_ptr<Image> rootTile;

	Timer timer;

	std::string title;

	std::string folder;
	int frameRate;

	float timePassed;

	int currentSpriteIndex;

	bool repeat;
	bool stopOnEnd;
	bool play, pause;
	bool reverse;

	bool end;

	Coord position;
	Size size;

	void LoadSpritesFromFolder();
public:
	SpriteAnimation();

	SpriteAnimation(std::string title, std::string folder, int frameRate, Window* window, bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>());
	SpriteAnimation(std::string title, Coord position, Size size, std::string folder, int frameRate, Window* window, bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>());
	SpriteAnimation(std::string title, std::vector<Image> sprites, int frameRate, Window* window, bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>());
	SpriteAnimation(std::string title, Coord position, Size size, std::vector<Image> sprites, int frameRate, Window* window, bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>());

	void SetWindow(Window* window);

	void SetTitle(std::string title);
	std::string_view GetTitle();

	std::string GetTitleString();

	std::unordered_map<std::string, Image> GetSprites();
	void SetSprites(std::vector<Image> sprites);

	std::string_view GetFolder();
	void LoadFromFolder(std::string folder);

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

	void SetRootTile(std::shared_ptr<Image> image);

	std::shared_ptr<Image> GetCurrentyFrame();
	std::shared_ptr<Image> GetRootTile();

	IAnimation* Clone();

	bool operator =(const SpriteAnimation& other);
};