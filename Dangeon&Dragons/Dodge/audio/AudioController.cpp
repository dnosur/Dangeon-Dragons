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

AudioController::AudioController(std::vector<std::shared_ptr<Audio>> sounds)
{
	Clear();
	for (std::shared_ptr<Audio>& sound : sounds) {
		this->sounds.push_back(sound);
	}
}

void AudioController::Play(const char* title, bool loop)
{
	std::weak_ptr<Audio> audio = (*this)[title];
	if (!audio.expired() && audio.lock() != nullptr) {
		audio.lock()->Play(loop);
	}
}

void AudioController::Load(const char* title, const char* path)
{
	sounds.push_back(std::make_shared<Audio>(title, path));
}

void AudioController::Load(std::shared_ptr<Audio> audio)
{
	sounds.push_back(audio);
}

int AudioController::GetSize()
{
	return sounds.size();
}

std::weak_ptr<Audio> AudioController::operator[](const char* title)
{
	for (std::shared_ptr<Audio>& sound : sounds) {
		if (!strcmp(sound->GetTitle(), title)) {
			return sound;
		}
	}
	return std::weak_ptr<Audio>();
}
