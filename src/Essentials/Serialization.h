#pragma once
#include <System/MemoryManagement.h>
#include <vector>
#include <Maths/vec.h>
#include "SerializationData.h"

class Serialization
{
private:
    std::vector<void*> vDataToSerialize;

protected:
    template<typename T>
    void toSerialize(T& data)
    {
        vDataToSerialize.push_back(&data);
    }

    virtual void onDeserialize() {};
    virtual void onSerialize() {};

public:
    virtual SerializationData& serialize(SerializationData& data) { return data; };
};