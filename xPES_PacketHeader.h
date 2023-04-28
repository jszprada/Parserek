#pragma once
#include "tsCommon.h"
#include <string>

class xPES_PacketHeader
{
public:
    enum eStreamId : uint8_t {
        eStreamId_program_stream_map = 0xBC,
        eStreamId_padding_stream = 0xBE,
        eStreamId_private_stream_2 = 0xBF,
        eStreamId_ECM = 0xF0,
        eStreamId_EMM = 0xF1,
        eStreamId_program_stream_directory = 0xFF,
        eStreamId_DSMCC_stream = 0xF2,
        eStreamId_ITUT_H222_1_type_E = 0xF8,
    };
protected:
    //PES packet header
    uint32_t m_PacketStartCodePrefix;
    uint8_t m_StreamId;
    uint16_t m_PacketLength;
    uint32_t m_PacketLength2;
public:
    xPES_PacketHeader();
    void Reset();
    int32_t Parse(const uint8_t* Input, uint32_t GlobalAFL);
    void Print() const;
    void PrintLen() const;
public:
    //PES packet header
    uint32_t getPacketStartCodePrefix() const { return m_PacketStartCodePrefix; }
    uint8_t getStreamId() const { return m_StreamId; }
    uint16_t getPacketLength() const { return m_PacketLength; }
};
