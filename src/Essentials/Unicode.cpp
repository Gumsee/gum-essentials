#include "Unicode.h"
#include "Output.h"
#include <codecvt>
#include <locale>
#include "Tools.h"

namespace Gum 
{
    Unicode::Unicode() { }
    Unicode::Unicode(const char* utf8) : Unicode(std::string(utf8)) { }
    Unicode::Unicode(std::vector<std::basic_string<char>> vec) { this->vUTF8Chars = vec; }

    Unicode::Unicode(std::string utf8)
    {
        int numBytes = 0;
        for(size_t i = 0L; i < utf8.length();)
        {
            char c = utf8[i];
            if      ((c & 0x80) == 0x00) numBytes = 1; // 1 Octet  (ASCII)
            else if ((c & 0xE0) == 0xC0) numBytes = 2; // 2 Octet
            else if ((c & 0xF0) == 0xE0) numBytes = 3; // 3 Octet
            else if ((c & 0xF8) == 0xF0) numBytes = 4; // 4 Octet
            else    Gum::Output::error("UTF-8 Unknown first byte " + Tools::decToHex(c));
            vUTF8Chars.push_back(utf8.substr(i, numBytes));

            i += numBytes;
        }
    }

    Unicode::Unicode(std::u32string str)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        for(size_t i = 0; i < str.length(); i++)
        {
            vUTF8Chars.push_back(converter.to_bytes(str[i]));
        }
    }


    std::basic_string<char>& Unicode::operator[](const unsigned int& index)
    {
        return vUTF8Chars[index];
    }
    std::basic_string<char> Unicode::operator[](const unsigned int& index) const
    {
        return vUTF8Chars[index];
    }

    unsigned int Unicode::getCodepoint(const unsigned int& index) const
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utf32conv;
        return utf32conv.from_bytes(vUTF8Chars[index])[0];
    }

    std::string Unicode::toString() const
    {
        std::string ret;
        for(std::string s : vUTF8Chars)
            ret += s;
            
        return ret;
    }

    size_t Unicode::length() const
    {
        return vUTF8Chars.size();
    }

    Unicode Unicode::substr(const unsigned int& start, const unsigned int& n) const
    {
        return Unicode(std::vector<std::basic_string<char>>(vUTF8Chars.begin() + start, vUTF8Chars.begin() + start + n));
    }

    void Unicode::append(const Unicode& unicode)
    {
        for(size_t i = 0; i < unicode.length(); i++)
            this->vUTF8Chars.push_back(unicode[i]);
    }
}