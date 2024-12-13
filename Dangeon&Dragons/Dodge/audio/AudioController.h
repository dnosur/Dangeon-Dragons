#pragma once
#include <vector>

#include "Audio.h"

class AudioController
{
	std::vector<Audio*> sounds;

	void Clear();
public:
	AudioController();
	AudioController(std::vector<Audio*> sounds);

	void Play(const char* title, bool loop = false);

	void Load(const char* title, const char* path);
	void Load(Audio* audio);

	int GetSize();

	Audio* operator[](const char* title);
};