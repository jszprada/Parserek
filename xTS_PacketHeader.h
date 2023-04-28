#pragma once
#include "tsCommon.h"
#include <string>

class xTS_PacketHeader
{
public:
    enum class ePID : uint16_t
    {
        PAT = 0x0000,
        CAT = 0x0001,
        TSDT = 0x0002,
        IPMT = 0x0003,
        NIT = 0x0010, //DVB specific PID
        SDT = 0x0011, //DVB specific PID
        NuLL = 0x1FFF,
    };
public:
    void     Reset();
    int32_t  Parse(int32_t TS_PacketId, const uint8_t* Input);
    void     Print() const;
public:
    //TODO - direct acces to header values
    bool adaptationFieldFlag = false;
    uint32_t syncByteGlobal;
    uint32_t transportErrorGlobal;
    uint32_t payloadGlobal;
    uint32_t transportPriorityGlobal;
    uint32_t PIDGlobal;
    uint32_t transportSGlobal;
    uint32_t AdaptationFieldControlGlobal;
    uint32_t AdaptationFieldGlobal;
    uint32_t globalCC;
public:
    //TODO
    bool     hasAdaptationField() const { return adaptationFieldFlag; }
    bool     hasPayload() const {  }
    uint32_t getSyncByte() const { return syncByteGlobal; }
    uint32_t getPID() const { return PIDGlobal; }
    uint32_t getAdaptationFieldControl() const { return AdaptationFieldControlGlobal; }
    uint32_t getPayload() const { return payloadGlobal; }
    uint32_t getContinuity() const { return globalCC; }
};
