#include "Controls.h"
#include "../Output.h"

namespace Gum {
namespace Input
{
	InputControlsClass::InputControlsClass()
	{
		Gum::Output::log("Setting Default Controls!");
		setControl("Forward", sf::Keyboard::Key::W);
		setControl("Backward", sf::Keyboard::Key::S);
		setControl("Right", sf::Keyboard::Key::D);
		setControl("Left", sf::Keyboard::Key::A);
		setControl("Jump", sf::Keyboard::Key::Space);
		setControl("Up", sf::Keyboard::Key::Space);
		setControl("Down", sf::Keyboard::Key::LControl);
		setControl("Speed", sf::Keyboard::F);
	}

	bool InputControlsClass::checkControl(const char* ControlName)
	{
		return sf::Keyboard::isKeyPressed(mControls[ControlName]);
	}

	//Setter
	void InputControlsClass::setCurrentKey(const int& character)                                      { iCurrentKey = character; }
	void InputControlsClass::setControl(const std::string& ControlName, const sf::Keyboard::Key& key) { mControls[ControlName] = key; }

	//Getter
	char InputControlsClass::getCurrentKey() const                                                    { return iCurrentKey; }

	InputControlsClass* Controls = nullptr;
}}