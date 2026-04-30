#pragma once
#include <functional>
#include <chrono>

template<typename T>
class tClock
{
private:
  std::function<void()> func;
  unsigned int n;
  typename T::time_point begin, intervalBegin;

public:
  tClock()
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

typedef tClock<std::chrono::high_resolution_clock> Clock;
typedef tClock<std::chrono::steady_clock> SteadyClock;
typedef tClock<std::chrono::system_clock> SystemClock;