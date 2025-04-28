#pragma once
#include <vector>
#include <functional>
#include <System/Output.h>

template<typename T>
class crate : public std::vector<T>
{
public:
    using std::vector<T>::vector;
    //crate<T>::at = delete;

    void iterate(std::function<void(T, size_t)> func)
    {
        if(func != nullptr)
            for(size_t i = 0; i < this->size(); i++)
                func(this->operator[](i), i);
    }

    void removeAll(T toremove)
    {
        for(size_t i = 0; i < this->size();)
        {
            if(this->operator[](i) == toremove)
            {
                this->erase(this->begin() + i);
                continue;
            }
            i++;
        }
    }

    const T& at(size_t index, const T& def) const
    {
        if(index >= this->size())
        {
            Gum::Output::error("Crate: getting item out of bounds! (Trying to get item at location "+std::to_string(index)+", but maximum size is "+std::to_string(this->size())+" returning default value!)");
            return def;
        }
        return this->operator[](index);
    }
};