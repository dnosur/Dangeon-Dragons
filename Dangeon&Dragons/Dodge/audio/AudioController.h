#pragma once
#include <vector>

#include "Audio.h"

class AudioController
{
	std::vector<std::shared_ptr<Audio>> sounds;

	void Clear();
public:
	AudioController();
	AudioController(std::vector<std::shared_ptr<Audio>> sounds);

	void Play(const char* title, bool loop = false);

	void Load(const char* title, const char* path);
	void Load(std::shared_ptr<Audio> audio);

	int GetSize();

	std::weak_ptr<Audio> operator[](const char* title);
};