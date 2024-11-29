#include "AudioController.h"

void AudioController::Clear()
{
	if (!sounds.size()) {
		return;
	}
	sounds.clear();
}

AudioController::AudioController()
{
}

AudioController::AudioController(std::vector<Audio> sounds)
{
	Clear();
	for (const Audio& sound : sounds) {
		this->sounds.push_back(sound);
	}
}

void AudioController::Play(const char* title)
{
	for (Audio& sound : sounds) {
		if (!strcmp(sound.GetTitle(), title)) {
			sound.Play();
		}
	}
}

void AudioController::Load(const char* title, const char* path)
{
	sounds.push_back(Audio(title, path));
}

void AudioController::Load(Audio audio)
{
	sounds.push_back(audio);
}

int AudioController::GetSize()
{
	return sounds.size();
}
