#pragma once
#include <string>
#include <vector>

namespace Gum 
{
    class Unicode
    {
    private:
        std::vector<std::basic_string<char>> vUTF8Chars;

    public:
        Unicode();
        Unicode(std::vector<std::basic_string<char>> vec);
        Unicode(const char* utf8);
        Unicode(std::string utf8);
        Unicode(std::u32string utf32);

        std::basic_string<char>& operator[](const unsigned int& index);
        std::basic_string<char> operator[](const unsigned int& index) const;
        
        unsigned int getCodepoint(const unsigned int& index) const;

        std::string toString() const;
        size_t length() const;
        Unicode substr(const unsigned int& start, const unsigned int& n) const;
        void append(const Unicode& unicode);
        void insert(const Unicode& unicode, const unsigned int& index);
        void erase(const unsigned int& index, const unsigned int& n);
        std::vector<std::basic_string<char>>::const_iterator begin() const;
        std::vector<std::basic_string<char>>::const_iterator end() const;
    };
}