#include "Tools.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <System/Output.h>
#include <iomanip>

namespace Tools
{
    fquat StringToQuat(std::string str, fquat def)
    {
        vec4 quatdata = StringToVec<float, 4>(str, vec4(def.w, def.x, def.y, def.z));
        return fquat(quatdata.x, quatdata.y, quatdata.z, quatdata.w); // w is at the back of vec4
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

    crate<std::string> splitStr(std::string str, char delimiter, bool remWhitespaces)
    {
        crate<std::string> retStrs;
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

    crate<std::string> findLinesContaining(const std::string& tofind, const std::string& str, const char& newlinedelimiter)
    {
        crate<std::string> ret;
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