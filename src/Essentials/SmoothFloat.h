#pragma once
#include "Time.h"
#include <cstdlib>

//TODO Different smoothfloat types: easing examples
//#error
class SmoothFloat
{
private:
	float speed = 5.0f;
	float target = 0.0f;
	float actual = 0.0f;
	float min = -99999.0f;
	float max = 99999.0f;
public:
	SmoothFloat() {};
	~SmoothFloat() {};

	SmoothFloat(float target, float speed, float initialValue = 0) 
	{
		this->target = target;
		this->actual = initialValue;
		this->speed = speed;
	}

	bool update() 
  {
    if(target == actual)
      return false;

		float offset = target - actual;
		float change = offset * Time::getFrametime() * speed;
		actual += change;

    if(std::abs(change) < 0.001)
      actual = target;
    
    return true;
	}
	
	void setTarget(float target) 			
	{ 
		this->target = target; 
		if(this->target < min) { this->target = min; }
		if(this->target > max) { this->target = max; }
	}


	void increaseTarget(float target) 		{ setTarget(this->target + target); }
	void instantIncrease(float increase) 	{ this->actual += increase; }
	void set(float val) 				    { this->actual = val; }
	void setMin(float min) 					{ this->min = min; }
	void setMax(float max) 					{ this->max = max; }
	void reset() 							{ this->actual = 0; }
	void setSpeed(float speed) 				{ this->speed = speed; }
	void operator+(int a) 					{ this->target += a; }
	void operator=(int a) 					{ this->target = a; }

    float getPercentage()                   { return this->actual / this->max; }
	float getMax() 							{ return this->max; }
	float get() 							{ return this->actual; }
	float getTarget() 						{ return this->target; }
	float getMin() 							{ return this->min; }
};