#include "xTS_AdaptationField.h"
#include <iostream>

using namespace std;

void xTS_AdaptationField::Reset() {

}

int32_t xTS_AdaptationField::Parse(const uint8_t* Input, uint8_t AdaptationFieldControl) {
    uint32_t temp = *((uint32_t*)(Input + 4));

    temp = xSwapBytes32(temp);
    uint32_t maskFieldLength{ 0b1111'1111'0000'0000'0000'0000'0000'0000 };
    uint32_t maskDiscontinuityI{ 0b0000'0000'1000'0000'0000'0000'0000'0000 };
    uint32_t maskRandomAccesI{ 0b0000'0000'0100'0000'0000'0000'0000'0000 };
    uint32_t maskStreamPriorityI{ 0b0000'0000'0010'0000'0000'0000'0000'0000 };
    uint32_t maskProgramClockReferenceF{ 0b0000'0000'0001'0000'0000'0000'0000'0000 };
    uint32_t maskOriginalpcrF{ 0b0000'0000'0000'1000'0000'0000'0000'0000 };
    uint32_t maskSplicingPointF{ 0b0000'0000'0000'0100'0000'0000'0000'0000 };
    uint32_t maskTransportPrivateDataF{ 0b0000'0000'0000'0010'0000'0000'0000'0000 };
    uint32_t maskAdaptationFieldExtensionF{ 0b0000'0000'0000'0001'0000'0000'0000'0000 };

    uint32_t adaptationFieldLength = temp & maskFieldLength;
    uint32_t discontinuityI = temp & maskDiscontinuityI;
    uint32_t randomAccessI = temp & maskRandomAccesI;
    uint32_t elementaryStreamPriorityI = temp & maskStreamPriorityI;
    uint32_t programClockReferenceF = temp & maskProgramClockReferenceF;
    uint32_t originalProgramClockReferenceF = temp & maskOriginalpcrF;
    uint32_t splicingPointF = temp & maskSplicingPointF;
    uint32_t transportPrivateDataF = temp & maskTransportPrivateDataF;
    uint32_t adaptationFieldExtension = temp & maskAdaptationFieldExtensionF;

    GlobalAFL = adaptationFieldLength >>= 24;
    dcc = discontinuityI >>= 23;
    random = randomAccessI >>= 22;
    priority = elementaryStreamPriorityI >>= 21;
    clockref = programClockReferenceF >>= 20;
    orgclockref = originalProgramClockReferenceF >>= 19;
    spliting = splicingPointF >>= 18;
    transportData = transportPrivateDataF >>= 17;
    extField = adaptationFieldExtension >>= 16;

    return temp;
}

void xTS_AdaptationField::Print() const {
    cout << " AF: L = " << GlobalAFL
        << " DC=" << dcc
        << " RA=" << random
        << " SP=" << priority
        << " PR=" << clockref
        << " OR=" << orgclockref
        << " SP=" << spliting
        << " TP=" << transportData
        << " EX=" << extField;
}
