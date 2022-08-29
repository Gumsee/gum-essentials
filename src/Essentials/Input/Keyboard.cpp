#include "Keyboard.h"
#include "../Window.h"
#include "../Output.h"
#include "GLFW/glfw3.h"
#include <locale>
#include <codecvt>

namespace Gum {
namespace Input
{
	InputKeyboardClass::InputKeyboardClass(Gum::Window* context)
	{
		pContextWindow = context;
		iLastPressedKey = 0;
		iLastReleasedKey = 0;
		u8TextInput = "";

		glfwSetCharCallback(pContextWindow->getRenderWindow(), [](GLFWwindow* window, unsigned int codepoint) {
			InputKeyboardClass* keyboard = ((Window*)glfwGetWindowUserPointer(window))->getKeyboard();

			std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
			keyboard->u8TextInput = convert.to_bytes(codepoint);
		});

		glfwSetKeyCallback(pContextWindow->getRenderWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			InputKeyboardClass* keyboard = ((Window*)glfwGetWindowUserPointer(window))->getKeyboard();
			if (action == GLFW_PRESS || action == GLFW_REPEAT)  { keyboard->iLastPressedKey  = key; }
			if (action == GLFW_RELEASE) 						{ keyboard->iLastReleasedKey = key; }
		});

	}

	void InputKeyboardClass::reset()
	{
		this->u8TextInput = "";
		this->iLastPressedKey = 0;
		this->iLastReleasedKey = 0;
	}


	std::string InputKeyboardClass::key2string(const int& key) const
	{
		std::string ret = "";
		switch(key)
		{
			case GUM_KEY_A: ret = "A"; break;
			case GUM_KEY_B: ret = "B"; break;
			case GUM_KEY_C: ret = "C"; break;
			case GUM_KEY_D: ret = "D"; break;
			case GUM_KEY_E: ret = "E"; break;
			case GUM_KEY_F: ret = "F"; break;
			case GUM_KEY_G: ret = "G"; break;
			case GUM_KEY_H: ret = "H"; break;
			case GUM_KEY_I: ret = "I"; break;
			case GUM_KEY_J: ret = "J"; break;
			case GUM_KEY_K: ret = "K"; break;
			case GUM_KEY_L: ret = "L"; break;
			case GUM_KEY_M: ret = "M"; break;
			case GUM_KEY_N: ret = "N"; break;
			case GUM_KEY_O: ret = "O"; break;
			case GUM_KEY_P: ret = "P"; break;
			case GUM_KEY_Q: ret = "Q"; break;
			case GUM_KEY_R: ret = "R"; break;
			case GUM_KEY_S: ret = "S"; break;
			case GUM_KEY_T: ret = "T"; break;
			case GUM_KEY_U: ret = "U"; break;
			case GUM_KEY_V: ret = "V"; break;
			case GUM_KEY_W: ret = "W"; break;
			case GUM_KEY_X: ret = "X"; break;
			case GUM_KEY_Y: ret = "Y"; break;
			case GUM_KEY_Z: ret = "Z"; break;

			case GUM_KEY_0: ret = "0"; break;
			case GUM_KEY_1: ret = "1"; break;
			case GUM_KEY_2: ret = "2"; break;
			case GUM_KEY_3: ret = "3"; break;
			case GUM_KEY_4: ret = "4"; break;
			case GUM_KEY_5: ret = "5"; break;
			case GUM_KEY_6: ret = "6"; break;
			case GUM_KEY_7: ret = "7"; break;
			case GUM_KEY_8: ret = "8"; break;
			case GUM_KEY_9: ret = "9"; break;

			case GUM_KEY_NUMPAD_0: ret = "Numpad0"; break;
			case GUM_KEY_NUMPAD_1: ret = "Numpad1"; break;
			case GUM_KEY_NUMPAD_2: ret = "Numpad2"; break;
			case GUM_KEY_NUMPAD_3: ret = "Numpad3"; break;
			case GUM_KEY_NUMPAD_4: ret = "Numpad4"; break;
			case GUM_KEY_NUMPAD_5: ret = "Numpad5"; break;
			case GUM_KEY_NUMPAD_6: ret = "Numpad6"; break;
			case GUM_KEY_NUMPAD_7: ret = "Numpad7"; break;
			case GUM_KEY_NUMPAD_8: ret = "Numpad8"; break;
			case GUM_KEY_NUMPAD_9: ret = "Numpad9"; break;

			case GUM_KEY_F1: 		ret = "F1"; break;
			case GUM_KEY_F2: 		ret = "F2"; break;
			case GUM_KEY_F3: 		ret = "F3"; break;
			case GUM_KEY_F4: 		ret = "F4"; break;
			case GUM_KEY_F5: 		ret = "F5"; break;
			case GUM_KEY_F6: 		ret = "F6"; break;
			case GUM_KEY_F7: 		ret = "F7"; break;
			case GUM_KEY_F8: 		ret = "F8"; break;
			case GUM_KEY_F9: 		ret = "F9"; break;
			case GUM_KEY_F10: 		ret = "F10"; break;
			case GUM_KEY_F11: 		ret = "F11"; break;
			case GUM_KEY_F12: 		ret = "F12"; break;
			case GUM_KEY_F13: 		ret = "F13"; break;
			case GUM_KEY_F14: 		ret = "F14"; break;
			case GUM_KEY_F15: 		ret = "F15"; break;
			case GUM_KEY_F16: 		ret = "F16"; break;
			case GUM_KEY_F17: 		ret = "F17"; break;
			case GUM_KEY_F18: 		ret = "F18"; break;
			case GUM_KEY_F19: 		ret = "F19"; break;
			case GUM_KEY_F20: 		ret = "F20"; break;
			case GUM_KEY_F21: 		ret = "F21"; break;
			case GUM_KEY_F22: 		ret = "F22"; break;
			case GUM_KEY_F23: 		ret = "F23"; break;
			case GUM_KEY_F24: 		ret = "F24"; break;
			case GUM_KEY_F25: 		ret = "F25"; break;

			case GUM_KEY_ESCAPE: 		ret = "Escape"; break;
			case GUM_KEY_LEFT_CONTROL: 	ret = "LControl"; break;
			case GUM_KEY_LEFT_SHIFT: 	ret = "LShift"; break;
			case GUM_KEY_LEFT_ALT: 		ret = "LAlt"; break;
			case GUM_KEY_LEFT_SUPER: 	ret = "LSystem"; break;
			case GUM_KEY_RIGHT_CONTROL: ret = "RControl"; break;
			case GUM_KEY_RIGHT_SHIFT: 	ret = "RShift"; break;
			case GUM_KEY_RIGHT_ALT: 	ret = "RAlt"; break;
			case GUM_KEY_RIGHT_SUPER: 	ret = "RSystem"; break;
			case GUM_KEY_MENU: 			ret = "Menu"; break;
			case GUM_KEY_LEFT_BRACKET: 	ret = "LBracket"; break;
			case GUM_KEY_RIGHT_BRACKET: ret = "RBracket"; break;
			case GUM_KEY_SEMICOLON: 	ret = ";"; break;
			case GUM_KEY_COMMA: 		ret = ","; break;
			case GUM_KEY_PERIOD: 		ret = "."; break;
			case GLFW_KEY_APOSTROPHE: 	ret = "\'"; break;
			case GUM_KEY_SLASH: 		ret = "/"; break;
			case GUM_KEY_BACKSLASH: 	ret = "\\"; break;
			//case GUM_KEY_Tilde: 		ret = "~"; break;
			case GUM_KEY_EQUAL: 		ret = "="; break;
			case GUM_KEY_MINUS: 		ret = "-"; break;

			case GUM_KEY_SPACE: 		ret = "Space"; break;
			case GUM_KEY_ENTER: 		ret = "Return"; break;
			case GUM_KEY_BACKSPACE: 	ret = "Back"; break;
			case GUM_KEY_TAB: 			ret = "Tab"; break;

			case GUM_KEY_PAGE_UP: 		ret = "Page Up"; break;
			case GUM_KEY_PAGE_DOWN: 	ret = "Page Down"; break;
			case GUM_KEY_END: 			ret = "End"; break;
			case GUM_KEY_HOME: 			ret = "Home"; break;
			case GUM_KEY_INSERT: 		ret = "Insert"; break;
			case GUM_KEY_DELETE: 		ret = "Delete"; break;
			case GUM_KEY_PAUSE: 		ret = "Paues"; break;

			case GUM_KEY_NUMPAD_ADD: 		ret = "+"; break;
			case GUM_KEY_NUMPAD_SUBTRACT: 	ret = "-"; break;
			case GUM_KEY_NUMPAD_MULTIPLY: 	ret = "*"; break;
			case GUM_KEY_NUMPAD_DIVIDE: 	ret = "/"; break;

			case GUM_KEY_LEFT: 		ret = "Left"; break;
			case GUM_KEY_RIGHT: 		ret = "Right"; break;
			case GUM_KEY_UP: 		ret = "UP"; break;
			case GUM_KEY_DOWN: 		ret = "Down"; break;

			default: ret = ""; break;
		}

		return ret;
	}

	bool InputKeyboardClass::checkLastPressedKey(const int& key) const
	{ 
		return iLastPressedKey == key; 
	}

	bool InputKeyboardClass::checkLastReleasedKey(const int& key) const
	{ 
		return iLastReleasedKey == key; 
	}

	bool InputKeyboardClass::checkKeyPressed(const int& key) const
	{ 
		return glfwGetKey(pContextWindow->getRenderWindow(), key) == GLFW_PRESS; 
	}

	bool InputKeyboardClass::checkKeyReleased(const int& key) const
	{ 
		return glfwGetKey(pContextWindow->getRenderWindow(), key) == GLFW_RELEASE; 
	}

	void InputKeyboardClass::setBusiness(const bool& val)  { busy = val; }


	bool InputKeyboardClass::isBusy() const           { return busy; }
	std::string InputKeyboardClass::getTextInput() const { return this->u8TextInput; }
}}