#include "TextureLoader.h"
#include <Essentials/Output.h>
#include <Essentials/Tools.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <iostream>
#include "../Tools.h"
#include "Filesystem.h"

/*#define TINYEXR_USE_MINIZ 0
#define TINYEXR_IMPLEMENTATION
#include <tinyexr.h>*/

TextureLoader::ImageData<unsigned char> TextureLoader::loadImage(const std::string& fileName)
{
    ImageData<unsigned char> imagedata;
	std::string extension = Tools::toUpperCase(fileName.substr(fileName.length() - 3, 3));

    if(extension == "BMP" || 
       extension == "PNG" || 
       extension == "TGA" || 
       extension == "JPG" || 
       extension == "JPEG" || 
       extension == "GIF" || 
       extension == "PSD" ||
       extension == "PIC"
       )
    {        
        unsigned char* data = stbi_load(fileName.c_str(), &imagedata.width, &imagedata.height, &imagedata.numComps, 0);

        size_t dataSize = imagedata.width * imagedata.height * imagedata.numComps;
        imagedata.data = (unsigned char*)malloc(dataSize);
        memcpy(imagedata.data, data, dataSize);

        
        if(!data)
            Gum::Output::error("TextureLoader: Failed to load image.");
        stbi_image_free(data);

    }
    else
    {
        Gum::Output::error("TextureLoader: Unknown file extension ." + extension);
    }

	Gum::Output::info("TextureLoader: Texture loaded! (" + fileName + ")");
    return imagedata;
}


TextureLoader::ImageData<unsigned char> TextureLoader::loadImage(const unsigned char* pixels, size_t length)
{
    ImageData<unsigned char> imagedata;
    unsigned char* data = stbi_load_from_memory(pixels, length, &imagedata.width, &imagedata.height, &imagedata.numComps, 0);

    size_t dataSize = imagedata.width * imagedata.height * imagedata.numComps;
    imagedata.data = (unsigned char*)malloc(dataSize);
    memcpy(imagedata.data, data, dataSize);

    
    if(!data)
        Gum::Output::error("TextureLoader: Failed to load image.");
    stbi_image_free(data);

	Gum::Output::info("TextureLoader: Texture loaded from Memory!");
    return imagedata;
}


TextureLoader::ImageData<float> TextureLoader::loadHDR(const std::string& fileName)
{
    ImageData<float> imagedata;
	std::string extension = Tools::toUpperCase(fileName.substr(fileName.length() - 3, 3));

    if(extension == "HDR")
    {
        //stbi_set_flip_vertically_on_load(true);
        stbi_ldr_to_hdr_gamma(1.0f);
        stbi_hdr_to_ldr_scale(1.0f);
        float* data = stbi_loadf(fileName.c_str(), &imagedata.width, &imagedata.height, &imagedata.numComps, 0);

        size_t dataSize = imagedata.width * imagedata.height * imagedata.numComps * sizeof(float);
        imagedata.data = (float*)malloc(dataSize);
        memcpy(imagedata.data, data, dataSize);
        
        if(!data)
            Gum::Output::error("TextureLoader: Failed to load HDR image.");
        stbi_image_free(data);
    }
    /*else if(extension == "EXR")
    {
        float* out; 
        const char* err = nullptr;
        if(LoadEXR(&out, &imagedata.width, &imagedata.height, fileName.c_str(), &err) != TINYEXR_SUCCESS) 
        {
            if (err) 
            {
                fprintf(stderr, "ERR : %s\n", err);
                FreeEXRErrorMessage(err); // release memory of error message.
            }
        } 
        else 
        {
            
            free(out); // release memory of image data
        }
    }*/
    else
    {
        Gum::Output::error("TextureLoader: Unknown file extension ." + extension);
    }

	Gum::Output::info("TextureLoader: Texture loaded! (" + fileName + ")");
    return imagedata;
}

void TextureLoader::writeImage(const std::string& filename, const int& filetype, TextureLoader::ImageData<unsigned char> imagedata)
{
    switch(filetype)
    {
        case GUM_TEXTURE_FILETYPE_PNG:
            stbi_write_png(filename.c_str(), imagedata.width, imagedata.height, imagedata.numComps, imagedata.data, imagedata.width * imagedata.numComps);
            break;
        
        case GUM_TEXTURE_FILETYPE_JPG:
            stbi_write_jpg(filename.c_str(), imagedata.width, imagedata.height, imagedata.numComps, imagedata.data, 100);
            break;

        case GUM_TEXTURE_FILETYPE_PNG_HEADER:
            stbi_write_png_to_func([](void *context, void *data, int size) {
                std::string outStr = "unsigned char image[] = {\n";
                int stride = std::sqrt(size);
                for(int i = 0; i < size; i++)
                {
                    outStr += Tools::decToHex(((unsigned char*)data)[i]) + ", ";
                    if(i % stride == 0)
                        outStr += "\n";
                }
                outStr += "\n};";

                Gum::Filesystem::writeToFile("./image.h", outStr);
            }, nullptr, imagedata.width, imagedata.height, imagedata.numComps, imagedata.data, imagedata.width * imagedata.numComps);
            break;
    }
}