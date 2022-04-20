#pragma once
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

namespace Gum {
namespace Input
{
	class InputKeyboardClass
	{
	private:
		bool busy;
		bool escape;
		bool alt;
		bool control;
		bool shift;
		bool system;

		std::string pressedChar;
		std::string releasedChar;
		std::string currentKey;

	public:
		void handleEvents(const sf::Event& event);
		void reset();
		std::string key2string(const sf::Keyboard::Key& key) const;
		bool checkKey(const int& key) const;
		bool checkKey(const std::string& key) const;
		bool checkKeySinglepress(const std::string& key) const;


		//Setter
		void setBusiness(const bool& val);
		
		//Getter
		std::string getPressedKey() const;
		std::string getReleasedKey() const;
		bool isBusy() const;
	};

	extern InputKeyboardClass* Keyboard;
}}