#pragma once
#include <vector>
#include <string>

#define GUM_TEXTURE_FILETYPE_BMP 0
#define GUM_TEXTURE_FILETYPE_PNG 1
#define GUM_TEXTURE_FILETYPE_TGA 2
#define GUM_TEXTURE_FILETYPE_JPG 2
#define GUM_TEXTURE_FILETYPE_PNG_HEADER 3

class TextureLoader
{
public:
    template<typename T>
    struct ImageData 
    {
        int width = 0;
        int height = 0;
        int numComps = 4;
        T* data;
    };
	static ImageData<unsigned char> loadImage(const std::string& fileName);
	static ImageData<unsigned char> loadImage(const unsigned char* pixels, size_t length);
	static ImageData<float> loadHDR(const std::string& fileName);

    static void writeImage(const std::string& filename, const int& filetype, ImageData<unsigned char> imagedata);
};