#include "FPS.h"
#include "Output.h"

namespace FPS
{
	float Current = 0;
	sf::Clock *pClock;

	void init()
	{
		pClock = new sf::Clock();
	}

	void update()
	{
		//Gum::Output::debug("Updating FPS");
		Current = pClock->getElapsedTime().asSeconds();
		pClock->restart();
	}

	float get() { return Current; }
}