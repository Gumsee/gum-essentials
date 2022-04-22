#include <gum-essentials.h>
#include <gum-maths.h>

int main(int argc, char** argv)
{
    Gum::Window* pContextWindow = new Gum::Window(false, "Window Example", ivec2(75, 75), true);
    pContextWindow->initOpenGL();
    pContextWindow->setClearColor(vec4(0.24f, 0.39f, 0.75f, 1.0f));
    pContextWindow->setMouse(new Gum::Input::InputMouseClass(pContextWindow));
    pContextWindow->setKeyboard(new Gum::Input::InputKeyboardClass(pContextWindow));

    Gum::Display::printInfo();

    while(pContextWindow->isOpen())
    {
        pContextWindow->pollEvent();
        glClear(GL_COLOR_BUFFER_BIT);
        pContextWindow->finishRender();
    }
}