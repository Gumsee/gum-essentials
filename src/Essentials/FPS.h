#pragma once
#include <chrono>

namespace FPS
{
	extern void init();
	extern void update();
	extern float get();

	extern float Current;
	extern std::chrono::system_clock::time_point clock;
}