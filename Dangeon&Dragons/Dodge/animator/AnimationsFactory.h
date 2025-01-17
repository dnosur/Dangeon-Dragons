#pragma once
#include "VertexAnimation.h"
#include "SpriteAnimation.h"

static class AnimationsFactory
{
public:
	static std::shared_ptr<VertexAnimation> CreateVertexAnimation(
		const char* title,
		int frameRate, bool repeat, bool stopOnEnd,
		std::shared_ptr<IGameObject> object, 
		std::vector<std::pair<int, std::vector<Coord>>> frames = {}
	);

	static std::shared_ptr<SpriteAnimation> CreateSpriteAnimation(
		const char* title, const char* folder, 
		int frameRate, Window* window, bool revere = false, 
		std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

	static std::shared_ptr<SpriteAnimation> CreateSpriteAnimation(
		const char* title, Coord pos, Size size, 
		const char* folder, int frameRate, Window* window, 
		bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

	static std::shared_ptr<SpriteAnimation> CreateSpriteAnimation(
		const char* title, std::vector<Image> sprites, 
		int frameRate, Window* window, bool revere = false, 
		std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

	static std::shared_ptr<SpriteAnimation> CreateSpriteAnimation(
		const char* title, Coord pos, Size size, std::vector<Image> sprites,
		int frameRate, Window* window, bool revere = false, 
		std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);
};

