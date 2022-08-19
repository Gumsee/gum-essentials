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
		Gum::Window *pParentWindow;
		ivec2 v2VisibleAreaSize;
		ivec2 v2Size, v2Pos;
		vec2 v2PixelSize;
		mat4 m4ScreenMatrix;
		float fAspectRatio, fAspectRatioWidthToHeight;
		bool bIsFullscreen;
		bool bHidden;
		bool bIsResizable;
		bool bHasBorder;
		bool bScalingSnapped;
		bool bIsFloating;
		bool bIsMaximized;
		std::string sTitle;

		std::vector<std::function<void(ivec2 size)> > vResizeFunctions;

		Input::InputKeyboardClass* pKeyboard;
		Input::InputMouseClass* pMouse;

	public:
		Window(std::string title, ivec2 windowsize, int properties, Window* parentWindow = nullptr);
		~Window();

		static Window* MainWindow;
		static Window* CurrentlyBoundWindow;
		static bool WINDOW_IS_ACTIVE_SCALING;

		enum Properties
		{
			WINDOW_DEFAULTS        = 0b00000,
			WINDOW_RESIZABLE       = 0b00001,
			WINDOW_FULLSCREEN      = 0b00010,
			WINDOW_FLOATING        = 0b00100,
			WINDOW_BORDERLESS      = 0b01000,
			WINDOW_SIZE_IN_PERCENT = 0b10000,
		};

		void resetViewport();
		void initOpenGL();
		void update();

		//Passthrough
		void close();
		void minimize();
		void maximize(bool domaximize);
		void finishRender();
		void bind();
		static void unbind();
		void clear(int clearbits = GL_COLOR_BUFFER_BIT);

		//Events
		void onResize(const std::function<void(ivec2 size)>& resize);

		//Setter
		void setSize(const ivec2& size);
		void setPosition(const ivec2& pos);
		void setClearColor(vec4 color);
		void setVerticalSync(bool vsync);
		void hide(bool hiddenstat);
		void setTitle(const std::string& title);
		void setResizable(const bool& resizable);

		//Getter
		GLFWwindow* getRenderWindow() const;
		ivec2 getSize() const;
		vec2 getPixelSize() const;
		ivec2 getPosition() const;
		mat4 getScreenMatrix() const;
		std::string getTitle() const;
		Input::InputKeyboardClass* getKeyboard();
		Input::InputMouseClass* getMouse();
		float getAspectRatio() const;
		float getAspectRatioWidthToHeight() const;
		Gum::Window* getParentWindow();
		bool isFullscreen() const;
		bool isOpen() const;
		bool isMaximized() const;
		bool isResizable() const;
	};
}
