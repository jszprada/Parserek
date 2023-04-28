#include "xPES_Assembler.h"
#include <iostream>
#include "xTS_AdaptationField.h"
#include "xTS_PacketHeader.h"
#include "tsTransportStream.h"

using namespace std;

int32_t xPES_Assembler::Parse(const uint8_t* Input, const xTS_PacketHeader PacketHeader, const xTS_AdaptationField AdaptationField) {
    int32_t pessize = xTS::TS_PacketLength - xTS::TS_HeaderLength;
    const char* outFile = "C:/Users/jszpr/Desktop/kodzik/Test2.mp2";

    if (PacketHeader.getPayload() == 1) {
        uint8_t header_size = (uint8_t)m_PESH.Parse(Input, AdaptationField.getAFL());
        Input += xTS::TS_HeaderLength;

        if (PacketHeader.getAdaptationFieldControl() == 2 || PacketHeader.getAdaptationFieldControl() == 3) {
            pessize -= (1 + AdaptationField.getAFL());
            Input += (1 + AdaptationField.getAFL());
        }

        pessize -= header_size;
        Input += header_size;

        FILE* pFile = fopen(outFile, "ab");
        fwrite(Input, sizeof(uint8_t), pessize, pFile);
        fclose(pFile);
    }
    else if (PacketHeader.getContinuity() == 15) {
        FILE* pFile = fopen(outFile, "ab");
        pessize -= 48;
        Input += 52;
        fwrite(Input, sizeof(uint8_t), pessize, pFile);
        fclose(pFile);
    }
    else {
        Input += 4;
        FILE* pFile = fopen(outFile, "ab");
        fwrite(Input, sizeof(uint8_t), pessize, pFile);
        fclose(pFile);
    }

    return pessize;
}