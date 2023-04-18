#include "Unicode.h"
#include <System/Output.h>
#include <algorithm>
#include <codecvt>
#include <cstddef>
#include <cstdint>
#include <locale>
#include <string>
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
    Unicode Unicode::operator+(const Unicode& other) const
    {
        Unicode ret(*this);
        ret.append(other);
        return ret;
    }
    void Unicode::operator+=(const Unicode& other)
    {
        append(other);
    }
    bool Unicode::operator==(const Unicode& other) const
    {
        if(this->length() != other.length())
            return false;

        for(size_t i = 0; i < length(); i++)
        {
            if(this->operator[](i) != other[i])
                return false;
        }

        return true;
    }

    unsigned int Unicode::getCodepoint(const unsigned int& index) const
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utf32conv;
        return utf32conv.from_bytes(vUTF8Chars[index])[0];
    }


    bool Unicode::contains(const Gum::Unicode& tofind) const
    {
        return std::search(begin(), end(), tofind.begin(), tofind.end()) != end();
    }

    bool Unicode::isEmpty() const
    {
        return vUTF8Chars.empty();
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

    std::vector<Unicode> Unicode::split(char32_t splitchar) const //FIX THIS TODO
    {
        std::vector<Unicode> ret;
        std::string tofind = "";

        for(int i = 0; i < 4; i++)
        {
            char part = (char)(splitchar >> i * 8);
            if(part == '\0') 
                break;
            tofind += part;
        }

        size_t oldi = 0L;
        for(size_t i = 0L; i < vUTF8Chars.size(); i++)
        {
            if(vUTF8Chars[i] == tofind || i == vUTF8Chars.size() - 1)
            {
                std::vector<std::basic_string<char>> splice;
                splice.resize(i - oldi);
                std::copy(begin() + oldi, begin() + i, splice.begin());
                ret.push_back(splice);
                oldi = i + 1;
            }
        }

        return ret;
    }

    void Unicode::append(const Unicode& unicode)
    {
        for(size_t i = 0; i < unicode.length(); i++)
        {
            vUTF8Chars.push_back(unicode[i]);
        }
    }

    void Unicode::insert(const Unicode& unicode, const unsigned int& index)
    {
        vUTF8Chars.insert(vUTF8Chars.begin() + index, unicode.begin(), unicode.end());
    }

    void Unicode::erase(const unsigned int& index, const unsigned int& n)
    {
        int from = Gum::Maths::max(std::vector<unsigned int>{index, 0});
        int to = Gum::Maths::min(index + n, (unsigned int)vUTF8Chars.size());
        this->vUTF8Chars.erase(vUTF8Chars.begin() + from, vUTF8Chars.begin() + to);
    }

    std::vector<std::basic_string<char>>::const_iterator Unicode::begin() const
    {
        return this->vUTF8Chars.begin();
    }

    std::vector<std::basic_string<char>>::const_iterator Unicode::end() const
    {
        return this->vUTF8Chars.end();
    }

}