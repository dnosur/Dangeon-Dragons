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

AudioController::AudioController(std::vector<Audio*> sounds)
{
	Clear();
	for (Audio*& sound : sounds) {
		this->sounds.push_back(sound);
	}
}

void AudioController::Play(const char* title, bool loop)
{
	Audio* audio = (*this)[title];
	if (audio != nullptr) {
		audio->Play(loop);
	}
}

void AudioController::Load(const char* title, const char* path)
{
	sounds.push_back(new Audio(title, path));
}

void AudioController::Load(Audio* audio)
{
	sounds.push_back(audio);
}

int AudioController::GetSize()
{
	return sounds.size();
}

Audio* AudioController::operator[](const char* title)
{
	for (Audio*& sound : sounds) {
		if (!strcmp(sound->GetTitle(), title)) {
			return sound;
		}
	}
	return nullptr;
}
