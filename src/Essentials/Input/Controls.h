#pragma once
#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <string>

namespace Gum {
namespace Input
{
	class InputControlsClass
	{
	private:
		int iCurrentKey;
		std::map<std::string, sf::Keyboard::Key> mControls;

	public:
		InputControlsClass();

		bool checkControl(const char* ControlName);

		//Setter
		void setCurrentKey(const int& character);
		void setControl(const std::string& ControlName, const sf::Keyboard::Key& key);
		
		//Getter
		char getCurrentKey() const;
	};

	extern InputControlsClass* Controls;
}}