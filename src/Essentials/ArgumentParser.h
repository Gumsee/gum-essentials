#pragma once
#include "Argument.h"
#include <vector>

namespace Gum
{
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

        bool passArguments(int argc, char** argv, std::function<void(const char*)> defaultAction);
    };
}