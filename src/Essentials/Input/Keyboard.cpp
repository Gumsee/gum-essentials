#include "Keyboard.h"
#include "../Window.h"

#include <SFML/Window/Keyboard.hpp>
#include <iostream>

namespace Gum {
namespace Input
{
	std::string InputKeyboardClass::key2string(const sf::Keyboard::Key& key) const
	{
		std::string ret = "";
		switch(key)
		{
			case sf::Keyboard::Key::A: ret = "A"; break;
			case sf::Keyboard::Key::B: ret = "B"; break;
			case sf::Keyboard::Key::C: ret = "C"; break;
			case sf::Keyboard::Key::D: ret = "D"; break;
			case sf::Keyboard::Key::E: ret = "E"; break;
			case sf::Keyboard::Key::F: ret = "F"; break;
			case sf::Keyboard::Key::G: ret = "G"; break;
			case sf::Keyboard::Key::H: ret = "H"; break;
			case sf::Keyboard::Key::I: ret = "I"; break;
			case sf::Keyboard::Key::J: ret = "J"; break;
			case sf::Keyboard::Key::K: ret = "K"; break;
			case sf::Keyboard::Key::L: ret = "L"; break;
			case sf::Keyboard::Key::M: ret = "M"; break;
			case sf::Keyboard::Key::N: ret = "N"; break;
			case sf::Keyboard::Key::O: ret = "O"; break;
			case sf::Keyboard::Key::P: ret = "P"; break;
			case sf::Keyboard::Key::Q: ret = "Q"; break;
			case sf::Keyboard::Key::R: ret = "R"; break;
			case sf::Keyboard::Key::S: ret = "S"; break;
			case sf::Keyboard::Key::T: ret = "T"; break;
			case sf::Keyboard::Key::U: ret = "U"; break;
			case sf::Keyboard::Key::V: ret = "V"; break;
			case sf::Keyboard::Key::W: ret = "W"; break;
			case sf::Keyboard::Key::X: ret = "X"; break;
			case sf::Keyboard::Key::Y: ret = "Y"; break;
			case sf::Keyboard::Key::Z: ret = "Z"; break;

			case sf::Keyboard::Key::Num0: ret = "0"; break;
			case sf::Keyboard::Key::Num1: ret = "1"; break;
			case sf::Keyboard::Key::Num2: ret = "2"; break;
			case sf::Keyboard::Key::Num3: ret = "3"; break;
			case sf::Keyboard::Key::Num4: ret = "4"; break;
			case sf::Keyboard::Key::Num5: ret = "5"; break;
			case sf::Keyboard::Key::Num6: ret = "6"; break;
			case sf::Keyboard::Key::Num7: ret = "7"; break;
			case sf::Keyboard::Key::Num8: ret = "8"; break;
			case sf::Keyboard::Key::Num9: ret = "9"; break;

			case sf::Keyboard::Key::Numpad0: ret = "Numpad0"; break;
			case sf::Keyboard::Key::Numpad1: ret = "Numpad1"; break;
			case sf::Keyboard::Key::Numpad2: ret = "Numpad2"; break;
			case sf::Keyboard::Key::Numpad3: ret = "Numpad3"; break;
			case sf::Keyboard::Key::Numpad4: ret = "Numpad4"; break;
			case sf::Keyboard::Key::Numpad5: ret = "Numpad5"; break;
			case sf::Keyboard::Key::Numpad6: ret = "Numpad6"; break;
			case sf::Keyboard::Key::Numpad7: ret = "Numpad7"; break;
			case sf::Keyboard::Key::Numpad8: ret = "Numpad8"; break;
			case sf::Keyboard::Key::Numpad9: ret = "Numpad9"; break;

			case sf::Keyboard::Key::F1: 		ret = "F1"; break;
			case sf::Keyboard::Key::F2: 		ret = "F2"; break;
			case sf::Keyboard::Key::F3: 		ret = "F3"; break;
			case sf::Keyboard::Key::F4: 		ret = "F4"; break;
			case sf::Keyboard::Key::F5: 		ret = "F5"; break;
			case sf::Keyboard::Key::F6: 		ret = "F6"; break;
			case sf::Keyboard::Key::F7: 		ret = "F7"; break;
			case sf::Keyboard::Key::F8: 		ret = "F8"; break;
			case sf::Keyboard::Key::F9: 		ret = "F9"; break;
			case sf::Keyboard::Key::F10: 		ret = "F10"; break;
			case sf::Keyboard::Key::F11: 		ret = "F11"; break;
			case sf::Keyboard::Key::F12: 		ret = "F12"; break;
			case sf::Keyboard::Key::F13: 		ret = "F13"; break;
			case sf::Keyboard::Key::F14: 		ret = "F14"; break;
			case sf::Keyboard::Key::F15: 		ret = "F15"; break;

			case sf::Keyboard::Key::Escape: 	ret = "Escape"; break;
			case sf::Keyboard::Key::LControl: 	ret = "LControl"; break;
			case sf::Keyboard::Key::LShift: 	ret = "LShift"; break;
			case sf::Keyboard::Key::LAlt: 		ret = "LAlt"; break;
			case sf::Keyboard::Key::LSystem: 	ret = "LSystem"; break;
			case sf::Keyboard::Key::RControl: 	ret = "RControl"; break;
			case sf::Keyboard::Key::RShift: 	ret = "RShift"; break;
			case sf::Keyboard::Key::RAlt: 		ret = "RAlt"; break;
			case sf::Keyboard::Key::RSystem: 	ret = "RSystem"; break;
			case sf::Keyboard::Key::Menu: 		ret = "Menu"; break;
			case sf::Keyboard::Key::LBracket: 	ret = "LBracket"; break;
			case sf::Keyboard::Key::RBracket: 	ret = "RBracket"; break;
			case sf::Keyboard::Key::SemiColon: 	ret = ";"; break;
			case sf::Keyboard::Key::Comma: 		ret = ","; break;
			case sf::Keyboard::Key::Period: 	ret = "."; break;
			case sf::Keyboard::Key::Quote: 		ret = "\'"; break;
			case sf::Keyboard::Key::Slash: 		ret = "/"; break;
			case sf::Keyboard::Key::BackSlash: 	ret = "\\"; break;
			case sf::Keyboard::Key::Tilde: 		ret = "~"; break;
			case sf::Keyboard::Key::Equal: 		ret = "="; break;
			case sf::Keyboard::Key::Dash: 		ret = "-"; break;

			case sf::Keyboard::Key::Space: 		ret = "Space"; break;
			case sf::Keyboard::Key::Return: 	ret = "Return"; break;
			case sf::Keyboard::Key::BackSpace: 	ret = "Back"; break;
			case sf::Keyboard::Key::Tab: 		ret = "Tab"; break;

			case sf::Keyboard::Key::PageUp: 	ret = "Page Up"; break;
			case sf::Keyboard::Key::PageDown: 	ret = "Page Down"; break;
			case sf::Keyboard::Key::End: 		ret = "End"; break;
			case sf::Keyboard::Key::Home: 		ret = "Home"; break;
			case sf::Keyboard::Key::Insert: 	ret = "Insert"; break;
			case sf::Keyboard::Key::Delete: 	ret = "Delete"; break;
			case sf::Keyboard::Key::Pause: 		ret = "Paues"; break;

			case sf::Keyboard::Key::Add: 		ret = "+"; break;
			case sf::Keyboard::Key::Subtract: 	ret = "-"; break;
			case sf::Keyboard::Key::Multiply: 	ret = "*"; break;
			case sf::Keyboard::Key::Divide: 	ret = "/"; break;

			case sf::Keyboard::Key::Left: 		ret = "Left"; break;
			case sf::Keyboard::Key::Right: 		ret = "Right"; break;
			case sf::Keyboard::Key::Up: 		ret = "UP"; break;
			case sf::Keyboard::Key::Down: 		ret = "Down"; break;

			default: ret = ""; break;
		}

		return ret;
	}

	void InputKeyboardClass::handleEvents(const sf::Event& event)
	{
		switch(event.type)
		{
			case sf::Event::KeyPressed:
				escape = event.key.code == sf::Keyboard::Escape;
				system = event.key.system;
				shift = event.key.shift;
				alt = event.key.alt;
				control = event.key.control;

				currentKey = key2string(event.key.code);
				break;

			case sf::Event::KeyReleased:
				releasedChar = currentKey;
				currentKey = "";
				break;

			case sf::Event::TextEntered:
			default:
				break;
		}
	}

	bool InputKeyboardClass::checkKey(const int& key) const
	{ 
		return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key); 
	}

	bool InputKeyboardClass::checkKey(const std::string& key) const
	{ 
		return key == currentKey;
	}

	bool InputKeyboardClass::checkKeySinglepress(const std::string& key) const
	{
		return key == releasedChar;
	}

	void InputKeyboardClass::reset()
	{
		releasedChar = "";
	}

	void InputKeyboardClass::setBusiness(const bool& val)  { busy = val; }


	std::string InputKeyboardClass::getPressedKey() const  { return currentKey; }
	std::string InputKeyboardClass::getReleasedKey() const { return releasedChar; }
	bool InputKeyboardClass::isBusy() const                { return busy; }

	InputKeyboardClass* Keyboard = nullptr;
}}