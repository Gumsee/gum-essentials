#pragma once
#include <functional>
#include <chrono>

class Clock
{
private:
    std::function<void()> func;
    unsigned int n;
    std::chrono::steady_clock::time_point begin;

public:
    Clock();
    ~Clock();

    void runEveryNMilliSeconds(std::function<void()> func, const unsigned int& ms);

    void update();
};