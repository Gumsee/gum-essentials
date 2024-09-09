#include <gum-essentials.h>
#include <gum-system.h>

using namespace Gum;

int main(int argc, char** argv)
{
    int b = 0;

    int* a = new int(10);
    std::cout << *a << " " << b << std::endl;

    delete a;

    return 0;
}