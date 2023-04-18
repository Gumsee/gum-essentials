#include <gum-essentials.h>
#include <gum-system.h>

using namespace Gum;

int main(int argc, char** argv)
{
    Unicode testStr = "testeeeäöü gegeßß";
    std::vector<Unicode> parts = testStr.split(U' ');
    std::cout << "(" << parts[0].toString() << ") other: (" << parts[1].toString() << ")" << std::endl;
    return 0;
}