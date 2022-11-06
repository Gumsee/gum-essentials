#include "Essentials/Tools.h"
#include <gum-essentials.h>
#include <Essentials/Filesystem/TextureLoader.h>
#include <gum-system.h>

std::string usageString = 
R"(Usage: ImageToHeaderConverter [IMAGEFILE] [OUTFILE]
)";

std::string usageStringSuffix = 
R"(
Available datatypes are: PNG, JPG, BMP, TGA, RAW
)";

std::vector<std::string> vFiles;
std::string varname = "image";
int type = GUM_TEXTURE_FILETYPE_RAW_HEADER;

int main(int argc, char** argv)
{
    /*Gum::ArgumentParser* pArgumentParser = new Gum::ArgumentParser();

    pArgumentParser->usageSetup(usageString, "", "--help", "-h", 20);

    pArgumentParser->addArgument(Gum::Argument("--varname=VARNAME", "-v", "Header variable name", [](std::string value) {
        varname = value;
        return true;
    }));

    pArgumentParser->addArgument(Gum::Argument("--type=TYPE", "-t", "Datatype that should be used", [](std::string value) {
        std::string typeStr = Tools::toUpperCase(value);
        if     (typeStr == "PNG") { type = GUM_TEXTURE_FILETYPE_PNG_HEADER; }
        else if(typeStr == "JPG") { type = GUM_TEXTURE_FILETYPE_JPG_HEADER; }
        else if(typeStr == "BMP") { type = GUM_TEXTURE_FILETYPE_BMP_HEADER; }
        else if(typeStr == "TGA") { type = GUM_TEXTURE_FILETYPE_TGA_HEADER; }
        else if(typeStr == "RAW") { type = GUM_TEXTURE_FILETYPE_RAW_HEADER; }
        else                      { std::cerr << "Unknown datatype '" << typeStr << "'" << std::endl; }
        return true;
    }));


    if(!pArgumentParser->passArguments(argc, argv, [](std::string arg) { vFiles.push_back(arg); }))
    {
        delete pArgumentParser;
        return 1;
    }
    delete pArgumentParser;*/

    if(vFiles.size() != 2)
    {
        std::cerr << "Please specify exactly 2 files" << std::endl;
        return 1;
    }

    TextureLoader::writeImage(vFiles[1], type, TextureLoader::loadImage(vFiles[0]), varname);

    return 0;
}