#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <gum-maths.h>

namespace Gum
{
	class Window
	{
	private:
		//extern SDL_Window *handle;
		//extern SDL_GLContext maincontext;
		//extern SDL_Event event;
		sf::RenderWindow *pRenderWindow;
		ivec2 v2RenderQuadSize;
		ivec2 v2RenderQuadPos;
		ivec2 v2VisibleAreaSize;
		ivec2 v2Size;
		mat4 m4ScreenMatrix;
		float fAspectRatio, fAspectRatioWidthToHeight;
		bool bIsFullscreen = false;

	public:
		Window(bool fullscreen, std::string title, ivec2 windowsize, bool inpercent);

		void resize(const ivec2& size);
		void handleEvents(sf::Event& event);

		void finishRender();
		void resetViewport();

		//Passthrough
		void close();
		bool pollEvent(sf::Event& event) const;
		static void initOpenGL();

		//Setter
		void setSize(const ivec2& size);
		void setPosition(const ivec2& pos);

		//Getter
		sf::RenderWindow* getRenderWindow() const;
		ivec2 getSize() const;
		ivec2 getPosition() const;
		ivec2 getScreenSize() const;
		ivec2 getRenderQuadSize() const;
		ivec2 getRenderQuadPos() const;
		mat4 getScreenMatrix() const;
		float getAspectRatio() const;
		float getAspectRatioWidthToHeight() const;
		bool isFullscreen() const;
		bool isOpen() const;
	};
}
