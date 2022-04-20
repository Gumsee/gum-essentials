#pragma once
#include <SFML/Graphics.hpp>

namespace FPS
{
	extern void init();
	extern void update();
	extern float get();

	extern float Current;
	extern sf::Clock *pClock;
}