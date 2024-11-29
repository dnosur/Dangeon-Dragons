#pragma once
#include <AL/al.h>
#include <AL/alc.h>

#include <cstddef>
#include <iostream>

class SoundSystem
{
	ALCdevice* device;
	ALCcontext* context;
	ALchar* devicename;
public:

	SoundSystem(ALchar* devicename = NULL);
	~SoundSystem();
};

