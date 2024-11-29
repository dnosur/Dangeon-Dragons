#include "Timer.h"

Timer::Timer(){
	lastTime = std::chrono::high_resolution_clock::now();
}

float Timer::GetDeltaTime()
{
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> deltaTime = now - lastTime;
    lastTime = now;
    return deltaTime.count();
}
