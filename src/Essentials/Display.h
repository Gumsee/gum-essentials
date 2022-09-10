#pragma once
#include <GLFW/glfw3.h>
#include <gum-maths.h>

namespace Gum {
namespace Display
{
    extern void init();
    extern void terminate();
    extern void pollEvents();
    extern std::vector<GLFWmonitor*> getMonitors();
    extern GLFWmonitor* getPrimaryMonitor();
    extern ivec2 getScreenSize(GLFWmonitor* screen = nullptr);
    extern int getScreenRefreshrate(GLFWmonitor* screen = nullptr);
    extern ivec3 getScreenPixelDepth(GLFWmonitor* screen = nullptr);
    extern void printInfo();
}}