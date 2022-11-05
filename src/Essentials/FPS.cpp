#include "FPS.h"
#include <System/Output.h>

namespace FPS
{
	float Current = 0;
	std::chrono::high_resolution_clock::time_point clock = std::chrono::high_resolution_clock::now();

	void update()
	{
		auto elapsed = std::chrono::high_resolution_clock::now() - clock;
		Current = std::chrono::duration<double>(elapsed).count();
		clock = std::chrono::high_resolution_clock::now();
	}

	float get() { return Current; }
}