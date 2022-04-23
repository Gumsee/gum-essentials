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
		GLFWwindow *pRenderWindow;
		ivec2 v2VisibleAreaSize;
		ivec2 v2Size, v2Pos;
		mat4 m4ScreenMatrix;
		float fAspectRatio, fAspectRatioWidthToHeight;
		bool bIsFullscreen = false;
		bool bHidden = false;
		std::string sTitle;

		Input::InputKeyboardClass* pKeyboard;
		Input::InputMouseClass* pMouse;

	public:
		Window(bool fullscreen, std::string title, ivec2 windowsize, bool inpercent, bool borderless, Window* parentWindow = nullptr);

		void resetViewport();
		void initOpenGL();

		//Passthrough
		void close();
		void finishRender();
		void bind();
		void clear(int clearbits = GL_COLOR_BUFFER_BIT);

		//Setter
		void setSize(const ivec2& size);
		void setPosition(const ivec2& pos);
		void setKeyboard(Input::InputKeyboardClass* keyboard);
		void setMouse(Input::InputMouseClass* mouse);
		void setClearColor(vec4 color);
		void setVerticalSync(bool vsync);
		void hide(bool hiddenstat);

		//Getter
		GLFWwindow* getRenderWindow() const;
		ivec2 getSize() const;
		ivec2 getPosition() const;
		mat4 getScreenMatrix() const;
		std::string getTitle() const;
		Input::InputKeyboardClass* getKeyboard();
		Input::InputMouseClass* getMouse();
		float getAspectRatio() const;
		float getAspectRatioWidthToHeight() const;
		bool isFullscreen() const;
		bool isOpen() const;
	};
}
