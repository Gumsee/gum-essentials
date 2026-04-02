#include "ArgumentParser.h"
#include <iostream>

namespace Gum
{
    ArgumentParser::ArgumentParser()
    {

    }

    ArgumentParser::~ArgumentParser()
    {

    }

    std::string ArgumentParser::offsetGen(size_t strLength)
    {
        std::string ret;
        for(size_t i = 0; i < iDescriptionOffset - strLength; i++)
            ret += " ";

        return ret;
    }

    void ArgumentParser::usageSetup(std::string prefix, std::string suffix, std::string arg, std::string argshort, int descriptionOffset)
    {
        usagePrefix = prefix;
        usageSuffix = suffix;
        iDescriptionOffset = descriptionOffset;

        if(arg != "")
        {
            addArgument(Argument(arg, argshort, "Print this help menu", [this](std::string) { 
                usage(); 
                return false; 
            }));
            usageArg = arg;
        }
    }

    void ArgumentParser::usage()
    {
        std::string helpStr = usagePrefix + "\n";
        for(size_t j = 0; j < vArguments.size(); j++)
        {
            Argument &arg = vArguments[j];
            helpStr += "    " + arg.switchNameShort + ", " + arg.switchFullName + offsetGen(arg.switchFullName.length()) + arg.description + "\n";
        }
        helpStr += usageSuffix;

        std::cout << helpStr << std::endl;
    }

    Argument* ArgumentParser::getArgument(const std::string& arg)
    {
        for(Argument &argument : vArguments)
            if(arg == argument.switchTriggerName || arg == argument.switchNameShort)
                return &argument;

        return nullptr;
    }

    bool ArgumentParser::passArguments(int argc, char** argv, std::function<void(const char*)> defaultAction)
    {
        if(argc <= 1) 
            return true;

        for(int i = 1; i < argc; i++)
        {
            std::string passedArgStr = argv[i];
            std::string trimmedargStr = passedArgStr.substr(0, passedArgStr.find("="));

            Argument* arg = getArgument(trimmedargStr);
            if(arg == nullptr)
            {
                if(passedArgStr[0] == '-')
                {
                    std::cerr << "Error: unknown argument: '" << trimmedargStr << "'" << std::endl;
                    std::cerr << "Try " + usageArg + " for help." << std::endl;
                    return false;
                }
                else if(defaultAction == nullptr)
                {
                    usage();
                    return false;
                }
                else
                {
                    defaultAction(passedArgStr.c_str());
                }
                continue;
            }

            
            std::string setvalue = "";
            if(arg->expectsSetValue)
            {
                if(passedArgStr.find("=") != std::string::npos)
                {
                    setvalue = passedArgStr.substr(passedArgStr.find("=") + 1, passedArgStr.length());
                }
                else
                {
                    if(i == argc - 1)
                    {
                        std::cerr << arg->switchTriggerName << " expects another argument" << std::endl;
                        return false;
                    }
                    setvalue = argv[++i];
                }
            }

            if(arg->func != nullptr)
                arg->func(setvalue.c_str());
        }

        return true;
    }

    void ArgumentParser::addArgument(Argument arg)
    {
        vArguments.push_back(arg);
    }
}