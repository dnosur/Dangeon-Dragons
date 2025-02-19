#pragma once
#include "VertexAnimation.h"
#include "SpriteAnimation.h"

static class AnimationsFactory
{
public:
	static std::shared_ptr<VertexAnimation> CreateVertexAnimation(
		std::string title,
		int frameRate, bool repeat, bool stopOnEnd,
		std::shared_ptr<IGameObject> object, 
		std::vector<std::pair<int, std::vector<Coord>>> frames = {}
	);

	static std::shared_ptr<SpriteAnimation> CreateSpriteAnimation(
		std::string title, std::string folder, 
		int frameRate, bool revere = false, 
		std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

	static std::shared_ptr<SpriteAnimation> CreateSpriteAnimation(
		std::string title, Coord position, Size size, 
		std::string folder, int frameRate, 
		bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

	static std::shared_ptr<SpriteAnimation> CreateSpriteAnimation(
		std::string title, std::vector<Image> sprites, 
		int frameRate, bool revere = false, 
		std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

	static std::shared_ptr<SpriteAnimation> CreateSpriteAnimation(
		std::string title, Coord position, Size size, std::vector<Image> sprites,
		int frameRate, bool revere = false, 
		std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);
};

