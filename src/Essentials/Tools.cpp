#include "Tools.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "Output.h"
#include <bitset>

namespace Tools
{
    int StringToInt(std::string str)        { int ret = 0;      try { ret = std::stoi(str); } catch(const std::invalid_argument& e) { Gum::Output::error("StringToInt: couldn't convert string, invalid argument!");    } return ret; }
    float StringToFloat(std::string str)    { float ret = 0.0f; try { ret = std::stof(str); } catch(const std::invalid_argument& e) { Gum::Output::error("StringToFloat: couldn't convert string, invalid argument!");  } return ret; }
    double StringToDouble(std::string str)  { double ret = 0.0; try { ret = std::stod(str); } catch(const std::invalid_argument& e) { Gum::Output::error("StringToDouble: couldn't convert string, invalid argument!"); } return ret; }

    vec2 StringToVec2(std::string str)
    {
        vec2 vec;
        std::vector<std::string> numsStr = splitStr(str, ',');
        for(unsigned int i = 0; i < 2; i++)
        {
            vec[i] = StringToFloat(strExtractNumbers(numsStr[i]));
        }

        return vec;
    }

    vec3 StringToVec3(std::string str)
    {
        vec3 vec;
        std::vector<std::string> numsStr = splitStr(str, ',');
        for(unsigned int i = 0; i < 3; i++)
        {
            vec[i] = StringToFloat(strExtractNumbers(numsStr[i]));
        }

        return vec;
    }

    vec4 StringToVec4(std::string str)
    {
        vec4 vec;
        std::vector<std::string> numsStr = splitStr(str, ',');
        for(unsigned int i = 0; i < 4; i++)
        {
            vec[i] = StringToFloat(strExtractNumbers(numsStr[i]));
        }

        return vec;
    }

    quat StringToQuat(std::string str)
    {
        quat quat;
        std::string currentNumber;
        int index = 0;

        std::string forstr = str + ",";

        for(unsigned int i = 0; i < forstr.length(); i++)
        {
            if(forstr[i] == ',')
            {
                //index [0..3] = [x,y,z,w]
                if(index == 0)      { quat.x = StringToFloat(currentNumber); }
                else if(index == 1) { quat.y = StringToFloat(currentNumber); }
                else if(index == 2) { quat.z = StringToFloat(currentNumber); }
                else if(index == 3) { quat.w = StringToFloat(currentNumber); }
                index++;
                currentNumber = "";
            }
            else
            {
                currentNumber += forstr[i];
            }
        }

        return quat;
    }

    vec3 aiVector3ToVec3(const aiVector3D &v)      { return vec3(v.x, v.y, v.z); }
    quat aiQuaternionToQuat(const aiQuaternion &q) { return quat(q.w, q.x, q.y, q.z); }
    mat4 aiMatrix4x4ToMat4(aiMatrix4x4 from)
    {
        mat4 to;
        to[0][0] = (float)from.a1; to[0][1] = (float)from.b1;  to[0][2] = (float)from.c1; to[0][3] = (float)from.d1;
        to[1][0] = (float)from.a2; to[1][1] = (float)from.b2;  to[1][2] = (float)from.c2; to[1][3] = (float)from.d2;
        to[2][0] = (float)from.a3; to[2][1] = (float)from.b3;  to[2][2] = (float)from.c3; to[2][3] = (float)from.d3;
        to[3][0] = (float)from.a4; to[3][1] = (float)from.b4;  to[3][2] = (float)from.c4; to[3][3] = (float)from.d4;

        return to;
    }

    aiMatrix4x4 Mat4ToAiMatrix4(mat4 mat)
    {
        return aiMatrix4x4(mat[0][0],mat[0][1],mat[0][2],mat[0][3],
                        mat[1][0],mat[1][1],mat[1][2],mat[1][3],
                        mat[2][0],mat[2][1],mat[2][2],mat[2][3],
                        mat[3][0],mat[3][1],mat[3][2],mat[3][3]);
    }

    std::string decToHex(const int& dec)
    {
        std::stringstream ss;
        ss << std::uppercase << std::hex << dec;
        return "0x" + ss.str();
    }

    std::string decToBin(const int& dec)
    {
        return "0b" + std::bitset<32>(dec).to_string();
    }

    std::string typeToString(const std::type_info &type)
    {
        if(type == typeid(int)) { return "int"; }
        if(type == typeid(float)) { return "float"; }
        if(type == typeid(bool)) { return "bool"; }
        if(type == typeid(double)) { return "double"; }
        if(type == typeid(long)) { return "long"; }
        if(type == typeid(char)) { return "char"; }
        if(type == typeid(mat2)) { return "mat2"; }
        if(type == typeid(mat3)) { return "mat3"; }
        if(type == typeid(mat4)) { return "mat4"; }
        if(type == typeid(vec2)) { return "vec2"; }
        if(type == typeid(vec3)) { return "vec3"; }
        if(type == typeid(vec4)) { return "vec4"; }
        return "void";
    }
    
    std::string to_string(void* var, const std::type_info &type)
    {
        if(type == typeid(int))    { return std::to_string(*static_cast<int*>(var)); }
        if(type == typeid(float))  { return std::to_string(*static_cast<float*>(var)); }
        if(type == typeid(bool))   { return std::to_string(*static_cast<bool*>(var)); }
        if(type == typeid(double)) { return std::to_string(*static_cast<double*>(var)); }
        if(type == typeid(long))   { return std::to_string(*static_cast<long*>(var)); }
        if(type == typeid(char))   { return std::to_string(*static_cast<char*>(var)); }
        if(type == typeid(mat2))   { return ((mat2*)var)->toString(); }
        if(type == typeid(mat3))   { return ((mat3*)var)->toString(); }
        if(type == typeid(mat4))   { return ((mat4*)var)->toString(); }
        if(type == typeid(vec2))   { return ((vec2*)var)->toString(); }
        if(type == typeid(vec3))   { return ((vec3*)var)->toString(); }
        if(type == typeid(vec4))   { return ((vec4*)var)->toString(); }
        return "";
    }

    std::vector<std::string> splitStr(std::string str, char delimiter, bool remWhitespaces)
    {
        std::vector<std::string> retStrs;
        std::string foundstr = "";
        for(unsigned int i = 0; i < str.length(); i++)
        {
            if(str[i] == delimiter)
            {
                if(foundstr != "")
                {
                    retStrs.push_back(foundstr);
                    foundstr = "";
                }
            }            
            else
            {
                if((str[i] != ' ' && str[i] != '\n' && str[i] != '\t') || !remWhitespaces)
                {
                    foundstr += str[i];
                }
            }
        }
        if(foundstr != "")
        {
            retStrs.push_back(foundstr);
            foundstr = "";
        }
        return retStrs;
    }

    bool strContains(std::string str, std::string contain)
    {
        return str.find(contain) != str.npos;
    }
    bool isInList(const int& item, const std::vector<int>& list)
    {
        for(int i : list)
        {
            if(i == item) 
                return true;
        }
        return false;
    }

    std::string strExtractNumbers(std::string str)
    {
        std::string numStr = "";
        for(unsigned int i = 0; i < str.length(); i++)
        {
            if((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
            {
                numStr += str[i];
            }
        }
        return numStr;
    }

    std::string toUpperCase(std::string str)
    {
        std::string retStr;
        for(unsigned int i = 0; i < str.length(); i++)
        {
            if(str[i] > 96 && str[i] < 123)
                retStr += str[i] - 32;
            else
                retStr += str[i];
        }
        return retStr;
    }
}