#include "xTS_PacketHeader.h"
#include <iostream>

using namespace std;

void xTS_PacketHeader::Reset() {

}

int32_t xTS_PacketHeader::Parse(int32_t TS_PacketId, const uint8_t* Input) {
    uint32_t temp = *((uint32_t*)Input);

    temp = xSwapBytes32(temp);
    constexpr std::uint32_t maskSB{ 0b1111'1111'0000'0000'0000'0000'0000'0000 };
    constexpr std::uint32_t maskTransportError{ 0b0000'0000'1000'0000'0000'0000'0000'0000 };
    constexpr std::uint32_t maskPayload{ 0b0000'0000'0100'0000'0000'0000'0000'0000 };
    constexpr std::uint32_t maskTransportPriority{ 0b0000'0000'0010'0000'0000'0000'0000'0000 };
    constexpr std::uint32_t maskPacketId{ 0b0000'0000'0001'1111'1111'1111'0000'0000 };
    constexpr std::uint32_t maskTransportS{ 0b0000'0000'0000'0000'0000'0000'1100'0000 };
    constexpr std::uint32_t maskAdaptation{ 0b0000'0000'0000'0000'0000'0000'0011'0000 };
    constexpr std::uint32_t maskContinuity{ 0b0000'0000'0000'0000'0000'0000'0000'1111 };
    uint32_t syncByte = temp & maskSB;
    uint32_t transportError = temp & maskTransportError;
    uint32_t payload = temp & maskPayload;
    uint32_t transportPriority = temp & maskTransportPriority;
    uint32_t packetId = temp & maskPacketId;
    uint32_t transportS = temp & maskTransportS;
    uint32_t adaptation = temp & maskAdaptation;
    uint32_t continuity = temp & maskContinuity;

    syncByteGlobal = syncByte >>= 24;
    transportErrorGlobal = transportError >>= 23;
    payloadGlobal = payload >>= 22;
    transportPriorityGlobal = transportPriority >>= 21;
    PIDGlobal = packetId >>= 8;
    transportSGlobal = transportS >>= 6;
    AdaptationFieldGlobal = adaptation >>= 4;
    globalCC = continuity;

    if (AdaptationFieldGlobal == 2 || AdaptationFieldGlobal == 3) {
        adaptationFieldFlag = true;
        AdaptationFieldControlGlobal = adaptation;
    }
    else {
        adaptationFieldFlag = false;
    }

    return temp;
}

void xTS_PacketHeader::Print() const {
    cout << " TS: SB = " << syncByteGlobal
        << " E=" << transportErrorGlobal
        << " S=" << payloadGlobal
        << " P=" << transportPriorityGlobal
        << " PID=" << PIDGlobal
        << " TSC=" << transportSGlobal
        << " AF=" << AdaptationFieldGlobal
        << " CC=" << globalCC;
}



