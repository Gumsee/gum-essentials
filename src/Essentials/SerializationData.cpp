#include "SerializationData.h"
#include "Serialization.h"

SerializationData& SerializationData::operator<<(Serialization& data)
{
    bIsSavingData = true;
    return data.serialize(*this); 
}


SerializationData& SerializationData::operator>>(Serialization& data)
{
    bIsSavingData = false;
    return data.serialize(*this); 
}