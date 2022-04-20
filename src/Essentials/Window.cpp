#include "Window.h"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>
#include "Output.h"
#include <GL/glew.h>

namespace Gum
{
	Window::Window(bool fullscreen, std::string title, ivec2 windowsize, bool inpercent)
	{
		bIsFullscreen = fullscreen;

		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 4;
		settings.majorVersion = 4;
		settings.minorVersion = 2;

		int style = sf::Style::Default;
		if(windowsize == ivec2(0,0))
		{
			windowsize = ivec2(75,75);
			inpercent = true;
		}

		if(fullscreen)
		{
			windowsize = ivec2(100, 100);
			style = sf::Style::None;
			inpercent = true;
		}

		sf::VideoMode videoMode(windowsize.x, windowsize.y);
		if(inpercent)
		{
			videoMode.width  = sf::VideoMode::getDesktopMode().width * ((float)windowsize.x / 100.0f);
			videoMode.height = sf::VideoMode::getDesktopMode().height * ((float)windowsize.y / 100.0f);
		}

		pRenderWindow = new sf::RenderWindow(videoMode, title, style,	settings);
		pRenderWindow->setVerticalSyncEnabled(false);
		pRenderWindow->setMouseCursorVisible(false);
		//pRenderWindow->setMouseCursorGrabbed(true);
		//pRenderWindow->resetGLStates();

		v2Size = ivec2(pRenderWindow->getSize().x, pRenderWindow->getSize().y);

		if(v2RenderQuadSize != ivec2(0,0))
			v2RenderQuadSize = v2Size * v2RenderQuadSize;
		else
			v2RenderQuadSize = v2Size;
		
		v2RenderQuadPos = ivec2(0,0);
		fAspectRatio = (float)v2Size.y / (float)v2Size.x;
		fAspectRatioWidthToHeight = (float)v2Size.x / (float)v2Size.y;

		resize(v2Size);

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

	void Window::handleEvents(sf::Event& event)
	{
		switch(event.type)
		{
			case sf::Event::Resized:
				resize(ivec2(event.size.width, event.size.height));
				break;

			case sf::Event::Closed:
				close();
				break;
			case sf::Event::LostFocus:
			case sf::Event::GainedFocus:
			default:
				break;
		}
	}


	void Window::resetViewport()
	{
		glViewport(0.0f, 0.0f, getSize().x, getSize().y);
		glScissor(0.0f, 0.0f, getSize().x, getSize().y);
	}

	void Window::resize(const ivec2& size)
	{
		v2RenderQuadSize = size;
		fAspectRatio = (float)size.y / (float)size.x;
		fAspectRatioWidthToHeight = (float)size.x / (float)size.y;
		v2Size = size;
		m4ScreenMatrix = Gum::Maths::ortho((float)v2Size.y, (float)v2Size.x, 0.0f, 0.0f, -100.0f, 100.0f);
	}


	void Window::finishRender()
	{
		//SDL_GL_SwapWindow(Gum::Window->handle);
		pRenderWindow->display();
	}


	//Passthrough
	void Window::close()                            { pRenderWindow->close(); }
	bool Window::pollEvent(sf::Event& event) const  { return pRenderWindow->pollEvent(event); }

	
	void Window::initOpenGL()
	{
		//Initialize OpenGL Variables and glew
		Gum::Output::info("Initializing OpenGL Variables...");

		GLenum err = glewInit();

		if(err != GLEW_OK)
			Gum::Output::error("GLEW ERROR: " + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glDepthFunc(GL_LEQUAL);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		//glEnable(GL_STENCIL_TEST);
		//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		Gum::Output::info("Successfully initialized OpenGL Variables!");
	}


	//Setter
	void Window::setSize(const ivec2& size)    { pRenderWindow->setSize(sf::Vector2u(size.x, size.y)); resize(size); }
	void Window::setPosition(const ivec2& pos) { pRenderWindow->setPosition(sf::Vector2i(pos.x, pos.y)); }


	//Getter
	sf::RenderWindow* Window::getRenderWindow() const 	{ return this->pRenderWindow; }
	ivec2 Window::getSize() const              			{ return this->v2Size; }
	ivec2 Window::getPosition() const          			{ return ivec2(pRenderWindow->getPosition().x, pRenderWindow->getPosition().y); }
	ivec2 Window::getScreenSize() const        			{ return ivec2(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height); }
	ivec2 Window::getRenderQuadSize() const    			{ return this->v2RenderQuadSize; }
	ivec2 Window::getRenderQuadPos() const     			{ return this->v2RenderQuadPos; }
	mat4 Window::getScreenMatrix() const				{ return this->m4ScreenMatrix; }
	float Window::getAspectRatio() const        		{ return this->fAspectRatio; }
	float Window::getAspectRatioWidthToHeight() const 	{ return this->fAspectRatioWidthToHeight; }
	bool Window::isFullscreen() const          			{ return this->bIsFullscreen; }
	bool Window::isOpen() const                			{ return pRenderWindow->isOpen(); }
}