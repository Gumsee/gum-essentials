#pragma once
#include <chrono>

namespace Time
{
	extern void update();
	extern float getFrametime();
	extern float getFPS();
    extern float getTime();

	extern float fCurrentFrametime;
	extern float fElapsedTime;
	extern std::chrono::high_resolution_clock::time_point clock; //std::chrono::system_time::time_point
}