#pragma once
#include <AL/al.h>
#include <sndfile.h>
#include <iostream>

#include "../functions.h"
#include "AudioStates.h"

class Audio
{
	ALuint source;
	ALuint buffer;

	std::string title;
	std::string path;

	float baseVolume;
	float volume;

	bool loop;

	float radius;

	AudioStates state;

	void Load();
public:
	Audio();
	Audio(
		std::string title, std::string path, 
		float radius = 10.0f, float volume = 1.0f, 
		bool loop = false
	);

	void Play(bool loop = false);

	void SetVolume(float volume);
	void SetDistanceVolume(Coord sourcePos, Coord listenerPos);

	float GetVolume();

	void SetRadius(float radius);
	float GetRadius();

	void SetLoop(bool loop);
	bool GetLoop();

	std::string_view GetTitle();
	std::string_view GetPath();

	AudioStates GetState();

	~Audio();

	bool operator==(const Audio& other) const;
	bool operator!=(const Audio& other) const;

	Audio& operator=(const Audio& other);
};