#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GUM_KEY_UNKNOWN             GLFW_KEY_UNKNOWN
#define GUM_KEY_SPACE               GLFW_KEY_SPACE
#define GUM_KEY_APOSTROPHE          GLFW_KEY_APOSTROPHE
#define GUM_KEY_COMMA               GLFW_KEY_COMMA
#define GUM_KEY_MINUS               GLFW_KEY_MINUS
#define GUM_KEY_PERIOD              GLFW_KEY_PERIOD
#define GUM_KEY_SLASH               GLFW_KEY_SLASH
#define GUM_KEY_0                   GLFW_KEY_0
#define GUM_KEY_1                   GLFW_KEY_1
#define GUM_KEY_2                   GLFW_KEY_2
#define GUM_KEY_3                   GLFW_KEY_3
#define GUM_KEY_4                   GLFW_KEY_4
#define GUM_KEY_5                   GLFW_KEY_5
#define GUM_KEY_6                   GLFW_KEY_6
#define GUM_KEY_7                   GLFW_KEY_7
#define GUM_KEY_8                   GLFW_KEY_8
#define GUM_KEY_9                   GLFW_KEY_9
#define GUM_KEY_SEMICOLON           GLFW_KEY_SEMICOLON
#define GUM_KEY_EQUAL               GLFW_KEY_EQUAL
#define GUM_KEY_A                   GLFW_KEY_A
#define GUM_KEY_B                   GLFW_KEY_B
#define GUM_KEY_C                   GLFW_KEY_C
#define GUM_KEY_D                   GLFW_KEY_D
#define GUM_KEY_E                   GLFW_KEY_E
#define GUM_KEY_F                   GLFW_KEY_F
#define GUM_KEY_G                   GLFW_KEY_G
#define GUM_KEY_H                   GLFW_KEY_H
#define GUM_KEY_I                   GLFW_KEY_I
#define GUM_KEY_J                   GLFW_KEY_J
#define GUM_KEY_K                   GLFW_KEY_K
#define GUM_KEY_L                   GLFW_KEY_L
#define GUM_KEY_M                   GLFW_KEY_M
#define GUM_KEY_N                   GLFW_KEY_N
#define GUM_KEY_O                   GLFW_KEY_O
#define GUM_KEY_P                   GLFW_KEY_P
#define GUM_KEY_Q                   GLFW_KEY_Q
#define GUM_KEY_R                   GLFW_KEY_R
#define GUM_KEY_S                   GLFW_KEY_S
#define GUM_KEY_T                   GLFW_KEY_T
#define GUM_KEY_U                   GLFW_KEY_U
#define GUM_KEY_V                   GLFW_KEY_V
#define GUM_KEY_W                   GLFW_KEY_W
#define GUM_KEY_X                   GLFW_KEY_X
#define GUM_KEY_Y                   GLFW_KEY_Y
#define GUM_KEY_Z                   GLFW_KEY_Z
#define GUM_KEY_LEFT_BRACKET        GLFW_KEY_LEFT_BRACKET
#define GUM_KEY_BACKSLASH           GLFW_KEY_BACKSLASH
#define GUM_KEY_RIGHT_BRACKET       GLFW_KEY_RIGHT_BRACKET
#define GUM_KEY_GRAVE_ACCENT        GLFW_KEY_GRAVE_ACCENT
#define GUM_KEY_WORLD_1             GLFW_KEY_WORLD_1
#define GUM_KEY_WORLD_2             GLFW_KEY_WORLD_2
#define GUM_KEY_ESCAPE              GLFW_KEY_ESCAPE
#define GUM_KEY_ENTER               GLFW_KEY_ENTER
#define GUM_KEY_TAB                 GLFW_KEY_TAB
#define GUM_KEY_BACKSPACE           GLFW_KEY_BACKSPACE
#define GUM_KEY_INSERT              GLFW_KEY_INSERT
#define GUM_KEY_DELETE              GLFW_KEY_DELETE
#define GUM_KEY_RIGHT               GLFW_KEY_RIGHT
#define GUM_KEY_LEFT                GLFW_KEY_LEFT
#define GUM_KEY_DOWN                GLFW_KEY_DOWN
#define GUM_KEY_UP                  GLFW_KEY_UP
#define GUM_KEY_PAGE_UP             GLFW_KEY_PAGE_UP
#define GUM_KEY_PAGE_DOWN           GLFW_KEY_PAGE_DOWN
#define GUM_KEY_HOME                GLFW_KEY_HOME
#define GUM_KEY_END                 GLFW_KEY_END
#define GUM_KEY_CAPS_LOCK           GLFW_KEY_CAPS_LOCK
#define GUM_KEY_SCROLL_LOCK         GLFW_KEY_SCROLL_LOCK
#define GUM_KEY_NUM_LOCK            GLFW_KEY_NUM_LOCK
#define GUM_KEY_PRINT_SCREEN        GLFW_KEY_PRINT_SCREEN
#define GUM_KEY_PAUSE               GLFW_KEY_PAUSE
#define GUM_KEY_F1                  GLFW_KEY_F1
#define GUM_KEY_F2                  GLFW_KEY_F2
#define GUM_KEY_F3                  GLFW_KEY_F3
#define GUM_KEY_F4                  GLFW_KEY_F4
#define GUM_KEY_F5                  GLFW_KEY_F5
#define GUM_KEY_F6                  GLFW_KEY_F6
#define GUM_KEY_F7                  GLFW_KEY_F7
#define GUM_KEY_F8                  GLFW_KEY_F8
#define GUM_KEY_F9                  GLFW_KEY_F9
#define GUM_KEY_F10                 GLFW_KEY_F10
#define GUM_KEY_F11                 GLFW_KEY_F11
#define GUM_KEY_F12                 GLFW_KEY_F12
#define GUM_KEY_F13                 GLFW_KEY_F13
#define GUM_KEY_F14                 GLFW_KEY_F14
#define GUM_KEY_F15                 GLFW_KEY_F15
#define GUM_KEY_F16                 GLFW_KEY_F16
#define GUM_KEY_F17                 GLFW_KEY_F17
#define GUM_KEY_F18                 GLFW_KEY_F18
#define GUM_KEY_F19                 GLFW_KEY_F19
#define GUM_KEY_F20                 GLFW_KEY_F20
#define GUM_KEY_F21                 GLFW_KEY_F21
#define GUM_KEY_F22                 GLFW_KEY_F22
#define GUM_KEY_F23                 GLFW_KEY_F23
#define GUM_KEY_F24                 GLFW_KEY_F24
#define GUM_KEY_F25                 GLFW_KEY_F25
#define GUM_KEY_NUMPAD_0            GLFW_KEY_KP_0
#define GUM_KEY_NUMPAD_1            GLFW_KEY_KP_1
#define GUM_KEY_NUMPAD_2            GLFW_KEY_KP_2
#define GUM_KEY_NUMPAD_3            GLFW_KEY_KP_3
#define GUM_KEY_NUMPAD_4            GLFW_KEY_KP_4
#define GUM_KEY_NUMPAD_5            GLFW_KEY_KP_5
#define GUM_KEY_NUMPAD_6            GLFW_KEY_KP_6
#define GUM_KEY_NUMPAD_7            GLFW_KEY_KP_7
#define GUM_KEY_NUMPAD_8            GLFW_KEY_KP_8
#define GUM_KEY_NUMPAD_9            GLFW_KEY_KP_9
#define GUM_KEY_NUMPAD_DECIMAL      GLFW_KEY_KP_DECIMAL
#define GUM_KEY_NUMPAD_DIVIDE       GLFW_KEY_KP_DIVIDE
#define GUM_KEY_NUMPAD_MULTIPLY     GLFW_KEY_KP_MULTIPLY
#define GUM_KEY_NUMPAD_SUBTRACT     GLFW_KEY_KP_SUBTRACT
#define GUM_KEY_NUMPAD_ADD          GLFW_KEY_KP_ADD
#define GUM_KEY_NUMPAD_ENTER        GLFW_KEY_KP_ENTER
#define GUM_KEY_NUMPAD_EQUAL        GLFW_KEY_KP_EQUAL
#define GUM_KEY_LEFT_SHIFT          GLFW_KEY_LEFT_SHIFT
#define GUM_KEY_LEFT_CONTROL        GLFW_KEY_LEFT_CONTROL
#define GUM_KEY_LEFT_ALT            GLFW_KEY_LEFT_ALT
#define GUM_KEY_LEFT_SUPER          GLFW_KEY_LEFT_SUPER
#define GUM_KEY_RIGHT_SHIFT         GLFW_KEY_RIGHT_SHIFT
#define GUM_KEY_RIGHT_CONTROL       GLFW_KEY_RIGHT_CONTROL
#define GUM_KEY_RIGHT_ALT           GLFW_KEY_RIGHT_ALT
#define GUM_KEY_RIGHT_SUPER         GLFW_KEY_RIGHT_SUPER
#define GUM_KEY_MENU                GLFW_KEY_MENU
#define GUM_MOD_SHIFT               GLFW_MOD_SHIFT
#define GUM_MOD_CONTROL             GLFW_MOD_CONTROL
#define GUM_MOD_ALT                 GLFW_MOD_ALT
#define GUM_MOD_SUPER               GLFW_MOD_SUPER
#define GUM_MOD_CAPS_LOCK           GLFW_MOD_CAPS_LOCK
#define GUM_MOD_NUM_LOCK            GLFW_MOD_NUM_LOCK

namespace Gum {
class Window;

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

		Gum::Window* pContextWindow;

	public:
        InputKeyboardClass(Gum::Window* context);
        InputKeyboardClass(InputKeyboardClass& other) = delete;
        InputKeyboardClass& operator=(InputKeyboardClass& other) = delete;

		std::string key2string(const int& key) const;
		bool checkKeyPressed(const int& key) const;
		bool checkKeyReleased(const int& key) const;

		void addKeyCallback();

		//Setter
		void setBusiness(const bool& val);
		
		//Getter
		bool isBusy() const;
	};
}}