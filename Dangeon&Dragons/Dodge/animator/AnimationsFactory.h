#pragma once
#include "VertexAnimation.h"
#include "SpriteAnimation.h"

static class AnimationsFactory
{
public:
	static VertexAnimation* CreateVertexAnimation(
		const char* title,
		int frameRate, bool repeat, bool stopOnEnd,
		IGameObject* object, std::vector<std::pair<int, std::vector<Coord>>> frames = {}
	);

	static SpriteAnimation* CreateSpriteAnimation(
		const char* title, const char* folder, 
		int frameRate, Window* window, bool revere = false, 
		std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

	static SpriteAnimation* CreateSpriteAnimation(
		const char* title, Coord pos, Size size, 
		const char* folder, int frameRate, Window* window, 
		bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

	static SpriteAnimation* CreateSpriteAnimation(
		const char* title, std::vector<Image> sprites, 
		int frameRate, Window* window, bool revere = false, 
		std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

	static SpriteAnimation* CreateSpriteAnimation(
		const char* title, Coord pos, Size size, std::vector<Image> sprites,
		int frameRate, Window* window, bool revere = false, 
		std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);
};

