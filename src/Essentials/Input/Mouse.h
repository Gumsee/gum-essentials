#pragma once
#include "../Window.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>
#include <gum-maths.h>

#define CURSORTYPE_DEFAULT 0
#define CURSORTYPE_SCALE 1
#define CURSORTYPE_ARROW_LEFT_RIGHT 2

namespace Gum {
namespace Input
{
	class InputMouseClass
	{
	private:
		ivec2 v2Position, v2PreviousPosition, v2PositionDelta;
		vec2 snapPoint;
		int iMouseWheelState;
		int frameSize;
		int CursorType;
		vec3 rayDir;
		int mouseOnID;
		Gum::Window* pContextWindow;

		float lastClickTimeLeft = 0.0f;
		float lastClickTimeRight = 0.0f;

		bool defaulHideState;
		bool defaulTrapState;
		bool updateonclick;
		bool bIsBusy;
		bool bIsTrapped;
		bool bIsHidden;
		bool bIsSnapped;

	public:
        InputMouseClass(Gum::Window* context);
        InputMouseClass(InputMouseClass& other) = delete;
        InputMouseClass& operator=(InputMouseClass& other) = delete;

		bool LeftClick = false;
		bool LeftDoubleClick = false;
		bool RightClick = false;
		bool RightDoubleClick = false;
		bool MiddleClick = false;
		bool LeftRelease = false;
		bool RightRelease = false;
		bool MiddleRelease = false;
		std::string DragAndDropInfo;

		void calcRay();
		void update();
		void handleEvents(const sf::Event& event);
		void freeze(const bool& state);

		//Setter
		void setPosition(const ivec2& pos);
		void setGlobalPosition(const ivec2& pos);
		void setCursorType(const int& type);
		void setBusiness(const bool& val);
		void setSnapPoint(const vec2& snappoint);
		void trap(const bool& doTrap);
		void hide(const bool& doHide);
		void updateOnClick(const bool& bln);
		void setInstanceIDUnderMouse(const unsigned int& id);

		//Getter
		vec3 getRayDirection() const;
		vec2 getScreenPosition() const;
		vec2 getDelta() const;
		vec2 getPosition() const;
		float getDeltaDistance() const;
		float getDeltaDistanceNorm() const;
		int getMouseWheelState() const;
		int getCurrentPickedObjectID() const;
		int getCursorType() const;
		unsigned int getInstanceIDUnderMouse() const;
		bool isBusy() const;
		bool isHidden() const;
		bool isInArea(const vec2& pos, const vec2& size) const;
	};

	extern InputMouseClass* Mouse;
}}