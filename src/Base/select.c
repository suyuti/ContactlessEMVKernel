/*
    Copyright 2015
*/

#include <string.h>
#include "./select.h"
#include "./tlv.h"
#include "./err.h"
#include "../Hal/hal.h"

#define PPSE        "2PAY.SYS.DDF01"

static unsigned char gTmp1[1024];
static unsigned char gTmp2[1024];
static int gSize = 0;

//-----------------------------------------------------------------------

int selectPpse(FciPtr pFci)
{
    int err = _buildSelectPpse(gTmp1, &gSize);
    if (err != SUCCESS) return err;

    err = CR_SENDRECV(ggprofTmp1, gSize, gTmp2, &gSize);
    if (err != SUCCESS) return err;

    err = _resolveSelectPpse(gTmp2, gSize, pFci);
    return err;
}

//-----------------------------------------------------------------------

int _buildSelect(const char* aid, int size, unsigned char* pBuffer, int* pSize)
{
    if (!pBuffer || !pSize || !aid || size==0) return -1;

    pBuffer[0] = 0x00;
    pBuffer[1] = 0xA4;
    pBuffer[2] = 0x04;
    pBuffer[3] = 0x00;
    pBuffer[4] = (unsigned char)size;
    memcpy(pBuffer+5, (unsigned char*)aid, size);
    *pSize = size + 5;

    return 0;
}

//-----------------------------------------------------------------------

int _buildSelectPpse(unsigned char* pBuffer, int* pSize)
{
    return _buildSelect(PPSE, sizeof(PPSE)-1, pBuffer, pSize);
}

//-----------------------------------------------------------------------

int _resolveSelectPpse(const unsigned char* pData, int size, FciPtr fci)
{
    if (!pData || size == 0 || !fci) return INVALID_PARAMETER;

    int res =  _parse(pData, size, (OnTag)OnTag_resolvePpse, fci);
    return res;
}

//-----------------------------------------------------------------------

int OnTag_resolvePpse(int tag, int len, int constructed, const unsigned char* val, FciPtr target)
{
    switch(tag) {
        case 0x6F: // check mandatory
        break;
        case 0x84:
            _set84(target, val, len);
        break;
        case 0xBF0C:
        break;
        case 0xA5:
            // mandatory check
        break;
        case 0x61:
            _incFciIssDataCounter(target);
        break;
        default:
            _setFciIssData(target, tag, val, len);
        break;
    }
    return SUCCESS;
}
