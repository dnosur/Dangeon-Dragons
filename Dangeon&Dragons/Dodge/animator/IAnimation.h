#pragma once
#include "../Coord.h"
#include "../Size.h"
#include "../Window.h"

__interface IAnimation
{
	void Play();
	void Play(Coord coord, Size size);

	bool IsEnd();

	bool IsPlay();
	bool IsReverse();

	void Pause();
	void Stop();

	void Restart();
	void Reverse();

	std::string_view GetFolder();
	void LoadFromFolder(std::string folder);

	int GetFrameRate();
	void SetFrameRate(int frameRate);

	bool IsRepeat();
	void SetRepeat(bool repeat);

	bool IsStopOnEnd();
	void SetStopOnEnd(bool stopOnEnd);

	void SetTitle(std::string title);
	std::string_view GetTitle();

	std::string GetStringTitle();

	IAnimation* Clone();
};