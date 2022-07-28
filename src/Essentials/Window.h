#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>
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
		bool bIsFullscreen;
		bool bHidden;
		bool bIsResizable;
		bool bHasBorder;
		bool bScalingSnapped;
		std::string sTitle;

		std::vector<std::function<void(int x, int y)> > vResizeFunctions;

		Input::InputKeyboardClass* pKeyboard;
		Input::InputMouseClass* pMouse;

	public:
		Window(bool fullscreen, std::string title, ivec2 windowsize, bool inpercent, bool borderless, Window* parentWindow = nullptr);
		~Window();

		static Window* MainWindow;
		static Window* CurrentlyBoundWindow;
		static bool WINDOW_IS_ACTIVE_SCALING;
		static Window* WINDOW_IS_ACTIVE_MOVING;

		void resetViewport();
		void initOpenGL();
		void update();

		//Passthrough
		void close();
		void finishRender();
		void bind();
		void unbind();
		void clear(int clearbits = GL_COLOR_BUFFER_BIT);

		//Events
		void onResize(std::function<void(int x, int y)> resize);

		//Setter
		void setSize(const ivec2& size);
		void setPosition(const ivec2& pos);
		void setKeyboard(Input::InputKeyboardClass* keyboard);
		void setMouse(Input::InputMouseClass* mouse);
		void setClearColor(vec4 color);
		void setVerticalSync(bool vsync);
		void hide(bool hiddenstat);
		void setTitle(const std::string& title);
		void setResizable(const bool& resizable);

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
