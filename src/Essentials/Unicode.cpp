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

    Unicode::Unicode(const char32_t* codepoints) : Unicode(std::u32string(codepoints)) {}

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
            push_back(utf8.substr(i, numBytes));

            i += numBytes;
        }
    }

    Unicode::Unicode(std::u32string str)
    {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        #pragma GCC diagnostic pop
        for(size_t i = 0; i < str.length(); i++)
            push_back(converter.to_bytes(str[i]));
    }

    Unicode::Unicode(crate<std::basic_string<char>>::const_iterator begin, crate<std::basic_string<char>>::const_iterator end)
        : std::vector<std::basic_string<char>>(begin, end)
    {
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
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utf32conv;
        #pragma GCC diagnostic pop
        return utf32conv.from_bytes(at(index))[0];
    }


    bool Unicode::contains(const Gum::Unicode& tofind) const
    {
        return std::search(begin(), end(), tofind.begin(), tofind.end()) != end();
    }

    bool Unicode::isEmpty() const
    {
        return empty();
    }

    std::string Unicode::toString() const
    {
        std::string ret("");
        for(std::string s : *this)
            ret += s;
            
        return ret;
    }

    size_t Unicode::length() const
    {
        return size();
    }

    Unicode Unicode::substr(const unsigned int& start, const unsigned int& n) const
    {
        if(start > size() || n > size())
            return "";
        return Unicode(begin() + start, begin() + start + n);
    }

    Unicode Unicode::substr(const unsigned int& start) const
    {
        if(start > size())
            return "";
        return Unicode(begin() + start, end());
    }

    crate<Unicode> Unicode::split(char32_t splitchar) const //FIX THIS TODO
    {
        crate<Unicode> ret;
        std::string tofind = "";

        for(int i = 0; i < 4; i++)
        {
            char part = (char)(splitchar >> i * 8);
            if(part == '\0') 
                break;
            tofind += part;
        }

        size_t oldi = 0L;
        for(size_t i = 0L; i < size(); i++)
        {
            if(at(i) == tofind || i == size() - 1)
            {
                Unicode splice;
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
            push_back(unicode[i]);
        }
    }

    void Unicode::insert(const Unicode& unicode, const unsigned int& index)
    {
        UnicodeVectype::insert(begin() + index, unicode.begin(), unicode.end());
    }

    void Unicode::erase(const unsigned int& index, const unsigned int& n)
    {
        int from = Gum::Maths::max(crate<unsigned int>{index, 0});
        int to = Gum::Maths::min(index + n, (unsigned int)size());
        UnicodeVectype::erase(begin() + from, begin() + to);
    }

    void Unicode::eraseEveryOccurence(const std::string& toremove)
    {
        crate<int> indices;
        for(size_t i = 0; i < size(); i++)
        {
            if(at(i) == toremove)
                indices.push_back((int)i);
        }
        for(int i : indices)
            erase((unsigned int)i, 1);
    }

    void Unicode::replace(const std::string& toreplace, const std::string& replacement)
    {
        for(size_t i = 0; i < size(); i++)
        {
            if(at(i) == toreplace)
                at(i) = replacement;
        }
    }

    size_t Unicode::find(const std::string& tofind)
    {
        size_t ret = max_size();
        for(size_t i = 0; i < size(); i++)
        {
            if(at(i) == tofind)
            {
                ret = i;
                break;
            }
        }

        return ret;
    }

    size_t Unicode::rfind(const std::string& tofind)
    {
        size_t ret = max_size();
        for(size_t i = size(); i --> 0;)
        {
            if(at(i) == tofind)
            {
                ret = i;
                break;
            }
        }

        return ret;
    }
}