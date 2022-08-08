#pragma once
#include <string>
#include <gum-maths.h>

#define CURSORTYPE_DEFAULT 0
#define CURSORTYPE_SCALE 1
#define CURSORTYPE_ARROW_LEFT_RIGHT 2

namespace Gum {
class Window;

namespace Input
{
	class InputMouseClass
	{
	private:
		ivec2 v2Position, v2PreviousPosition;
		ivec2 snapPoint;
		int iMouseWheelState;
		int frameSize;
		int CursorType;
		vec3 rayDir;
		int mouseOnID;
		Gum::Window* pContextWindow;

		float lastClickTimeLeft = 0.0f;
		float lastClickTimeRight = 0.0f;

		bool LeftDown = false;
		bool RightDown = false;
		bool LeftClickOnce = false;
		bool RightClickOnce = false;
		bool LeftReleased = false;
		bool RightReleased = false;
		bool LeftDoubleClick = false;
		bool RightDoubleClick = false;

		bool defaulHideState;
		bool defaulTrapState;
		bool updateonclick;
		bool bIsTrapped;
		bool bIsHidden;
		bool bIsSnapped;

	public:
        InputMouseClass(Gum::Window* context);
        InputMouseClass(InputMouseClass& other) = delete;
        InputMouseClass& operator=(InputMouseClass& other) = delete;
		
		enum CURSOR_SHAPE 
		{
			DEFAULT,
			HORIZONTAL_RESIZE,
			VERTICAL_RESIZE,
			HAND,
			CROSSHAIR,
			IBEAM,
		};

		std::string DragAndDropInfo;

		void calcRay();		
		void reset();
		void freeze(const bool& state);

		//Setter
		void setContextWindow(Gum::Window* context);
		void setPosition(const ivec2& pos);
		void setGlobalPosition(const ivec2& pos);
		void setCursorType(const int& type);
		void setSnapPoint(const ivec2& snappoint);
		void trap(const bool& doTrap);
		void hide(const bool& doHide);
		void updateOnClick(const bool& bln);
		void setInstanceIDUnderMouse(const unsigned int& id);
		void setCursor(uint8_t shape);

		//Getter
		vec3 getRayDirection() const;
		ivec2 getPosition() const;
		float getDeltaDistanceNorm() const;
		int getMouseWheelState() const;
		int getCurrentPickedObjectID() const;
		int getCursorType() const;
		unsigned int getInstanceIDUnderMouse() const;
		bool isHidden() const;
		bool isInArea(const ivec2& pos, const ivec2& size) const;
		bool hasLeftClick();
		bool hasRightClick();
		bool isLeftDown();
		bool isRightDown();
		bool hasLeftDoubleClick();
		bool hasRightDoubleClick();
		bool hasLeftRelease();
		bool hasRightRelease();
		bool hasMiddleClick();
		bool hasMiddleRelease();
	};

	namespace Mouse 
	{
		extern void update(Gum::Window* mainwindow);
		extern ivec2 getScreenPosition();
		extern ivec2 getDelta();
		extern bool isBusy();
		extern void setBusiness(const bool& val);
		extern void setCursor(Gum::Window* window, uint8_t shape);
	}
}}