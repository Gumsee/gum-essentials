#pragma once
#include <map>
#include "Keyboard.h"
#include <string>

namespace Gum {
namespace Input {
namespace Controls
{
	void init();
	bool checkControl(const char* ControlName, InputKeyboardClass* keyboard);

	//Setter
	void setCurrentKey(const int& character);
	void setControl(const std::string& ControlName, const int& key);
	
	//Getter
	char getCurrentKey();
}}}