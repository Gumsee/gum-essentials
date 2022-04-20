#include <gum-essentials.h>
#include <gum-maths.h>

#include <iostream>

int main(int argc, char** argv)
{
    Gum::Window* pContextWindow = new Gum::Window(false, "GUI Example", ivec2(75, 75), true);
    Gum::Window::initOpenGL();
    Gum::Input::init(pContextWindow);

    while(pContextWindow->isOpen())
    {
        sf::Event event;
		while(pContextWindow->pollEvent(event))
		{
			Gum::Input::Keyboard->handleEvents(event);
			Gum::Input::Mouse->handleEvents(event);
			pContextWindow->handleEvents(event);
		}
    }
}