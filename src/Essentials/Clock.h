#pragma once
#include <functional>
#include <chrono>

template<typename T = std::chrono::high_resolution_clock>
class Clock
{
private:
  std::function<void()> func;
  unsigned int n;
  T::time_point begin, intervalBegin;

public:
  Clock()
  {
    func = nullptr;
    begin = intervalBegin = T::now();
  }

  void runEveryNMilliSeconds(std::function<void()> func, const unsigned int& ms)
  {
    this->func = func;
    n = ms;
  }

  void update()
  {
    long intervalTime = std::chrono::duration_cast<std::chrono::milliseconds>(T::now() - intervalBegin).count();
    if(func != nullptr && intervalTime > n)
    {
      func();
      intervalBegin = T::now();
    }
  }

  void reset()
  {
    begin = T::now();
  }

  long getPassedTimeInMicros()
  {
    return std::chrono::duration_cast<std::chrono::microseconds>(T::now() - begin).count();
  }

  long getPassedTimeInMillis()
  {
    return std::chrono::duration_cast<std::chrono::milliseconds>(T::now() - begin).count();
  }
};