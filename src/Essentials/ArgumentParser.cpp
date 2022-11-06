/*#include "ArgumentParser.h"
#include <iostream>

namespace Gum
{
    ArgumentParser::ArgumentParser()
    {

    }

    ArgumentParser::~ArgumentParser()
    {

    }

    std::string ArgumentParser::offsetGen(int strLength)
    {
        std::string ret;
        for(int i = 0; i < iDescriptionOffset - strLength; i++)
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
        for(unsigned int j = 0; j < vArguments.size(); j++)
        {
            Argument &arg = vArguments[j];
            helpStr += "    " + arg.switchNameShort + ", " + arg.switchFullName + offsetGen(arg.switchFullName.length()) + arg.description + "\n";
        }
        helpStr += usageSuffix;

        std::cout << helpStr << std::endl;
    }

    bool ArgumentParser::passArguments(int argc, char** argv, std::function<void(const char*)> defaultAction)
    {
        if(argc <= 1) 
            return true;

        for(int i = 1; i < argc; i++)
        {
            std::string passedArgStr = argv[i];
            std::string trimmedargStr = passedArgStr.substr(0, passedArgStr.find("="));
            bool hitAny = false;

            for(unsigned int j = 0; j < vArguments.size(); j++)
            {
                Argument &arg = vArguments[j];
                if(trimmedargStr == arg.switchTriggerName || trimmedargStr == arg.switchNameShort)
                {
                    hitAny = true;
                    std::string setvalue = "";
                    if(arg.expectsSetValue)
                    {
                        if(passedArgStr.find("=") != std::string::npos)
                        {
                            setvalue = passedArgStr.substr(passedArgStr.find("=") + 1, passedArgStr.length());
                        }
                        else
                        {
                            if(i == argc - 1)
                            {
                                std::cerr << arg.switchTriggerName << " expects another argument" << std::endl;
                                return false;
                            }
                            setvalue = argv[++i];
                        }
                    }

                    //if(!arg.func(setvalue))
                    //    return false;
                }
            }

            if(!hitAny)
            {
                if(passedArgStr[0] == '-')
                {
                    std::cerr << "Error: unknown argument: '" << trimmedargStr << "'" << std::endl;
                    std::cerr << "Try " + usageArg + " for help." << std::endl;
                    return false;
                }
                else
                {
                    defaultAction(passedArgStr.c_str());
                }
            }
        }

        return true;
    }

    void ArgumentParser::addArgument(Argument arg)
    {
        vArguments.push_back(arg);
    }
}*/