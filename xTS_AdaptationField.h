#pragma once
#include "tsCommon.h"
#include <string>

class xTS_AdaptationField
{
public:
    void Reset();
    int32_t Parse(const uint8_t* Input, uint8_t AdaptationFieldControl);
    void Print() const;
    uint32_t GlobalAFL;
    uint32_t dcc;
    uint32_t random;
    uint32_t priority;
    uint32_t clockref;
    uint32_t orgclockref;
    uint32_t spliting;
    uint32_t transportData;
    uint32_t extField;
public:
    //derrived values
    uint32_t getNumBytes() const { }
    uint32_t getAFL() const { return GlobalAFL; }
};
