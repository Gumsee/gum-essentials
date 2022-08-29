#include "Clock.h"
#include <chrono>

Clock::Clock()
{
    func = nullptr;
    begin = std::chrono::steady_clock::now();
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
    long passedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count();
    if(func != nullptr && passedTime > n)
    {
        func();
        begin = std::chrono::steady_clock::now();
    }
}