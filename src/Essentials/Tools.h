#pragma once
#include "BoundingBox.h"
#include <string>
#include <vector>
#include <assimp/scene.h>
#include <gum-maths.h>
#include <typeinfo>

namespace Tools
{
    //Conversion
    extern int StringToInt(std::string str);
    extern float StringToFloat(std::string str);
    extern double StringToDouble(std::string str);
    extern vec2 StringToVec2(std::string str);
    extern vec3 StringToVec3(std::string str);
    extern vec4 StringToVec4(std::string str);
    extern quat StringToQuat(std::string str);

    extern vec3 aiVector3ToVec3(const aiVector3D &v);
    extern quat aiQuaternionToQuat(const aiQuaternion &q);
    extern mat4 aiMatrix4x4ToMat4(aiMatrix4x4 from);
    extern aiMatrix4x4 Mat4ToAiMatrix4(mat4 mat);


    //Processing
    extern std::string decToHex(const int& dec);
    extern std::string typeToString(const std::type_info &type);
    extern std::string to_string(void* var, const std::type_info &type);
    extern std::vector<std::string> splitStr(std::string str, char delimiter, bool remWhitespaces = true);
    extern bool strContains(std::string str, std::string contain);
    extern bool isInList(const int& item, const std::vector<int>& list);

    extern std::string strExtractNumbers(std::string str);
    extern std::string toUpperCase(std::string str);

    template<typename T>
    static bool checkBoxIntersection(tbbox<T, 2> bbox1, tbbox<T, 2> bbox2)
    {
        return  bbox1.getPos().x                     <= bbox2.getPos().x + bbox2.getSize().x &&
                bbox1.getPos().x + bbox1.getSize().x >= bbox2.getPos().x                     && 
                bbox1.getPos().y                     <= bbox2.getPos().y + bbox2.getSize().y && 
                bbox1.getPos().y + bbox1.getSize().y >= bbox2.getPos().y;
    }

    template<typename T>
    static bool checkPointInBox(tvec<T, 2> point, tbbox<T, 2> bbox)
    {
        return  point.x <= bbox.getPos().x + bbox.getSize().x &&
                point.x >= bbox.getPos().x && 
                point.y <= bbox.getPos().y + bbox.getSize().y && 
                point.y >= bbox.getPos().y;
    }
}