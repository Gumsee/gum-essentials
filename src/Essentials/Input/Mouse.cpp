#include "Mouse.h"
#include <SFML/Window/Mouse.hpp>
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
        
        std::cout << "created mouse" << std::endl;
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
            
        LeftRelease  = false;
        RightRelease  = false;
		MiddleRelease  = false;
        LeftDoubleClick = false;
        RightDoubleClick = false;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            LeftClick = true;
        }
        else
        {
            if(LeftClick)
            { 
                if(lastClickTimeLeft < 0.5f)
                {
                    LeftDoubleClick = true;
                    lastClickTimeLeft = 0.5f;
                }
                else
                    lastClickTimeLeft = 0;

                LeftRelease = true;
                LeftClick = false;
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {
            RightClick = true;
        }
        else
        {
            if(RightClick)
            {
                if(lastClickTimeRight < 0.5f)
                {
                    RightDoubleClick = true;
                    lastClickTimeRight = 0.5f;
                }
                else
                    lastClickTimeRight = 0;
                RightRelease = true;
                RightClick = false;
            }
        }
		iMouseWheelState = 0;
        CursorType = 0;
        frameSize = 0;
        v2PositionDelta = ivec2(0,0);


        v2PreviousPosition = v2Position;
        v2Position.x = sf::Mouse::getPosition(*pContextWindow->getRenderWindow()).x;
        v2Position.y = sf::Mouse::getPosition(*pContextWindow->getRenderWindow()).y;

        v2PositionDelta = v2Position - v2PreviousPosition;

        if(bIsTrapped) { setPosition(pContextWindow->getSize() / 2); }
        if(bIsSnapped) { setPosition(snapPoint); }
    }

    void InputMouseClass::handleEvents(sf::Event const& event)
	{
        //Gum::Output::debug("Updating Mouse");
        switch (event.type)
        {
            case sf::Event::MouseWheelMoved:
                iMouseWheelState = event.mouseWheel.delta;
                break;

            case sf::Event::MouseMoved:
                calcRay();
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

            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseWheelScrolled:
            case sf::Event::MouseEntered:
            case sf::Event::MouseLeft:
            default:
                break;
        }
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
	void InputMouseClass::setPosition(const ivec2& pos) 		            { this->v2PreviousPosition = v2Position; sf::Mouse::setPosition(sf::Vector2i(pos.x, pos.y), *pContextWindow->getRenderWindow()); v2Position = pos; }
	void InputMouseClass::setGlobalPosition(const ivec2& pos)	            { this->v2PreviousPosition = v2Position; sf::Mouse::setPosition(sf::Vector2i(pos.x, pos.y)); v2Position = pos - pContextWindow->getPosition(); }
	void InputMouseClass::setCursorType(const int& type) 		            { this->CursorType = type; }
	void InputMouseClass::setBusiness(const bool& val) 			            { this->bIsBusy = val; }
	void InputMouseClass::setSnapPoint(const vec2& snappoint) 	            { this->snapPoint = snappoint; }
	void InputMouseClass::updateOnClick(const bool& bln)    	            { this->updateonclick = bln; }
	void InputMouseClass::trap(const bool& doTrap) 			                { this->bIsTrapped = doTrap; }
	void InputMouseClass::hide(const bool& doHide) 			                { this->bIsHidden = doHide; }
    void InputMouseClass::setInstanceIDUnderMouse(const unsigned int& id)   { this->mouseOnID = id; }

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

    InputMouseClass* Mouse = nullptr;
}}