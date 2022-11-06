#pragma once
#include <functional>
#include <string>

#pragma optimize("", off)

namespace Gum
{
    class Argument
    {
        public:
        std::string switchTriggerName, switchFullName, switchNameShort;
        std::string description;
        bool expectsSetValue;
        std::function<bool(std::string value)> func;

        Argument(std::string switchName, std::string switchNameShort, std::string description, std::function<bool(std::string value)> func)
        {
            this->switchFullName    = switchName;
            this->switchTriggerName = switchName.substr(0, switchName.find("="));
            this->switchNameShort   = switchNameShort;
            this->description       = description;
            //this->func              = func;
            this->expectsSetValue   = switchName.find("=") != std::string::npos;
        };
    };
}
#pragma optimize("", on)