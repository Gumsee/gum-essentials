#include "Time.h"
#include <System/Output.h>

namespace Time
{
	float fCurrentFrametime = 0;
	float fElapsedTime = 0;
	std::chrono::high_resolution_clock::time_point clock = std::chrono::high_resolution_clock::now();

	void update()
	{
		auto elapsed = std::chrono::high_resolution_clock::now() - clock;
		fCurrentFrametime = std::chrono::duration<double>(elapsed).count();
        fElapsedTime += fCurrentFrametime;
		clock = std::chrono::high_resolution_clock::now();
	}

	float getFrametime() { return fCurrentFrametime; }
	float getFPS()       { return 1.0f / fCurrentFrametime; }
    float getTime()      { return fElapsedTime; }
}