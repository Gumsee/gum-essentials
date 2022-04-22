#include "Mouse.h"
#include "../Output.h"
#include "../Window.h"
#include "../FPS.h"
#include <iostream>

namespace Gum {
namespace Input
{
    InputMouseClass::InputMouseClass(Gum::Window* context)
    {
        v2Position = ivec2(0,0);
        v2PreviousPosition = ivec2(0,0);
        v2PositionDelta = ivec2(0,0);
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
        
        
        glfwSetCursorPosCallback(pContextWindow->getRenderWindow(), [](GLFWwindow* window, double x, double y) {
				InputMouseClass* mouseptr = ((Window*)glfwGetWindowUserPointer(window))->getMouse();
                mouseptr->v2PositionDelta = ivec2(0,0);
                mouseptr->v2PreviousPosition = mouseptr->v2Position;
                mouseptr->v2Position.x = x;
                mouseptr->v2Position.y = y;

                mouseptr->v2PositionDelta = mouseptr->v2Position - mouseptr->v2PreviousPosition;

                mouseptr->calcRay();
            }
        );

        glfwSetMouseButtonCallback(pContextWindow->getRenderWindow(), [](GLFWwindow* window, int button, int action, int mods) {
				InputMouseClass* mouseptr = ((Window*)glfwGetWindowUserPointer(window))->getMouse();
                if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
                {
                    mouseptr->LeftClickOnce = true;
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
                }
                if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
                {
                    mouseptr->RightClickOnce = true;
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
                }
            }
        );
        
        /*switch (event.type)
        {
            case sf::Event::MouseWheelScrolled:
                iMouseWheelState = event.mouseWheelScroll.delta;
                break;

            case sf::Event::MouseMoved:
                break;

            /*case sf::Event::MouseButtonReleased:
                switch(event.mouseButton.button)
                {
                    case sf::Mouse::Right:  RightRelease  = true; break;
                    case sf::Mouse::Left:   LeftRelease   = true; break;
                    case sf::Mouse::Middle: MiddleRelease = true; break;
                    default:                                      break;
                }
                break;*/

            /*case sf::Event::MouseButtonPressed:
            case sf::Event::MouseEntered:
            case sf::Event::MouseLeft:
            default:
                break;
        }*/
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

    void InputMouseClass::update()
    {
        lastClickTimeLeft += FPS::get();
        lastClickTimeRight += FPS::get();

		iMouseWheelState = 0;
        CursorType = 0;
        frameSize = 0;

        if(bIsTrapped) { setPosition(pContextWindow->getSize() / 2); }
        if(bIsSnapped) { setPosition(snapPoint); }
    }

	bool InputMouseClass::isInArea(const vec2& pos, const vec2& size) const
	{
		if (getPosition().x <= pos.x + size.x &&
		getPosition().x >= pos.x && 
		getPosition().y <= pos.y + size.y && 
		getPosition().y >= pos.y )
		{
			return true;
		}
		return false;
	}

	void InputMouseClass::freeze(const bool& state)
    {
        setSnapPoint(v2Position);
        bIsSnapped = state;
    }

    //Setter
	void InputMouseClass::setCursorType(const int& type) 		            { this->CursorType = type; }
	void InputMouseClass::setBusiness(const bool& val) 			            { this->bIsBusy = val; }
	void InputMouseClass::setSnapPoint(const vec2& snappoint) 	            { this->snapPoint = snappoint; }
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
	vec2 InputMouseClass::getScreenPosition() const 			            { return this->v2Position + pContextWindow->getPosition(); }
	vec2 InputMouseClass::getDelta() const 					                { return this->v2PositionDelta; }
	vec2 InputMouseClass::getPosition() const 				                { return this->v2Position; }
	int InputMouseClass::getCurrentPickedObjectID() const 		            { return this->mouseOnID; }
	int InputMouseClass::getMouseWheelState() const 			            { return this->iMouseWheelState; }
    int InputMouseClass::getCursorType() const                              { return this->CursorType; }
    unsigned int InputMouseClass::getInstanceIDUnderMouse() const           { return this->mouseOnID; }
	bool InputMouseClass::isBusy() const 						            { return this->bIsBusy; }
    bool InputMouseClass::isHidden() const                                  { return this->bIsHidden; }
}}