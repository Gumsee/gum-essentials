#pragma once
#include <chrono>

namespace FPS
{
	extern void update();
	extern float get();
	extern float getFPS();

	extern float Current;
	extern std::chrono::high_resolution_clock::time_point clock; //std::chrono::system_time::time_point
}