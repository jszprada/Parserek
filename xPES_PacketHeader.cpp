#include "xPES_PacketHeader.h"
#include <iostream>
#include "tsTransportStream.h"

using namespace std;
void xPES_PacketHeader::Print() const {
    cout << " PES: PSCP = " << m_PacketStartCodePrefix
        << " SID = " << (int)m_StreamId
        << " L = " << m_PacketLength;
}

void xPES_PacketHeader::PrintLen() const {
    cout << " PES: Len = " << m_PacketLength2;
}

xPES_PacketHeader::xPES_PacketHeader() {
    m_PacketStartCodePrefix = 0;
    m_StreamId = 0;
    m_PacketLength = 0;
    m_PacketLength2 = 0;
}

int32_t xPES_PacketHeader::Parse(const uint8_t* TransportStreamPacket, uint32_t GlobalAFL) {
    int32_t PESheaderSize = 0;
    uint32_t temp = *((uint32_t*)(TransportStreamPacket + xTS::TS_HeaderLength + 1 + GlobalAFL));
    temp = xSwapBytes32(temp);
    uint16_t temp2 = *((uint16_t*)(TransportStreamPacket + xTS::TS_HeaderLength + 1 + GlobalAFL + 4));
    temp2 = xSwapBytes16(temp2);
    uint8_t temp3 = *((uint8_t*)(TransportStreamPacket + xTS::TS_HeaderLength + 1 + GlobalAFL + 3));
    uint8_t temp4 = *((uint8_t*)(TransportStreamPacket + xTS::TS_HeaderLength + 1 + GlobalAFL + 3 + 1 + 2 + 2));
    uint32_t maskStartPrefix{ 0b1111'1111'1111'1111'1111'1111'0000'0000 };
    uint8_t maskStreamID{ 0b1111'1111 };
    uint16_t maskPacketLength{ 0b1111'1111'1111'1111 };

    m_PacketStartCodePrefix = temp & maskStartPrefix;
    m_PacketStartCodePrefix >>= 8;
    m_StreamId = temp3 & maskStreamID;
    m_PacketLength = temp2 & maskPacketLength;

    m_PacketLength2 = m_PacketLength + xTS::PES_HeaderLength;
    PESheaderSize += 6;
    if (m_StreamId != eStreamId::eStreamId_program_stream_map
        && m_StreamId != eStreamId::eStreamId_padding_stream
        && m_StreamId != eStreamId::eStreamId_private_stream_2
        && m_StreamId != eStreamId::eStreamId_ECM
        && m_StreamId != eStreamId::eStreamId_EMM
        && m_StreamId != eStreamId::eStreamId_program_stream_directory
        && m_StreamId != eStreamId::eStreamId_DSMCC_stream
        && m_StreamId != eStreamId::eStreamId_ITUT_H222_1_type_E
        ) {
        PESheaderSize += 2;
        PESheaderSize += 1;
        PESheaderSize += temp4;
    }
    return PESheaderSize;
}

