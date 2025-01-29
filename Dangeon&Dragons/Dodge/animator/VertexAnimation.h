#pragma once
#include "IAnimation.h"
#include "../audio/FrameSoundsController.h"
#include "../IGameObject.h"

class VertexAnimation :
    public IAnimation
{
    FrameSoundsController frameSounds;

    std::vector<
		//wait time, vertexes
		std::pair<int, std::vector<Coord>>
    > frames;

    Timer* timer;

	std::string title;

	int frameRate;

	float timePassed;
	float delay;

	int currentAnimationIndex;

	bool repeat;
	bool stopOnEnd;
	bool play, pause;
	bool reverse;

	bool end;

	IGameObject* object;

public:
	VertexAnimation(
		std::string title, int frameRate, bool repeat, bool stopOnEnd, 
		IGameObject* object, std::vector<
		std::pair<int, std::vector<Coord>>> frames = {}
	);

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

	std::string GetTitleString();


	void AddFrame(int waitTime, std::vector<Coord> vertexes);
	void AddFrame(std::pair<int, std::vector<Coord>> frame);

	void ClearFrames();

	int GetFramesCount();

	IGameObject* GetGameObject();
	void SetGameObject(IGameObject* object);

	IAnimation* Clone();

	std::pair<int, std::vector<Coord>>* operator[](int index);
};

