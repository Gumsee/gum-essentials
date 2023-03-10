#include <gum-essentials.h>
#include <gum-system.h>

int main(int argc, char** argv)
{
    Gum::System::init();

    Gum::ArgumentParser argParser;
    argParser.usageSetup("ArgumentTest usage: ", "", "--help", "-h");
    argParser.addArgument(Gum::Argument("--test", "-t", "Testarg", [](std::string str){

        return true;
    }));
    argParser.addArgument(Gum::Argument("--test2", "-g", "Testarg2", [](std::string str){

        return true;
    }));
    argParser.addArgument(Gum::Argument("--test3", "-h", "Testarg3", [](std::string str){

        return true;
    }));

    if(!argParser.passArguments(argc, argv, nullptr))
        return 1;

    return 0;
}