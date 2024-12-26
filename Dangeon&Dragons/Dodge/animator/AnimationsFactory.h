#pragma once
#include "VertexAnimation.h"
#include "SpriteAnimation.h"

static class AnimationsFactory
{
public:
	static VertexAnimation* CreateVertexAnimation(
		const char* title,
		int frameRate, bool repeat, bool stopOnEnd,
		IGameObject* object, boost::container::vector<std::pair<int, boost::container::vector<Coord>>> frames = {}
	);

	static SpriteAnimation* CreateSpriteAnimation(
		const char* title, const char* folder, 
		int frameRate, Window* window, bool revere = false, 
		boost::container::vector<FrameSound> frameSounds = boost::container::vector<FrameSound>()
	);

	static SpriteAnimation* CreateSpriteAnimation(
		const char* title, Coord pos, Size size, 
		const char* folder, int frameRate, Window* window, 
		bool revere = false, boost::container::vector<FrameSound> frameSounds = boost::container::vector<FrameSound>()
	);

	static SpriteAnimation* CreateSpriteAnimation(
		const char* title, boost::container::vector<Image> sprites, 
		int frameRate, Window* window, bool revere = false, 
		boost::container::vector<FrameSound> frameSounds = boost::container::vector<FrameSound>()
	);

	static SpriteAnimation* CreateSpriteAnimation(
		const char* title, Coord pos, Size size, boost::container::vector<Image> sprites,
		int frameRate, Window* window, bool revere = false, 
		boost::container::vector<FrameSound> frameSounds = boost::container::vector<FrameSound>()
	);
};

