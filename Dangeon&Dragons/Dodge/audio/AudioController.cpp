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

void AudioController::Play(std::string_view title, bool loop)
{
	Audio* audio = (*this)[title];
	if (audio != nullptr) {
		audio->Play(loop);
	}
}

void AudioController::Load(std::string title, std::string path)
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

<<<<<<< Updated upstream
Audio* AudioController::operator[](const char* title)
{
	for (Audio*& sound : sounds) {
		if (!strcmp(sound->GetTitle(), title)) {
=======
std::weak_ptr<Audio> AudioController::operator[](std::string_view title)
{
	for (std::shared_ptr<Audio>& sound : sounds) {
		if (sound->GetTitle() == title) {
>>>>>>> Stashed changes
			return sound;
		}
	}
	return nullptr;
}
