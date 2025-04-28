#pragma once
#include <System/MemoryManagement.h>
#include "Crate.h"
#include <Maths/vec.h>
#include "SerializationData.h"

class Serialization
{
private:
    crate<void*> vDataToSerialize;

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