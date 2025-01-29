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

	void Play(std::string_view title, bool loop = false);

	void Load(std::string title, std::string path);
	void Load(std::shared_ptr<Audio> audio);

	int GetSize();

	std::weak_ptr<Audio> operator[](std::string_view title);
};