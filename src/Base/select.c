/*
    Copyright 2015
*/

#include <string.h>
#include "./select.h"
#include "./tlv.h"
#include "./err.h"
#include "../Hal/hal.h"
#include "./kernel.h"
#include "./general.h"

#define PPSE        "2PAY.SYS.DDF01"

static unsigned char    gTmp1[1024];
static unsigned char    gTmp2[1024];
static unsigned long    gSize = 0;
static unsigned short   gLastSW;

//-----------------------------------------------------------------------

unsigned short getLastSw() 
{
    return gLastSW;
}

//-----------------------------------------------------------------------

int selectPpse(FciPtr pFci)
{
    if (!pFci) return NULL_PARAMETER;
    int err = _buildSelectPpse(gTmp1, &gSize);
    if (err != SUCCESS) return err;

    gLastSW = MAKEWORD(0, 0);
    err = CARD_TRANSMIT(&gHal, gTmp1, gSize, gTmp2, &gSize);
/*
    int i = 0;
    for (i = 0; i < gSize; ++i) {
        printf("%02X ", gTmp2[i]);
    }
    printf("\n");
*/

    if (err != SUCCESS) return err;

    if (gSize >= 2) {
        gLastSW = MAKEWORD(gTmp2[gSize-2], gTmp2[gSize-1]);
    }
    else {
        return SW_NOT_SUCCESS;
    }
    if (gLastSW == MAKEWORD(0x90, 0x00)) {
        err = _resolveSelectPpse(gTmp2, gSize-2, pFci);
    }
    return err;
}

//-----------------------------------------------------------------------

int _buildSelect(const char* aid, int size, unsigned char* pBuffer, unsigned long* pSize)
{
    if (!pBuffer || !pSize || !aid || size==0) return NULL_PARAMETER;

    pBuffer[0] = 0x00;
    pBuffer[1] = 0xA4;
    pBuffer[2] = 0x04;
    pBuffer[3] = 0x00;
    pBuffer[4] = (unsigned char)size;
    memcpy(pBuffer+5, (unsigned char*)aid, size);
    *pSize = size + 5;

    return SUCCESS;
}

//-----------------------------------------------------------------------

int _buildSelectPpse(unsigned char* pBuffer, unsigned long* pSize)
{
    return _buildSelect(PPSE, sizeof(PPSE)-1, pBuffer, pSize);
}

//-----------------------------------------------------------------------

int _resolveSelectPpse(const unsigned char* pData, int size, FciPtr fci)
{
    if (!pData || size == 0 || !fci) return NULL_PARAMETER;

    int res =  _parse(pData, size, (OnTag)OnTag_resolvePpse, fci);
    return res;
}

//-----------------------------------------------------------------------

int OnTag_resolvePpse(int tag, int len, int constructed, const unsigned char* val, FciPtr target)
{
    int err;
    if (!target || len == 0) return NULL_PARAMETER;
    //if (constructed == 1 && !val) return NULL_PARAMETER;
    switch(tag) {
        case 0x6F: // check mandatory
            err = SUCCESS;
        break;
        case 0x84:
            err = _set84(target, val, len);
        break;
        case 0xBF0C:
            err = SUCCESS;
        break;
        case 0xA5:
            // mandatory check
            err = SUCCESS;
        break;
        case 0x61:
            err = _incFciIssDataCounter(target);
        break;
        default:
            err = _setFciIssData(target, tag, val, len);
        break;
    }
    return err;
}

//-----------------------------------------------------------------------

