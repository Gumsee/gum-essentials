#include "Window.h"
#include "Output.h"
#include "Display.h"
#include <GLFW/glfw3.h>

namespace Gum
{
	Window::Window(bool fullscreen, std::string title, ivec2 windowsize, bool inpercent, bool borderless, Window* parentWindow)
	{
		this->bIsFullscreen = fullscreen;
		this->v2Size = windowsize;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_DECORATED, (int)!borderless);
		glfwWindowHint(GLFW_FLOATING, (int)(parentWindow != nullptr));


		if(v2Size == ivec2(0,0))
		{
			v2Size = ivec2(75,75);
			inpercent = true;
		}

		if(fullscreen)
		{
			v2Size = ivec2(100, 100);
			inpercent = true;
		}

		if(inpercent)
		{
			v2Size.x = Display::getScreenSize().x * ((float)v2Size.x / 100.0f);
			v2Size.y = Display::getScreenSize().y * ((float)v2Size.y / 100.0f);
		}
		GLFWwindow* parentGLFWWindow = nullptr;
		if(parentWindow != nullptr)
			parentGLFWWindow = parentWindow->getRenderWindow();
		pRenderWindow = glfwCreateWindow(v2Size.x, v2Size.y, title.c_str(), NULL, parentGLFWWindow);

		bind();
		setVerticalSync(false); // Enable vsync

		//LEARN HOWTO USE GLFW AND SET UP AN OPENGL CONTEXT

		/*sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 4;
		settings.majorVersion = 4;
		settings.minorVersion = 2;

		int style = sf::Style::Default;

		pRenderWindow = new sf::RenderWindow(videoMode, title, style,	settings);
		pRenderWindow->setMouseCursorVisible(false);
		//pRenderWindow->setMouseCursorGrabbed(true);
		//pRenderWindow->resetGLStates();
		
		v2RenderQuadPos = ivec2(0,0);
		fAspectRatio = (float)v2Size.y / (float)v2Size.x;
		fAspectRatioWidthToHeight = (float)v2Size.x / (float)v2Size.y;*/

		glfwSetWindowUserPointer(pRenderWindow, this);
		glfwSetWindowSizeCallback(pRenderWindow, [](GLFWwindow* window, int width, int height) {
				Window* context = (Window*)glfwGetWindowUserPointer(window);
				context->v2Size = ivec2(width, height);
				context->fAspectRatio = (float)context->v2Size.y / (float)context->v2Size.x;
				context->fAspectRatioWidthToHeight = (float)context->v2Size.x / (float)context->v2Size.y;
				context->m4ScreenMatrix = Gum::Maths::ortho((float)context->v2Size.y, (float)context->v2Size.x, 0.0f, 0.0f, -100.0f, 100.0f);
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
			Gum::Output::info("Renderer: "                + std::string(reinterpret_cast<const char*>(glrenderer)));
			Gum::Output::info("OpenGL version supported " + std::string(reinterpret_cast<const char*>(version)));
			Gum::Output::info("GLSL version supported "   + std::string(reinterpret_cast<const char*>(shaderversion)));
			Gum::Output::info("OpenGL Version "           + std::to_string(major) + "." + std::to_string(minor));
			Gum::Output::info("OpenGL Graphics Vendor: "  + std::string(reinterpret_cast<const char*>(vendor)));
		#endif
	}


	void Window::resetViewport()
	{
		glViewport(0.0f, 0.0f, getSize().x, getSize().y);
		glScissor(0.0f, 0.0f, getSize().x, getSize().y);
	}


	//Passthrough
	void Window::close()            	{ glfwDestroyWindow(pRenderWindow); }
	void Window::finishRender() 		{ glfwSwapBuffers(pRenderWindow); }
	void Window::bind()					{ glfwMakeContextCurrent(pRenderWindow); }
	void Window::clear(int clearbits) 	{ glClear(clearbits); }

	
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

		Gum::Output::info("Successfully initialized OpenGL Variables!");
	}


	//Setter
	void Window::setSize(const ivec2& size)    						{ glfwSetWindowSize(pRenderWindow, size.x, size.y); }
	void Window::setPosition(const ivec2& pos) 						{ glfwSetWindowPos(pRenderWindow, pos.x, pos.y); }
	void Window::setKeyboard(Input::InputKeyboardClass* keyboard) 	{ this->pKeyboard = keyboard; }
	void Window::setMouse(Input::InputMouseClass* mouse)		  	{ this->pMouse = mouse; }
	void Window::setClearColor(vec4 color)							{ glClearColor(color.r, color.g, color.b, color.a); }
	void Window::setVerticalSync(bool vsync)						{ glfwSwapInterval((int)vsync); }


	//Getter
	GLFWwindow* Window::getRenderWindow() const 					{ return this->pRenderWindow; }
	ivec2 Window::getSize() const              						{ return this->v2Size; }
	ivec2 Window::getPosition() const          						{ return this->v2Pos; }
	mat4 Window::getScreenMatrix() const							{ return this->m4ScreenMatrix; }
	Input::InputKeyboardClass* Window::getKeyboard()				{ return this->pKeyboard; }
	Input::InputMouseClass* Window::getMouse()						{ return this->pMouse; }
	float Window::getAspectRatio() const        					{ return this->fAspectRatio; }
	float Window::getAspectRatioWidthToHeight() const 				{ return this->fAspectRatioWidthToHeight; }
	bool Window::isFullscreen() const          						{ return this->bIsFullscreen; }
	bool Window::isOpen() const                						{ return !glfwWindowShouldClose(pRenderWindow); }
}