#pragma once
#include <string>
#include <vector>
#include "Crate.h"

namespace Gum 
{
    typedef std::vector<std::basic_string<char>> UnicodeVectype;
    class Unicode : private UnicodeVectype
    {
    public:
        Unicode();
        Unicode(const char32_t* codepoints);
        Unicode(const char* utf8);
        Unicode(std::string utf8);
        Unicode(std::u32string utf32);
        Unicode(UnicodeVectype::const_iterator begin, UnicodeVectype::const_iterator end);

        using UnicodeVectype::operator[];
        //using crate<std::basic_string<char>>::operator[] const;

        Unicode operator+(const Unicode& other) const;
        void operator+=(const Unicode& other);
        bool operator==(const Unicode& other) const;
        
        unsigned int getCodepoint(const unsigned int& index) const;

        bool contains(const Gum::Unicode& tofind) const;
        bool isEmpty() const;
        std::string toString() const;
        size_t length() const;
        Unicode substr(const unsigned int& start, const unsigned int& n) const;
        Unicode substr(const unsigned int& start) const;
        crate<Unicode> split(char32_t splitchar) const;
        void append(const Unicode& unicode);
        void insert(const Unicode& unicode, const unsigned int& index);
        void erase(const unsigned int& index, const unsigned int& n);
        void eraseEveryOccurence(const std::string& toremove);
        void replace(const std::string& toreplace, const std::string& replacement);
        size_t find(const std::string& tofind);
        size_t rfind(const std::string& tofind);
        using UnicodeVectype::begin;
        using UnicodeVectype::end;
    };
}