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

namespace Gum {
namespace Input
{
    InputMouseClass::InputMouseClass(Gum::Window* context)
    {
        v2Position = ivec2(0,0);
        v2PreviousPosition = ivec2(0,0);
        this->pContextWindow = context;
        //vec2 snapPoint;

        updateonclick = false;
        bIsHidden = false;
        bIsTrapped = false;
        bIsBusy = false;
        bIsSnapped = false;

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
		LeftReleased = false;
		RightReleased = false;

		iMouseWheelState = 0;
        CursorType = 0;
        frameSize = 0;

        


        if(bIsTrapped) { setPosition(pContextWindow->getSize() / 2); }
        if(bIsSnapped) { setPosition(snapPoint); }
    }

	bool InputMouseClass::isInArea(const ivec2& pos, const ivec2& size) const
	{
        return Tools::checkPointInBox(getPosition(), pos, size);
	}

	void InputMouseClass::freeze(const bool& state)
    {
        setSnapPoint(v2Position);
        bIsSnapped = state;
    }

    //Setter
    void InputMouseClass::setContextWindow(Gum::Window* context)            { this->pContextWindow = context; }
	void InputMouseClass::setCursorType(const int& type) 		            { this->CursorType = type; }
	void InputMouseClass::setBusiness(const bool& val) 			            { this->bIsBusy = val; }
	void InputMouseClass::setSnapPoint(const ivec2& snappoint) 	            { this->snapPoint = snappoint; }
	void InputMouseClass::updateOnClick(const bool& bln)    	            { this->updateonclick = bln; }
	void InputMouseClass::trap(const bool& doTrap) 			                { this->bIsTrapped = doTrap; }
	void InputMouseClass::hide(const bool& doHide) 			                { this->bIsHidden = doHide; }
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

    //Getter
	vec3 InputMouseClass::getRayDirection() const 			                { return this->rayDir; }
	ivec2 InputMouseClass::getPosition() const 				                { return this->v2Position; }
	int InputMouseClass::getCurrentPickedObjectID() const 		            { return this->mouseOnID; }
	int InputMouseClass::getMouseWheelState() const 			            { return this->iMouseWheelState; }
    int InputMouseClass::getCursorType() const                              { return this->CursorType; }
    unsigned int InputMouseClass::getInstanceIDUnderMouse() const           { return this->mouseOnID; }
	bool InputMouseClass::isBusy() const 						            { return this->bIsBusy; }
    bool InputMouseClass::isHidden() const                                  { return this->bIsHidden; }
    
    bool InputMouseClass::hasLeftClick()        { return this->LeftDown; /*glfwGetMouseButton(pContextWindow->getRenderWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;*/ }
    bool InputMouseClass::hasRightClick()       { return this->RightDown; /*glfwGetMouseButton(pContextWindow->getRenderWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;*/ }
    bool InputMouseClass::hasLeftDoubleClick()  { return LeftDoubleClick; }
    bool InputMouseClass::hasRightDoubleClick() { return RightDoubleClick; }
    bool InputMouseClass::hasLeftRelease()      { return LeftReleased; }
    bool InputMouseClass::hasRightRelease()     { return RightReleased; }
    bool InputMouseClass::hasMiddleClick()      { return glfwGetMouseButton(pContextWindow->getRenderWindow(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS; }
    bool InputMouseClass::hasMiddleRelease()    { return glfwGetMouseButton(pContextWindow->getRenderWindow(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE; }
    

	namespace Mouse 
	{
		ivec2 v2PositionDelta, v2ScreenPosition, v2PreviousScreenPosition;
		void update(Gum::Window* mainwindow)
		{
			v2PreviousScreenPosition = v2ScreenPosition;
			//double x, y;
			//glfwGetCursorPos(mainwindow->getRenderWindow(), &x, &y); 

            Display* display = glfwGetX11Display();
            int x, y, winx, winy;
            unsigned int mask = 0;
            unsigned long childWin, rootWin;
            XQueryPointer(display, XRootWindow(display, XDefaultScreen(display)), &childWin, &rootWin, &x, &y, &winx, &winy, &mask);

			v2ScreenPosition = ivec2(x, y);
			v2PositionDelta = v2ScreenPosition - v2PreviousScreenPosition;
		}
		ivec2 getScreenPosition() 			                    { return v2ScreenPosition; }
		ivec2 getDelta() 					                    { return v2PositionDelta; }
	}
}}