#pragma once
#include "VertexAnimation.h"
#include "SpriteAnimation.h"

static class AnimationsFactory
{
public:
<<<<<<< Updated upstream
	static VertexAnimation* CreateVertexAnimation(
		const char* title,
=======
	static std::shared_ptr<VertexAnimation> CreateVertexAnimation(
		std::string title,
>>>>>>> Stashed changes
		int frameRate, bool repeat, bool stopOnEnd,
		IGameObject* object, std::vector<std::pair<int, std::vector<Coord>>> frames = {}
	);

<<<<<<< Updated upstream
	static SpriteAnimation* CreateSpriteAnimation(
		const char* title, const char* folder, 
=======
	static std::shared_ptr<SpriteAnimation> CreateSpriteAnimation(
		std::string title, std::string folder, 
>>>>>>> Stashed changes
		int frameRate, Window* window, bool revere = false, 
		std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

<<<<<<< Updated upstream
	static SpriteAnimation* CreateSpriteAnimation(
		const char* title, Coord pos, Size size, 
		const char* folder, int frameRate, Window* window, 
		bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

	static SpriteAnimation* CreateSpriteAnimation(
		const char* title, std::vector<Image> sprites, 
=======
	static std::shared_ptr<SpriteAnimation> CreateSpriteAnimation(
		std::string title, Coord pos, Size size, 
		std::string folder, int frameRate, Window* window, 
		bool revere = false, std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

	static std::shared_ptr<SpriteAnimation> CreateSpriteAnimation(
		std::string title, std::vector<Image> sprites, 
>>>>>>> Stashed changes
		int frameRate, Window* window, bool revere = false, 
		std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);

<<<<<<< Updated upstream
	static SpriteAnimation* CreateSpriteAnimation(
		const char* title, Coord pos, Size size, std::vector<Image> sprites,
=======
	static std::shared_ptr<SpriteAnimation> CreateSpriteAnimation(
		std::string title, Coord pos, Size size, std::vector<Image> sprites,
>>>>>>> Stashed changes
		int frameRate, Window* window, bool revere = false, 
		std::vector<FrameSound> frameSounds = std::vector<FrameSound>()
	);
};

