#pragma once
#include <chrono>

class Timer
{
	std::chrono::high_resolution_clock::time_point lastTime;
public:
    Timer();

    float GetDeltaTime();
};

