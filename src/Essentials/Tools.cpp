#include "Tools.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <System/Output.h>
#include <bitset>
#include <iomanip>

namespace Tools
{
    int StringToInt(std::string str)        { int ret = 0;      try { ret = std::stoi(str); } catch(const std::invalid_argument& e) { Gum::Output::error("StringToInt: couldn't convert string, invalid argument!");    } return ret; }
    float StringToFloat(std::string str)    { float ret = 0.0f; try { ret = std::stof(str); } catch(const std::invalid_argument& e) { Gum::Output::error("StringToFloat: couldn't convert string, invalid argument!");  } return ret; }
    double StringToDouble(std::string str)  { double ret = 0.0; try { ret = std::stod(str); } catch(const std::invalid_argument& e) { Gum::Output::error("StringToDouble: couldn't convert string, invalid argument!"); } return ret; }

    vec2 StringToVec2(std::string str)
    {
        vec2 vec;
        std::vector<std::string> numsStr = splitStr(str, ',');
        for(unsigned int i = 0; i < Gum::Maths::min(numsStr.size(), (size_t)2UL); i++)
        {
            vec[i] = StringToFloat(strExtractNumbers(numsStr[i]));
        }

        return vec;
    }

    vec3 StringToVec3(std::string str)
    {
        Gum::Output::print(str);
        vec3 vec;
        std::vector<std::string> numsStr = splitStr(str, ',');
        for(unsigned int i = 0; i < Gum::Maths::min(numsStr.size(), (size_t)3UL); i++)
        {
            vec[i] = StringToFloat(strExtractNumbers(numsStr[i]));
        }

        return vec;
    }

    vec4 StringToVec4(std::string str)
    {
        vec4 vec;
        std::vector<std::string> numsStr = splitStr(str, ',');
        for(unsigned int i = 0; i < Gum::Maths::min(numsStr.size(), (size_t)4UL); i++)
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

    std::string decToHex(const int& dec, int leadingzeros)
    {
        std::stringstream ss;
        ss << std::uppercase << std::setfill('0') << std::setw(leadingzeros) << std::right << std::hex << dec;
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
    std::string repeatString(const std::string& str, const unsigned int& n)
    {
        std::string retStr = "";
        for(unsigned int i = 0; i < n; i++)
            retStr += str;
        return retStr;
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