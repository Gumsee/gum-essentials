#include "Window.h"
#include "Input/Mouse.h"
#include "Output.h"
#include "Display.h"
#include <GLFW/glfw3.h>
#include <X11/Xutil.h>
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#include <GLFW/glfw3native.h>
#include "MemoryManagement.h"

namespace Gum
{
	Window* Window::MainWindow = nullptr;
	Window* Window::CurrentlyBoundWindow = nullptr;
	bool Window::WINDOW_IS_ACTIVE_SCALING = false;

	Window::Window(std::string title, ivec2 windowsize, int properties, Window* parentWindow)
	{
		this->bIsResizable = properties & Properties::WINDOW_RESIZABLE;
		this->pParentWindow = parentWindow;
		this->bHidden = false;
		this->bScalingSnapped = false;
		this->bIsFullscreen = properties & Properties::WINDOW_FULLSCREEN;
		this->bHasBorder = !(bool)(properties & Properties::WINDOW_BORDERLESS);
		this->bIsFloating = properties & Properties::WINDOW_FLOATING;
		this->v2Size = windowsize;
		this->sTitle = title;
		this->bIsMaximized = false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_DECORATED, (int)bHasBorder);
		glfwWindowHint(GLFW_FLOATING, (int)bIsFloating);

		if(bIsFullscreen)
		{
			v2Size = ivec2(100, 100);
			properties |= Properties::WINDOW_SIZE_IN_PERCENT;
		}

		if(properties & Properties::WINDOW_SIZE_IN_PERCENT)
		{
			v2Size.x = Display::getScreenSize().x * ((float)v2Size.x / 100.0f);
			v2Size.y = Display::getScreenSize().y * ((float)v2Size.y / 100.0f);
		}
		this->v2PixelSize = vec2(1.0f) / (vec2)v2Size;
		
		GLFWwindow* parentGLFWWindow = NULL;
		if(parentWindow != nullptr)
			parentGLFWWindow = parentWindow->getRenderWindow();
		pRenderWindow = glfwCreateWindow(v2Size.x, v2Size.y, title.c_str(), NULL, parentGLFWWindow);

		glfwMakeContextCurrent(pRenderWindow);
		if(Window::MainWindow == nullptr)
			Window::MainWindow = this;
		
		bind();
		setVerticalSync(true); // Enable vsync

		glfwSetWindowUserPointer(pRenderWindow, this);
		glfwSetWindowSizeCallback(pRenderWindow, [](GLFWwindow* window, int width, int height) {
				Window* context = (Window*)glfwGetWindowUserPointer(window);
				context->v2Size = ivec2(width, height);
				context->fAspectRatio = (float)context->v2Size.y / (float)context->v2Size.x;
				context->fAspectRatioWidthToHeight = (float)context->v2Size.x / (float)context->v2Size.y;
				context->m4ScreenMatrix = Gum::Maths::ortho((float)context->v2Size.y, (float)context->v2Size.x, 0.0f, 0.0f, -100.0f, 100.0f);
				context->v2PixelSize = vec2(1.0f) / (vec2)context->v2Size;

				for(size_t i = 0; i < context->vResizeFunctions.size(); i++)
					context->vResizeFunctions[i](context->v2Size);
			}
		); //Maybe causes a scope violation
		fAspectRatio = (float)v2Size.y / (float)v2Size.x;
		fAspectRatioWidthToHeight = (float)v2Size.x / (float)v2Size.y;
		m4ScreenMatrix = Gum::Maths::ortho((float)v2Size.y, (float)v2Size.x, 0.0f, 0.0f, -100.0f, 100.0f);

		glfwSetWindowPosCallback(pRenderWindow, [](GLFWwindow* window, int x, int y) {
				Window* context = (Window*)glfwGetWindowUserPointer(window);
				context->v2Pos = ivec2(x, y);
			}
		); //Maybe causes a scope violation);

		pKeyboard = new Gum::Input::InputKeyboardClass(this);
		pMouse = new Gum::Input::InputMouseClass(this);
	}

	Window::~Window()
	{
		if(pRenderWindow != nullptr)
		{
			glfwDestroyWindow(pRenderWindow); 
			pRenderWindow = nullptr;
		}
		Gum::_delete(pKeyboard);
		Gum::_delete(pMouse);
	}


	void Window::resetViewport()
	{
		glViewport(0.0f, 0.0f, getSize().x, getSize().y);
		glScissor(0.0f, 0.0f, getSize().x, getSize().y);
	}

	void Window::update()
	{
		if(bIsResizable && !bHasBorder && this->pMouse != nullptr)
		{
			if (pMouse->isInArea(getSize() - ivec2(20, 20), getSize()))
			{
				pMouse->setCursor(Gum::Input::InputMouseClass::CURSOR_SHAPE::TOPLEFT_TO_BOTTOMRIGHT_RESIZE);
				if(pMouse->hasLeftClick() && !Gum::Input::Mouse::isBusy())
				{
					if(!Gum::Window::WINDOW_IS_ACTIVE_SCALING)
					{
						Gum::Window::WINDOW_IS_ACTIVE_SCALING = true;
						bScalingSnapped = true;
						Gum::Input::Mouse::setBusiness(true);
					}
				}
			}

			if(bScalingSnapped)
			{
				setSize(getSize() + Input::Mouse::getDelta());
				if(getSize().x < 100) { setSize(vec2(100, v2Size.y)); }
				if(getSize().y < 100) { setSize(vec2(v2Size.x, 100)); }

				if(!pMouse->hasLeftClick())
				{
					Gum::Window::WINDOW_IS_ACTIVE_SCALING = false;
					bScalingSnapped = false;
					Gum::Input::Mouse::setBusiness(false);
				}
			}
		}
	}


	//Passthrough
	void Window::close()            	
	{ 
		glfwSetWindowShouldClose(pRenderWindow, true);
	}
	void Window::minimize()
	{
		glfwIconifyWindow(pRenderWindow);
	}
	void Window::maximize(bool domaximize) 
	{ 
		if(domaximize)
			glfwMaximizeWindow(pRenderWindow); 
		else 
			glfwRestoreWindow(pRenderWindow); 
		bIsMaximized = domaximize;
	}
	void Window::finishRender() 		{ glfwSwapBuffers(pRenderWindow); }
	void Window::clear(int clearbits) 	{ glClear(clearbits); }
	void Window::bind()					
	{ 
		GLXContext context = glfwGetGLXContext(Window::MainWindow->getRenderWindow());
		GLXWindow win = glfwGetGLXWindow(pRenderWindow);
		glXMakeCurrent(glfwGetX11Display(), win, context);
		Window::CurrentlyBoundWindow = this;
		glViewport(0.0f, 0.0f, getSize().x, getSize().y);
	}
	void Window::unbind()
	{ 
		GLXContext context = glfwGetGLXContext(Window::MainWindow->getRenderWindow());
		GLXWindow win = glfwGetGLXWindow(Window::MainWindow->getRenderWindow());
		glXMakeCurrent(glfwGetX11Display(), win, context);
		Window::CurrentlyBoundWindow = Window::MainWindow;
		glViewport(0.0f, 0.0f, Window::MainWindow->getSize().x, Window::MainWindow->getSize().y);
	}

	
	void Window::initOpenGL()
	{
		//Initialize OpenGL Variables and glew
		Gum::Output::info("Initializing OpenGL Variables...");

		GLenum err = glewInit();

		if(err != GLEW_OK)
			Gum::Output::error("GLEW ERROR: " + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
		
		//glEnable(GL_STENCIL_TEST);
		//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glDepthFunc(GL_LEQUAL);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		#ifdef DEBUG
			int minor, major;
			const GLubyte* glrenderer = glGetString(GL_RENDERER); // get renderer string
			const GLubyte* version = glGetString(GL_VERSION); // version as a string
			//const GLubyte* Extensions = glGetString(GL_EXTENSIONS);
			const GLubyte* vendor = glGetString(GL_VENDOR);
			const GLubyte* shaderversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
			glGetIntegerv(GL_MAJOR_VERSION, &major);
			glGetIntegerv(GL_MINOR_VERSION, &minor);
			Gum::Output::info("");
			Gum::Output::info("Context Info:");
			Gum::Output::info("Renderer: "                + std::string(reinterpret_cast<const char*>(glrenderer)));
			Gum::Output::info("OpenGL version supported " + std::string(reinterpret_cast<const char*>(version)));
			Gum::Output::info("GLSL version supported "   + std::string(reinterpret_cast<const char*>(shaderversion)));
			Gum::Output::info("OpenGL Version "           + std::to_string(major) + "." + std::to_string(minor));
			Gum::Output::info("OpenGL Graphics Vendor: "  + std::string(reinterpret_cast<const char*>(vendor)));
		#endif

		Gum::Output::info("Successfully initialized OpenGL Variables!");
	}

	
	void Window::onResize(const std::function<void(ivec2 size)>& resize)
	{
		vResizeFunctions.push_back(resize);
	}


	//Setter
	void Window::setSize(const ivec2& size)    						{ glfwSetWindowSize(pRenderWindow, size.x, size.y); }
	void Window::setPosition(const ivec2& pos) 						{ glfwSetWindowPos(pRenderWindow, pos.x, pos.y); }
	void Window::setClearColor(vec4 color)							{ glClearColor(color.r, color.g, color.b, color.a); }
	void Window::setVerticalSync(bool vsync)						{ glfwSwapInterval((int)vsync); }
	void Window::setTitle(const std::string& title)					{ glfwSetWindowTitle(pRenderWindow, title.c_str()); this->sTitle = title; }
	void Window::setResizable(const bool& resizable)				{ this->bIsResizable = resizable; }
	void Window::hide(bool hiddenstat)                         				
	{ 
		bHidden = hiddenstat;
		if(bHidden)
			glfwHideWindow(pRenderWindow);
		else
			glfwShowWindow(pRenderWindow);
	}

	//Getter
	GLFWwindow* Window::getRenderWindow() const 					{ return this->pRenderWindow; }
	ivec2 Window::getSize() const              						{ return this->v2Size; }
	vec2 Window::getPixelSize() const          						{ return this->v2PixelSize; }
	ivec2 Window::getPosition() const          						{ return this->v2Pos; }
	mat4 Window::getScreenMatrix() const							{ return this->m4ScreenMatrix; }
	std::string Window::getTitle() const							{ return this->sTitle; }
	Input::InputKeyboardClass* Window::getKeyboard()				{ return this->pKeyboard; }
	Input::InputMouseClass* Window::getMouse()						{ return this->pMouse; }
	float Window::getAspectRatio() const        					{ return this->fAspectRatio; }
	float Window::getAspectRatioWidthToHeight() const 				{ return this->fAspectRatioWidthToHeight; }
	bool Window::isFullscreen() const          						{ return this->bIsFullscreen; }
	bool Window::isOpen() const                						{ return !glfwWindowShouldClose(pRenderWindow); }
	Gum::Window* Window::getParentWindow()							{ return this->pParentWindow; }
	bool Window::isMaximized() const								{ return this->bIsMaximized; }
	bool Window::isResizable() const								{ return this->bIsResizable; }
	
	Window* MainWindow = nullptr;
}
