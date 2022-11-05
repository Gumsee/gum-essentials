#pragma once
#include <vector>
#include <string>
#include "../ImageData.h"

#define GUM_TEXTURE_FILETYPE_BMP 0
#define GUM_TEXTURE_FILETYPE_PNG 1
#define GUM_TEXTURE_FILETYPE_TGA 2
#define GUM_TEXTURE_FILETYPE_JPG 3
#define GUM_TEXTURE_FILETYPE_PNG_HEADER 4
#define GUM_TEXTURE_FILETYPE_RAW_HEADER 5
#define GUM_TEXTURE_FILETYPE_BMP_HEADER 6
#define GUM_TEXTURE_FILETYPE_JPG_HEADER 7
#define GUM_TEXTURE_FILETYPE_TGA_HEADER 8

class TextureLoader
{
public:
	static ImageData<unsigned char> loadImage(const std::string& fileName);
	static ImageData<unsigned char> loadImage(const unsigned char* pixels, size_t length);
	static ImageData<float> loadHDR(const std::string& fileName);

    static void writeImage(const std::string& filename, const int& filetype, ImageData<unsigned char> imagedata, std::string varname = "image");
};