#pragma once
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
    extern std::vector<std::string> readFileContentsLines(std::string filepath);
    extern std::string readFileContents(std::string filepath);

    extern std::string getExecutablePath();

    extern std::string decToHex(const int& dec);
    extern std::string typeToString(const std::type_info &type);
    extern std::string to_string(void* var, const std::type_info &type);
    extern std::vector<std::string> splitStr(std::string str, char delimiter, bool remWhitespaces = true);
    extern bool strContains(std::string str, std::string contain);
    extern bool isInList(const int& item, const std::vector<int>& list);
    extern std::string strExtractNumbers(std::string str);
    extern std::string toUpperCase(std::string str);
}