#include "Clock.h"
#include <chrono>

Clock::Clock()
{
    func = nullptr;
    begin = intervalBegin = std::chrono::steady_clock::now();
}

Clock::~Clock()
{

}


void Clock::runEveryNMilliSeconds(std::function<void()> func, const unsigned int& ms)
{
    this->func = func;
    n = ms;
}

void Clock::update()
{
    lPassedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count();
    long intervalTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - intervalBegin).count();
    if(func != nullptr && intervalTime > n)
    {
        func();
        intervalBegin = std::chrono::steady_clock::now();
    }
}

void Clock::reset()
{
    begin = std::chrono::steady_clock::now();
}

long Clock::getPassedTime()
{
    return lPassedTime;
}