#pragma once

template<typename T>
struct ImageData 
{
    int width = 0;
    int height = 0;
    int numComps = 4;
    T* data;
};