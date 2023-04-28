#include "tsCommon.h"
#include "tsTransportStream.h"
#include "xTS_PacketHeader.h"
#include <bits.h>
#include <cstdio>
#include <iostream>
#include <string.h>
#include "xTS_AdaptationField.h"
#include "xPES_Assembler.h"

using namespace std;

const string outFile = "C:/Users/jszpr/Desktop/kodzik/Test2.mp2";
const string inFile = "C:/Users/jszpr/Desktop/kodzik/example_new.ts";

int main()
{
    FILE* pFile;
    pFile = fopen(inFile.c_str(), "rb");
    if (pFile == NULL) {
        fputs ("File error", stderr);
        exit (1);
    }
   
    cout << "start parsing\n";

    xTS_PacketHeader TS_PacketHeader;
    xTS_AdaptationField AdaptationField{};
    xPES_Assembler PES_Assembler;
    xPES_PacketHeader xPES;
    
    int32_t TS_PacketId = 0;
    uint32_t continuityTemp = 0;

    uint8_t* buffer;
    buffer = (uint8_t*)malloc(sizeof(uint8_t) * xTS::TS_PacketLength);
    if (buffer == nullptr) {
        fputs("Memory error", stderr);
        exit(1);
    }

    while (!feof(pFile)
        || TS_PacketId < 100000
        ) {
        fread(buffer, xTS::TS_PacketLength, 1, pFile);
        TS_PacketHeader.Parse(TS_PacketId, buffer);
        
        if (TS_PacketHeader.getSyncByte() == 'G' && TS_PacketHeader.getPID() == 136) {
            cout << endl << TS_PacketId;
            if (TS_PacketHeader.hasAdaptationField()) {
                AdaptationField.Parse(buffer, TS_PacketHeader.getAdaptationFieldControl());
            }
            PES_Assembler.Parse(buffer, TS_PacketHeader, AdaptationField);
            if (TS_PacketHeader.getPayload() == 1) {
                xPES.Parse(buffer, AdaptationField.getAFL());
            }
        }
        TS_PacketId++;
    }

    free(buffer);
    fclose(pFile);
    cout << "parsing end";
    return 0;
}