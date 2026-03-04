#pragma once
#include <System/MemoryManagement.h>
#include "Crate.h"
#include <queue>
#include <string>
#include <Maths/vec.h>

class Serialization;
class SerializationData : std::queue<unsigned char>
{
private:
    bool bIsSavingData = true; //true = saving, false = retrieving

public:
    SerializationData() {}
    SerializationData(const unsigned char* data, const unsigned int& len)
    {
        for(unsigned int i = 0; i < len; i++)
            push(data[i]);
    }

    template<typename T>
    void insertGenericData(const T& data)
    {
        bIsSavingData = true;
        crate<unsigned char> cdatav;
        unsigned char* cdata = (unsigned char*)&data;
        bool bytesnull = true;
        for(size_t i = 0; i < sizeof(T); i++)
        {
            if(cdata[i] != 0)
                bytesnull = false;
            
            if(!bytesnull)
                cdatav.push_back(cdata[i]);
        }

        push(static_cast<unsigned char>(cdatav.size()));
        for(size_t i = 0; i < cdatav.size(); i++)
            push(cdatav[i]);
    }

    template<typename T, unsigned int S, unsigned int type>
    SerializationData& operator<<(const tvec<T, S, type>& vec)
    { 
        for(unsigned int i = 0; i < S; i++)
            this->operator<<(vec[i]);
        return *this; 
    }

    SerializationData& operator<<(const float& data) { insertGenericData(data); return *this; }
    SerializationData& operator<<(const int& data)   { insertGenericData(data); return *this; }
    SerializationData& operator<<(const char& data)  { insertGenericData(data); return *this; }
    SerializationData& operator<<(const short& data) { insertGenericData(data); return *this; }
    SerializationData& operator<<(const long& data)  { insertGenericData(data); return *this; }
    SerializationData& operator<<(const unsigned int& data)   { insertGenericData(data); return *this; }
    SerializationData& operator<<(const unsigned char& data)  { insertGenericData(data); return *this; }
    SerializationData& operator<<(const unsigned short& data) { insertGenericData(data); return *this; }
    SerializationData& operator<<(const unsigned long& data)  { insertGenericData(data); return *this; }
    SerializationData& operator<<(const bool& data)  
    {
        push((unsigned char)data);
        return *this; 
    }
    SerializationData& operator<<(const std::string& data)
    { 
        bIsSavingData = true;
        insertGenericData((unsigned int)data.length());
        for(size_t i = 0; i < data.length(); i++)
            push((unsigned char)data[i]);
        return *this;
    }
    SerializationData& operator<<(Serialization& data);


    template<typename T>
    void retrieveGenericData(T& data)
    {
        bIsSavingData = false;
        if(size() < sizeof(T))
            return;

        size_t size = this->front();
        pop();

        unsigned char* cdata = (unsigned char*)&data;

        for(size_t i = 0; i < sizeof(T) - size; i++)
            cdata[i] = 0;
        
        for(size_t i = sizeof(T) - size; i < sizeof(T); i++)
        {
            cdata[i] = this->front();
            pop();
        }
    }

    SerializationData& operator>>(float& data) { retrieveGenericData(data); return *this; }
    SerializationData& operator>>(int& data)   { retrieveGenericData(data); return *this; }
    SerializationData& operator>>(char& data)  { retrieveGenericData(data); return *this; }
    SerializationData& operator>>(short& data) { retrieveGenericData(data); return *this; }
    SerializationData& operator>>(long& data)  { retrieveGenericData(data); return *this; }
    SerializationData& operator>>(unsigned int& data)   { retrieveGenericData(data); return *this; }
    SerializationData& operator>>(unsigned char& data)  { retrieveGenericData(data); return *this; }
    SerializationData& operator>>(unsigned short& data) { retrieveGenericData(data); return *this; }
    SerializationData& operator>>(unsigned long& data)  { retrieveGenericData(data); return *this; }


    template<typename T, unsigned int S, unsigned int type>
    SerializationData& operator>>(tvec<T, S, type>& vec)
    { 
        for(unsigned int i = 0; i < S; i++)
            this->operator>>(vec[i]);
        return *this; 
    }

    SerializationData& operator>>(bool& data)  
    {
        if(size() < 1)
            return *this;

        data = (bool)this->front();
        pop();
        return *this; 
    }
    SerializationData& operator>>(std::string& data)
    {
        bIsSavingData = false;
        if(size() < sizeof(unsigned int))
            return *this;

        unsigned int length;
        retrieveGenericData(length);

        if(size() < length)
            return *this;

        data.resize(length);
        for(size_t i = 0; i < length; i++)
        {
            data[i] = this->front();
            pop();
        }
        return *this; 
    }
    SerializationData& operator>>(Serialization& data);


    template<typename T>
    SerializationData& operator&(T& data)
    {
        if(bIsSavingData)
            return this->operator<<(data);
        
        return this->operator>>(data);
    }


    template<typename T>
    SerializationData& operator&(crate<T>& data)
    {
        size_t size = data.size();
        this->operator&(size);
        
        if(!bIsSavingData)
        {
            data.clear();
            data.resize(size);
        }

        for(size_t i = 0; i < size; i++)
            this->operator&(data[i]);

        return *this;
    }

    unsigned char* addRawBytes(unsigned char* data, unsigned int& length)
    {
        if(bIsSavingData)
        {
            insertGenericData(length);
            for(unsigned int i = 0; i < length; i++)
                push(data[i]);
        }
        else
        {
            if(data != nullptr)
                free(data);

            retrieveGenericData(length);
            data = (unsigned char*)Gum::_malloc(length);

            for(unsigned int i = 0; i < length; i++)
            {
                data[i] = front();
                pop();
            }
        }
        
        return data;
    }

    unsigned char* getData(unsigned int& len)
    {
        len = (unsigned int)this->size();
        unsigned char* data = (unsigned char*)Gum::_malloc(len * sizeof(unsigned char));

        for(size_t i = 0; i < len; i++)
        {
            data[i] = front();
            pop();
        }

        for(size_t i = 0; i < len; i++)
        {
            push(data[i]);
        }

        return data;
    }

    bool isSavingData()
    {
        return bIsSavingData;
    }
};