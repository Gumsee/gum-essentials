#include <gum-essentials.h>
#include <gum-maths.h>

int main(int argc, char** argv)
{
    Gum::Display::init();
    Gum::Window* pContextWindow = new Gum::Window("Window Example", ivec2(75, 75), Gum::Window::Properties::WINDOW_SIZE_IN_PERCENT);
    pContextWindow->initOpenGL();
    pContextWindow->setClearColor(vec4(0.24f, 0.39f, 0.75f, 1.0f));
    pContextWindow->setMouse(new Gum::Input::InputMouseClass(pContextWindow));
    pContextWindow->setKeyboard(new Gum::Input::InputKeyboardClass(pContextWindow));

    Gum::Display::printInfo();

    while(pContextWindow->isOpen())
    {
        Gum::Display::pollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        pContextWindow->finishRender();
    }
    Gum::Display::terminate();
}