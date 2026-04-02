#pragma once
#include <algorithm>
#include <bitset>
#include <functional>
#include <string>
#include <unordered_map>
#include "Crate.h"
#include <map>
#include <gum-maths.h>
#include <typeinfo>

#define _str(x) std::to_string(x)

namespace Tools
{
    //Processing
    extern crate<std::string> splitStr(std::string str, char delimiter, bool remWhitespaces = true);
    extern crate<std::string> findLinesContaining(const std::string& tofind, const std::string& str, const char& newlinedelimiter = '\n');
    const auto grep = findLinesContaining;
    extern std::string strExtractNumbers(std::string str);
    extern std::string toUpperCase(std::string str);
    extern std::string toLowerCase(std::string str);
    extern std::string escapeString(std::string str);
    extern std::string repeatString(const std::string& str, const unsigned int& n);
    extern std::string strReplace(const std::string& str, const char& toreplace, const char& symbol);


    //Conversion
    template<typename T>
    static T StringToNum(std::string str, T def = (T)0)
    {
      T ret = def; 
      try { 
        if      constexpr (std::is_same<T, int>())    ret = std::stoi(str); 
        else if constexpr (std::is_same<T, short>())  ret = static_cast<short>(std::stoi(str)); 
        else if constexpr (std::is_same<T, float>())  ret = std::stof(str); 
        else if constexpr (std::is_same<T, long>())   ret = std::stol(str); 
        else if constexpr (std::is_same<T, double>()) ret = std::stod(str); 
      } 
      catch(const std::invalid_argument& e) 
      { 
        Gum::Output::error("StringToNum: couldn't convert string, invalid argument!");
        ret = def;
      } 
      return ret;
    }

    template<typename T, unsigned int N>
    static tvec<T,N> StringToVec(std::string str, tvec<T,N> def = tvec<T,N>())
    {
      tvec<T,N> vec;
      crate<std::string> numsStr = splitStr(str, ',');
      for(unsigned int i = 0; i < Gum::Maths::min(numsStr.size(), (size_t)N); i++)
        vec[i] = StringToNum<T>(strExtractNumbers(numsStr[i]), def[i]);

      return vec;
    }
    
    extern fquat StringToQuat(std::string str, fquat def = fquat(0.0f));
    extern std::string decToHex(const int& dec, int leadingzeros = 2);
    template<typename T>
    static std::string decToBin(const T& dec, std::string prefix = "0b")
    {
        return prefix + std::bitset<sizeof(T) * 8>(dec).to_string();
    }
    extern std::string typeToString(const std::type_info &type);
    extern std::string to_string(void* var, const std::type_info &type = typeid(void));
    

    //Vector Operations
    extern vec2 lineLineIntersection(vec2 A, vec2 B, vec2 C, vec2 D);
	  extern float barryCentric(vec3 p1, vec3 p2, vec3 p3, vec2 pos);


    //Checking
    extern bool strContains(std::string str, std::string contain);

    template<typename T>
    static long isInList(const T& item, const crate<T>& list, std::function<bool(T, T)> comparisonfunc = [](T a, T b){ return a == b; })
    {
        for(long i = 0; i < (long)list.size(); i++)
        {
            if(comparisonfunc(list[i], item)) 
                return i;
        }
        return -1;
    }

    template<typename T, typename TT>
    static bool mapHasKey(const std::map<T,TT>& map, const T& key)
    {
        return map.find(key) != map.end();
    }

    template<typename T, typename TT>
    static bool mapHasKey(const std::unordered_map<T,TT>& map, const T& key)
    {
        return map.find(key) != map.end();
    }

    template<typename T, typename TT>
    static bool mapHasKeyNotNull(const std::map<T,TT>& map, const T& key)
    {
        return mapHasKey(map, key) && map.at(key) != nullptr;
    }

    template<typename T, typename TT>
    static bool mapHasKeyNotNull(const std::unordered_map<T,TT>& map, const T& key)
    {
        return mapHasKey(map, key) && map.at(key) != nullptr;
    }

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


    //List operations
    template<typename T>
    static bool moveEntryToBack(const crate<T>& vec, const T& entry)
    {
        auto it = std::find(vec.begin(), vec.end(), entry);
        if(it == vec.end())
            return false;

        std::rotate(it, it + 1, vec.end());
        return true;
    }
}