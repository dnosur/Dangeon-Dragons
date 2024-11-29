#pragma once
#include <AL/al.h>
#include <sndfile.h>
#include <iostream>

#include "functions.h"

class Audio
{
	ALuint source;
	ALuint buffer;

	char* title;
	char* path;

	void Load();
public:
	Audio();
	Audio(const char* title, const char* path);

	void Play();

	char* GetTitle();
	char* GetPath();

	~Audio();

	bool operator==(const Audio& other) const;
	bool operator!=(const Audio& other) const;

	Audio& operator=(const Audio& other);
};