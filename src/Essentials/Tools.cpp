#include "Tools.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <System/Output.h>
#include <iomanip>

namespace Tools
{
    int StringToInt(std::string str)        { int ret = 0;      try { ret = std::stoi(str); } catch(const std::invalid_argument& e) { Gum::Output::error("StringToInt: couldn't convert string, invalid argument!");    } return ret; }
    float StringToFloat(std::string str)    { float ret = 0.0f; try { ret = std::stof(str); } catch(const std::invalid_argument& e) { Gum::Output::error("StringToFloat: couldn't convert string, invalid argument!");  } return ret; }
    double StringToDouble(std::string str)  { double ret = 0.0; try { ret = std::stod(str); } catch(const std::invalid_argument& e) { Gum::Output::error("StringToDouble: couldn't convert string, invalid argument!"); } return ret; }
    long StringToLong(std::string str)      { long ret = 0L;    try { ret = std::stol(str); } catch(const std::invalid_argument& e) { Gum::Output::error("StringToLong: couldn't convert string, invalid argument!");   } return ret; }

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
        if     (type == typeid(int))    { return std::to_string(*static_cast<int*>(var)); }
        else if(type == typeid(float))  { return std::to_string(*static_cast<float*>(var)); }
        else if(type == typeid(bool))   { return std::to_string(*static_cast<bool*>(var)); }
        else if(type == typeid(double)) { return std::to_string(*static_cast<double*>(var)); }
        else if(type == typeid(long))   { return std::to_string(*static_cast<long*>(var)); }
        else if(type == typeid(char))   { return std::to_string(*static_cast<char*>(var)); }
        else if(type == typeid(mat2))   { return ((mat2*)var)->toString(); }
        else if(type == typeid(mat3))   { return ((mat3*)var)->toString(); }
        else if(type == typeid(mat4))   { return ((mat4*)var)->toString(); }
        else if(type == typeid(vec2))   { return ((vec2*)var)->toString(); }
        else if(type == typeid(vec3))   { return ((vec3*)var)->toString(); }
        else if(type == typeid(vec4))   { return ((vec4*)var)->toString(); }
        else
        {
            std::ostringstream address;
            address << (const void*)var;
            return address.str();
        }
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

    std::vector<std::string> findLinesContaining(const std::string& tofind, const std::string& str, const char& newlinedelimiter)
    {
        std::vector<std::string> ret;
        for(std::string line : splitStr(str, newlinedelimiter, false))
        {
            if(line.find(tofind) != line.npos)
                ret.push_back(line);
        }

        return ret;
    }

    std::string repeatString(const std::string& str, const unsigned int& n)
    {
        std::string retStr = "";
        for(unsigned int i = 0; i < n; i++)
            retStr += str;
        return retStr;
    }

    std::string strReplace(const std::string& str, const char& toreplace, const char& symbol)
    {
        std::string retstr = "";
        for(unsigned int i = 0; i < str.length(); i++)
        {
            if(str[i] == toreplace)
                retstr += symbol;
            else
                retstr += str[i];
        }

        return retstr;
    }

    bool strContains(std::string str, std::string contain)
    {
        return str.find(contain) != str.npos;
    }

    std::string strExtractNumbers(std::string str)
    {
        std::string numStr = "";
        bool hasDot = false;
        for(unsigned int i = 0; i < str.length(); i++)
        {
            if((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
            {
                numStr += str[i];
            }
            else if((str[i] == ',' || str[i] == '.') && !hasDot)
            {
                numStr += '.';
                hasDot = true;
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

    std::string toLowerCase(std::string str)
    {
        std::string retStr;
        for(unsigned int i = 0; i < str.length(); i++)
        {
            if(str[i] > 64 && str[i] < 91)
                retStr += str[i] + 32;
            else
                retStr += str[i];
        }
        return retStr;
    }

    std::string escapeString(std::string str)
    {
        std::string retStr;
        for(unsigned int i = 0; i < str.length(); i++)
        {
            switch(str[i])
            {
                case '\t': retStr += "\\t";  break;
                case '\"': retStr += "\\\""; break;
                case '\\': retStr += "\\\\"; break;
                case '\n': retStr += "\\n";  break;
                default:   retStr += str[i]; break;
            }
        }
        return retStr;
    }

    vec2 lineLineIntersection(vec2 A, vec2 B, vec2 C, vec2 D)
    {
        //Line AB represented as a1x + b1y = c1
        float a1 = B.y - A.y;
        float b1 = A.x - B.x;
        float c1 = a1 * A.x + b1 * A.y;
    
        //Line CD represented as a2x + b2y = c2
        float a2 = D.y - C.y;
        float b2 = C.x - D.x;
        float c2 = a2 * C.x + b2 * C.y;
    
        float determinant = a1 * b2 - a2 * b1;
        if(determinant == 0)
            return vec2(-1, -1);
        

        return vec2(b2 * c1 - b1 * c2, a1 * c2 - a2 * c1) / determinant;
    }
    
    float barryCentric(vec3 p1, vec3 p2, vec3 p3, vec2 pos) 
    {
        float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
        float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
        float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
        float l3 = 1.0f - l1 - l2;
        return l1 * p1.y + l2 * p2.y + l3 * p3.y;
    }
}