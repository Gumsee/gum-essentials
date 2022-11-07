#pragma once
#include <functional>
#include <string>

//#pragma optimize("", off)

namespace Gum
{
    class Argument
    {
    public:
        std::function<void(const char*)> func;
        std::string switchTriggerName, switchFullName, switchNameShort;
        std::string description;
        bool expectsSetValue;

        Argument(std::string switchName, std::string switchNameShort, std::string description, std::function<bool(const char*)> func)
        {
            this->switchFullName    = switchName;
            this->switchTriggerName = switchName.substr(0, switchName.find("="));
            this->switchNameShort   = switchNameShort;
            this->description       = description;
            this->func              = func;
            this->expectsSetValue   = switchName.find("=") != std::string::npos;
        }

        ~Argument() 
        {

        }
    };
}
//#pragma optimize("", on)