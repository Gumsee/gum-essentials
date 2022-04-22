#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gum-maths.h>
#include "Input/Mouse.h"
#include "Input/Keyboard.h"

namespace Gum
{
	class Window
	{
	private:
		//extern SDL_Window *handle;
		//extern SDL_GLContext maincontext;
		//extern SDL_Event event;
		GLFWwindow *pRenderWindow;
		ivec2 v2RenderQuadSize;
		ivec2 v2RenderQuadPos;
		ivec2 v2VisibleAreaSize;
		ivec2 v2Size, v2Pos;
		mat4 m4ScreenMatrix;
		float fAspectRatio, fAspectRatioWidthToHeight;
		bool bIsFullscreen = false;

		Input::InputKeyboardClass* pKeyboard;
		Input::InputMouseClass* pMouse;

	public:
		Window(bool fullscreen, std::string title, ivec2 windowsize, bool inpercent);

		void resetViewport();
		void initOpenGL();

		//Passthrough
		void close();
		void pollEvent();
		void finishRender();
		static void terminate();

		//Setter
		void setSize(const ivec2& size);
		void setPosition(const ivec2& pos);
		void setKeyboard(Input::InputKeyboardClass* keyboard);
		void setMouse(Input::InputMouseClass* mouse);
		void setClearColor(vec4 color);

		//Getter
		GLFWwindow* getRenderWindow() const;
		ivec2 getSize() const;
		ivec2 getPosition() const;
		ivec2 getRenderQuadSize() const;
		ivec2 getRenderQuadPos() const;
		mat4 getScreenMatrix() const;
		Input::InputKeyboardClass* getKeyboard();
		Input::InputMouseClass* getMouse();
		float getAspectRatio() const;
		float getAspectRatioWidthToHeight() const;
		bool isFullscreen() const;
		bool isOpen() const;
	};
}
