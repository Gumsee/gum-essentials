#include "Mouse.h"
#include "../Output.h"
#include "../Window.h"
#include "../Tools.h"
#include "../FPS.h"

#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_NATIVE_INCLUDE_NONE
#include "GLFW/glfw3native.h"
#include <GLFW/glfw3.h>
#include <X11/Xlib.h>
#include <iostream>

static GLFWcursor *pDefaultCursor, *pIBeamCursor, *pCrosshairCursor, *pHandCursor, *pVResizeCursor, *pHResizeCursor, *pNWSEResizeCursor, *pNESWResizeCursor, *pAllResizeCursor, *pNotAllowedCursor;
GLFWcursor *pActiveCursor;

namespace Gum {
namespace Input
{
    InputMouseClass::InputMouseClass(Gum::Window* context)
    {
        this->v2Position = ivec2(0,0);
        this->v2PreviousPosition = ivec2(0,0);
        this->pContextWindow = context;
        this->v2LeftClickPosition = ivec2(-1, -1);

        updateonclick = false;
        bIsTrapped = false;

        iMouseWheelState = 0;
        CursorType = 0;
        frameSize = 0;
        rayDir = vec3(0);
        DragAndDropInfo = "";
        mouseOnID = -1;
        
        //glfwSetInputMode(pContextWindow->getRenderWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        if (glfwRawMouseMotionSupported())
            glfwSetInputMode(pContextWindow->getRenderWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        
        glfwSetCursorPosCallback(pContextWindow->getRenderWindow(), [](GLFWwindow* window, double x, double y) {
				InputMouseClass* mouseptr = ((Window*)glfwGetWindowUserPointer(window))->getMouse();
                mouseptr->v2PreviousPosition = mouseptr->v2Position;
                mouseptr->v2Position.x = x;
                mouseptr->v2Position.y = y;

                //mouseptr->v2PositionDelta = mouseptr->v2Position - mouseptr->v2PreviousPosition;
                mouseptr->calcRay();
            }
        );

        glfwSetMouseButtonCallback(pContextWindow->getRenderWindow(), [](GLFWwindow* window, int button, int action, int mods) {
				InputMouseClass* mouseptr = ((Window*)glfwGetWindowUserPointer(window))->getMouse();
                if(button == GLFW_MOUSE_BUTTON_LEFT)
                {
                    if(action == GLFW_PRESS)
                    {
                        mouseptr->LeftClickOnce = true;
                        mouseptr->LeftDown = true;
                        mouseptr->v2LeftClickPosition = mouseptr->getPosition();
                    }
                    else
                    {
                        if(mouseptr->LeftClickOnce)
                        { 
                            if(mouseptr->lastClickTimeLeft < 0.5f)
                            {
                                mouseptr->LeftDoubleClick = true;
                                mouseptr->lastClickTimeLeft = 0.5f;
                            }
                            else
                                mouseptr->lastClickTimeLeft = 0;
                        }
                        mouseptr->LeftDown = false;
                    }
                }

                if(button == GLFW_MOUSE_BUTTON_RIGHT)
                {
                    if(action == GLFW_PRESS)
                    {
                        mouseptr->RightClickOnce = true;
                        mouseptr->RightDown = true;
                    }
                    else
                    {
                        if(mouseptr->RightClickOnce)
                        {
                            if(mouseptr->lastClickTimeRight < 0.5f)
                            {
                                mouseptr->RightDoubleClick = true;
                                mouseptr->lastClickTimeRight = 0.5f;
                            }
                            else
                                mouseptr->lastClickTimeRight = 0;
                        }
                        mouseptr->RightDown = false;
                    }
                }

                if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
                    mouseptr->LeftReleased = true; 
                else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
                    mouseptr->RightReleased = true; 
            }
        );

        glfwSetScrollCallback(pContextWindow->getRenderWindow(), [](GLFWwindow* window, double xoffset, double yoffset) {
                InputMouseClass* mouseptr = ((Window*)glfwGetWindowUserPointer(window))->getMouse();
                mouseptr->iMouseWheelState = yoffset;
            }
        );
    }



	float InputMouseClass::getDeltaDistanceNorm() const
	{		
		vec2 normPos = (v2Position - pContextWindow->getPosition()) / pContextWindow->getSize();
		vec2 normOldPos = (v2PreviousPosition - pContextWindow->getPosition()) / pContextWindow->getSize();

		return vec2::distance(normPos, normOldPos); 
	}


	void InputMouseClass::calcRay()
	{
		/*float frameX = (float)renderFrame.x;
        float frameY = (float)renderFrame.y;
        vec4 screen_space;

        //screen space to normalized device space
		screen_space.x = (2 * (getPosition().x / frameX)) - 1;
		screen_space.y = -((2 * (getPosition().y / frameY)) - 1);
        screen_space.z = -1.0f;
		screen_space.z = 1.0f;

		mat4 invertedProjection = mat4::inverse(GumEngine::ActiveCamera->getProjectionMatrix());
		vec4 eye_space = mat4::transpose(invertedProjection) * screen_space;
		eye_space.z = -1.0f;
		eye_space.w = 0.0f;

        //eye space to world space
		vec4 worldspace = GumEngine::ActiveCamera->getViewMatrix() * eye_space;

		rayDir = worldspace;
        rayDir = vec3::normalize(rayDir);*/
	}

    void InputMouseClass::reset()
    {
        lastClickTimeLeft += FPS::get();
        lastClickTimeRight += FPS::get();
        if(!LeftDown)
            v2LeftClickPosition = ivec2(-1, -1);
		LeftReleased = false;
		RightReleased = false;
        LeftDoubleClick = false;
        RightDoubleClick = false;

		iMouseWheelState = 0;
        CursorType = 0;
        frameSize = 0;

        
        glfwSetCursor(pContextWindow->getRenderWindow(), pActiveCursor);
        setCursor(CURSOR_SHAPE::DEFAULT);


        if(bIsTrapped) { setPosition(pContextWindow->getSize() / 2); }
    }

	bool InputMouseClass::isInArea(const ivec2& pos, const ivec2& size) const
	{
        return Tools::checkPointInBox(getPosition(), bbox2i(pos, size));
	}

    //Setter
    void InputMouseClass::setContextWindow(Gum::Window* context)            { this->pContextWindow = context; }
	void InputMouseClass::setCursorType(const int& type) 		            { this->CursorType = type; }
	void InputMouseClass::updateOnClick(const bool& bln)    	            { this->updateonclick = bln; }
	void InputMouseClass::trap(const bool& doTrap) 			                { this->bIsTrapped = doTrap; }
	void InputMouseClass::hide(const bool& doHide) 			                { glfwSetInputMode(pContextWindow->getRenderWindow(), GLFW_CURSOR, doHide ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL); }
    void InputMouseClass::setInstanceIDUnderMouse(const unsigned int& id)   { this->mouseOnID = id; }
    void InputMouseClass::setPosition(const ivec2& pos) 
    { 
        this->v2PreviousPosition = v2Position; 
        glfwSetCursorPos(pContextWindow->getRenderWindow(), pos.x, pos.y);
        v2Position = pos; 
    }

	void InputMouseClass::setGlobalPosition(const ivec2& pos) 
    { 
        this->v2PreviousPosition = v2Position; 
        glfwSetCursorPos(pContextWindow->getRenderWindow(), pos.x, pos.y); //TODO
        v2Position = pos - pContextWindow->getPosition(); 
    }

    void InputMouseClass::setCursor(uint8_t shape)
    {
        switch(shape)
        {
            case CURSOR_SHAPE::DEFAULT:           if(pDefaultCursor   == nullptr) { pDefaultCursor   = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);         } pActiveCursor = pDefaultCursor;   break;
            case CURSOR_SHAPE::HORIZONTAL_RESIZE: if(pHResizeCursor   == nullptr) { pHResizeCursor   = glfwCreateStandardCursor(GLFW_RESIZE_EW_CURSOR);     } pActiveCursor = pHResizeCursor;   break;
            case CURSOR_SHAPE::VERTICAL_RESIZE:   if(pVResizeCursor   == nullptr) { pVResizeCursor   = glfwCreateStandardCursor(GLFW_RESIZE_NS_CURSOR);     } pActiveCursor = pVResizeCursor;   break;
            case CURSOR_SHAPE::TOPLEFT_TO_BOTTOMRIGHT_RESIZE: if(pNWSEResizeCursor   == nullptr) { pNWSEResizeCursor   = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);     } pActiveCursor = pNWSEResizeCursor;   break;
            case CURSOR_SHAPE::TOPRIGHT_TO_BOTTOMLEFT_RESIZE: if(pNESWResizeCursor   == nullptr) { pNESWResizeCursor   = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);     } pActiveCursor = pNESWResizeCursor;   break;
            case CURSOR_SHAPE::ALL_SIDES_RESIZE:  if(pAllResizeCursor == nullptr) { pAllResizeCursor   = glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);     } pActiveCursor = pAllResizeCursor;   break;
            case CURSOR_SHAPE::CROSSHAIR:         if(pCrosshairCursor == nullptr) { pCrosshairCursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);     } pActiveCursor = pCrosshairCursor; break;
            case CURSOR_SHAPE::HAND:              if(pHandCursor      == nullptr) { pHandCursor      = glfwCreateStandardCursor(GLFW_POINTING_HAND_CURSOR); } pActiveCursor = pHandCursor;      break;
            case CURSOR_SHAPE::IBEAM:             if(pIBeamCursor     == nullptr) { pIBeamCursor     = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);         } pActiveCursor = pIBeamCursor;     break;
            case CURSOR_SHAPE::NOT_ALLOWED:       if(pNotAllowedCursor == nullptr) { pNotAllowedCursor     = glfwCreateStandardCursor(GLFW_NOT_ALLOWED_CURSOR);         } pActiveCursor = pNotAllowedCursor;     break;
        };
    }



    //Getter
	vec3 InputMouseClass::getRayDirection() const 			                { return this->rayDir; }
	ivec2 InputMouseClass::getPosition() const 				                { return this->v2Position; }
    ivec2 InputMouseClass::getLeftClickPosition() const                     { return this->v2LeftClickPosition; }
	int InputMouseClass::getCurrentPickedObjectID() const 		            { return this->mouseOnID; }
	int InputMouseClass::getMouseWheelState() const 			            { return this->iMouseWheelState; }
    int InputMouseClass::getCursorType() const                              { return this->CursorType; }
    unsigned int InputMouseClass::getInstanceIDUnderMouse() const           { return this->mouseOnID; }
    
    bool InputMouseClass::hasLeftClick()        { return glfwGetMouseButton(pContextWindow->getRenderWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS; }
    bool InputMouseClass::hasRightClick()       { return glfwGetMouseButton(pContextWindow->getRenderWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS; }
    bool InputMouseClass::isLeftDown()          { return this->LeftDown; }
    bool InputMouseClass::isRightDown()         { return this->RightDown; }
    bool InputMouseClass::hasLeftDoubleClick()  { return this->LeftDoubleClick; }
    bool InputMouseClass::hasRightDoubleClick() { return this->RightDoubleClick; }
    bool InputMouseClass::hasLeftRelease()      { return this->LeftReleased; }
    bool InputMouseClass::hasRightRelease()     { return this->RightReleased; }
    bool InputMouseClass::hasMiddleClick()      { return glfwGetMouseButton(pContextWindow->getRenderWindow(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS; }
    bool InputMouseClass::hasMiddleRelease()    { return glfwGetMouseButton(pContextWindow->getRenderWindow(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE; }
    

	namespace Mouse 
	{
		bool bIsBusy = false, bIsSnapped = false;
		ivec2 v2PositionDelta, v2ScreenPosition, v2PreviousScreenPosition, v2SnapPoint;

		void update()
		{

            Display* display = glfwGetX11Display();
            int x, y, winx, winy;
            unsigned int mask = 0;
            unsigned long childWin, rootWin;
            XQueryPointer(display, XRootWindow(display, XDefaultScreen(display)), &childWin, &rootWin, &x, &y, &winx, &winy, &mask);
			v2ScreenPosition = ivec2(x, y);
			v2PositionDelta = v2ScreenPosition - v2PreviousScreenPosition;
			v2PreviousScreenPosition = v2ScreenPosition;

            if(bIsSnapped) 
            {
                XWarpPointer(display, None, XRootWindow(display, XDefaultScreen(display)), 0, 0, 0, 0, v2SnapPoint.x, v2SnapPoint.y);
			    v2PreviousScreenPosition = v2SnapPoint;
            }
		}

        void freeze(const bool& state)
        {
            if(bIsSnapped != state)
            {
                v2SnapPoint = v2ScreenPosition;
                bIsSnapped = state;
            }
        }

		ivec2 getScreenPosition() 	              { return v2ScreenPosition; }
		ivec2 getDelta() 			              { return v2PositionDelta; }
        bool isBusy()                             { return bIsBusy; }

	    void setBusiness(const bool& val)         { bIsBusy = val; }
		void setSnapPoint(const ivec2& snappoint) { v2SnapPoint = snappoint; }
	}
}}