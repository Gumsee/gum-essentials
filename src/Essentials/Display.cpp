#include "Display.h"
#include "Output.h"
#include <GLFW/glfw3.h>
#include <string>

namespace Gum {
namespace Display
{
    void init()
	{
    	glfwSetErrorCallback([](int error, const char* description) {
    		Gum::Output::error("GLFW Error("+std::to_string(error)+"): " + description);
		});

		if (!glfwInit())
		{
    		Gum::Output::error("GLFW: Failed to initialize");
        	return;
		}
	}

    void terminate()
	{
		glfwTerminate();
	}

	void pollEvents() 
	{ 
		glfwPollEvents();
	}

	std::vector<GLFWmonitor*> getMonitors()
	{
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		std::vector<GLFWmonitor*> monitorsvec;
		for(int i = 0; i < count; i++)
			monitorsvec.push_back(monitors[i]);
		return monitorsvec;
	}

	GLFWmonitor* getPrimaryMonitor()
	{
		return glfwGetPrimaryMonitor();
	}
	ivec2 getScreenSize(GLFWmonitor* screen) 
	{ 
		if(screen == nullptr)
			screen = getPrimaryMonitor();
		const GLFWvidmode *mode = glfwGetVideoMode(screen);
		return ivec2(mode->width, mode->height); 
	}
	int getScreenRefreshrate(GLFWmonitor* screen)
	{
		if(screen == nullptr)
			screen = getPrimaryMonitor();
		const GLFWvidmode *mode = glfwGetVideoMode(screen);
		return mode->refreshRate; 
	}

	ivec3 getScreenPixelDepth(GLFWmonitor* screen)
	{
		if(screen == nullptr)
			screen = getPrimaryMonitor();
		const GLFWvidmode *mode = glfwGetVideoMode(screen);
		return ivec3(mode->redBits, mode->greenBits, mode->blueBits);
	}


	void printInfo()
	{
		std::vector<GLFWmonitor*> monitors = getMonitors();
        GLFWmonitor* primaryMonitor = getPrimaryMonitor();
		for(size_t i = 0; i < monitors.size(); i++)
		{
            ivec2 res = getScreenSize(monitors[i]);
            ivec3 depth = getScreenPixelDepth(monitors[i]);
            int refreshrate = getScreenRefreshrate(monitors[i]);
            std::string primaryStr = monitors[i] == primaryMonitor ? " (Primary Monitor)" : "";

			Gum::Output::print("Display: " + std::to_string(i) + primaryStr);
			Gum::Output::print("\tResolution: " + res.toString("", "", "x"));
			Gum::Output::print("\tRefreshrate: " + std::to_string(refreshrate));
			Gum::Output::print("\tPixelDepth: " + depth.toString("rgb(", ")"));
		}
	}

}}