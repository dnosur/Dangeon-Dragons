#pragma once
#include "IAnimation.h"
#include "../audio/FrameSoundsController.h"
#include "../IGameObject.h"

class VertexAnimation :
    public IAnimation
{
    FrameSoundsController frameSounds;

    boost::container::vector<
		//wait time, vertexes
		std::pair<int, boost::container::vector<Coord>>
    > frames;

    Timer* timer;

	char* title;

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
	VertexAnimation(const char* title, int frameRate, bool repeat, bool stopOnEnd, IGameObject* object, boost::container::vector<
		std::pair<int, boost::container::vector<Coord>>> frames = {}
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

	char* GetFolder();
	void LoadFromFolder(char* folder);

	int GetFrameRate();
	void SetFrameRate(int frameRate);

	bool IsRepeat();
	void SetRepeat(bool repeat);

	bool IsStopOnEnd();
	void SetStopOnEnd(bool stopOnEnd);

	void SetTitle(char* title);
	char* GetTitle();

	void AddFrame(int waitTime, boost::container::vector<Coord> vertexes);
	void AddFrame(std::pair<int, boost::container::vector<Coord>> frame);

	void ClearFrames();

	int GetFramesCount();

	IGameObject* GetGameObject();
	void SetGameObject(IGameObject* object);

	IAnimation* Clone();

	std::pair<int, boost::container::vector<Coord>>* operator[](int index);
};

