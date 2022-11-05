#pragma once
#include <functional>
#include <vector>
#include <string>

namespace Gum
{
    struct Argument
    {
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
            this->func              = func;
            this->expectsSetValue   = switchName.find("=") != std::string::npos;
        };
    };

    class ArgumentParser
    {
    private:
        std::vector<Argument> vArguments;
        std::string usagePrefix, usageSuffix, usageArg;
        int iDescriptionOffset;
        
        std::string offsetGen(int strLength);
        void usage();

    public:
        ArgumentParser();
        ~ArgumentParser();

        void addArgument(Argument arg);
        void usageSetup(std::string prefix, std::string suffix, std::string arg, std::string argshort, int descriptionOffset = 15);

        bool passArguments(int argc, char** argv, std::function<void(std::string)> defaultAction);
    };
}