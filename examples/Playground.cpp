#include "Essentials/Unicode.h"
#include <gum-essentials.h>
#include <gum-system.h>


std::map<std::string, std::string> mapper;

int main(int argc, char** argv)
{
    mapper["ል"] = "A";
    mapper["ጌ"] = "B";
    mapper["ር"] = "C";
    mapper["ዕ"] = "D";
    mapper["ቿ"] = "E";
    mapper["ቻ"] = "F";
    mapper["ኗ"] = "G";
    mapper["ዘ"] = "H";
    mapper["ጎ"] = "I";
    mapper["ጕ"] = "K";
    mapper["ጠ"] = "M";
    mapper["ክ"] = "N";
    mapper["ረ"] = "L";
    mapper["የ"] = "P";
    mapper["ዪ"] = "R";
    mapper["ነ"] = "S";
    mapper["ፕ"] = "T";
    mapper["ሁ"] = "U";
    mapper["ሀ"] = "V";
    mapper["ሠ"] = "W";
    mapper["ጊ"] = "Z";
    
    
    Gum::Unicode str("");


    std::cout << "Original: " << std::endl;
    std::cout << str.toString() << std::endl;
    std::cout << std::endl;

    std::cout << "Translated: " << std::endl;
    for(size_t i = 0; i < str.length(); i++)
    {
        if(mapper.find(str[i]) != mapper.end())
            std::cout << mapper[str[i]];
        else
            std::cout << str[i];
    }
    std::cout << std::endl;
    return 0;
}