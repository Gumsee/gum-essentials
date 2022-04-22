#pragma once
#include <map>
#include "Keyboard.h"
#include <string>

namespace Gum {
namespace Input
{
	class InputControlsClass
	{
	private:
		int iCurrentKey;
		InputKeyboardClass* pKeyboard;
		std::map<std::string, int> mControls;

	public:
		InputControlsClass(InputKeyboardClass* keyboard);

		bool checkControl(const char* ControlName);

		//Setter
		void setCurrentKey(const int& character);
		void setControl(const std::string& ControlName, const int& key);
		
		//Getter
		char getCurrentKey() const;
	};
}}