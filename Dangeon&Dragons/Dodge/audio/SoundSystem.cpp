#include "SoundSystem.h"

SoundSystem::SoundSystem(ALchar* devicename)
{
	device = alcOpenDevice(NULL);
	this->devicename = devicename;

	if (!device) {
		std::cerr << "Failed to open audio device!" << std::endl;
		return;
	}

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) {
		std::cerr << "Failed to create context!" << std::endl;
		return;
	}
}

SoundSystem::~SoundSystem()
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}
