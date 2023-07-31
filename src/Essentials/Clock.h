#pragma once
#include <functional>
#include <chrono>

class Clock
{
private:
    std::function<void()> func;
    unsigned int n;
    long lPassedTime;
    std::chrono::steady_clock::time_point begin, intervalBegin;

public:
    Clock();
    ~Clock();

    void runEveryNMilliSeconds(std::function<void()> func, const unsigned int& ms);

    void update();
    void reset();
    long getPassedTime();
};