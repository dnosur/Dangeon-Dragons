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

	void Play(std::string_view title, bool loop = false);

<<<<<<< Updated upstream
	void Load(const char* title, const char* path);
	void Load(Audio* audio);

	int GetSize();

	Audio* operator[](const char* title);
=======
	void Load(std::string title, std::string path);
	void Load(std::shared_ptr<Audio> audio);

	int GetSize();

	std::weak_ptr<Audio> operator[](std::string_view title);
>>>>>>> Stashed changes
};