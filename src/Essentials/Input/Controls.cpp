#include "Controls.h"
#include "../Output.h"
#include "Keyboard.h"

namespace Gum {
namespace Input
{
	InputControlsClass::InputControlsClass(InputKeyboardClass* keyboard)
	{
		Gum::Output::log("Setting Default Controls!");
		setControl("Forward", GUM_KEY_W);
		setControl("Backward", GUM_KEY_S);
		setControl("Right", GUM_KEY_D);
		setControl("Left", GUM_KEY_A);
		setControl("Jump", GUM_KEY_SPACE);
		setControl("Up", GUM_KEY_SPACE);
		setControl("Down", GUM_KEY_LEFT_CONTROL);
		setControl("Speed", GUM_KEY_F);
		pKeyboard = keyboard;
	}

	bool InputControlsClass::checkControl(const char* ControlName)
	{
		return pKeyboard->checkKeyPressed(mControls[ControlName]);
	}

	//Setter
	void InputControlsClass::setCurrentKey(const int& character)                        { iCurrentKey = character; }
	void InputControlsClass::setControl(const std::string& ControlName, const int& key) { mControls[ControlName] = key; }

	//Getter
	char InputControlsClass::getCurrentKey() const                                      { return iCurrentKey; }
}}