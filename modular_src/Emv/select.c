/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#include <string.h>
#include "./select.h"
#include "../Common/tlv.h"
#include "../Common/err.h"
#include "../Common/common.h"
#include "../Common/hal.h"
// #include "./kernel.h"
#include "../Common/general.h"

#define PPSE        "2PAY.SYS.DDF01"

static unsigned char    gTmp1[1024];    // output buffer: Terminal writes
static unsigned char    gTmp2[1024];    // input buffer : Card writes
static unsigned long    gSize = 0;
static unsigned short   gLastSW;

//-----------------------------------------------------------------------

unsigned short getLastSw()
{
    return gLastSW;
}

//-----------------------------------------------------------------------

int _select(void)
{
    HalInterfacesPtr pHal = getHal();
    gLastSW = MAKEWORD(0, 0);
    memset(gTmp2, 0x00, sizeof(gTmp2));

    int err = CARD_TRANSMIT(pHal, gTmp1, gSize, gTmp2, &gSize);
    IS_SUCCESS(err);

    if (gSize >= 2) {
        gLastSW = MAKEWORD(gTmp2[gSize-2], gTmp2[gSize-1]);
        if (gSize == 2 && getLastSw() != MAKEWORD(0x90, 0x00)) {
            return SW_NOT_SUCCESS;
        }
    } else {
        return SW_NOT_FOUND;
    }

    return err;
}

//-----------------------------------------------------------------------

int selectAid(FciPtr pFci, const unsigned char* aid, int aidLen)
{
    int err = _buildSelect(aid, aidLen, gTmp1, &gSize);
    IS_SUCCESS(err);

    err = _select();
    IS_SUCCESS(err);

    err = _resolveSelectAid(gTmp2, gSize, pFci);
    IS_SUCCESS(err);

    return err;
}

int selectPpse(FciPtr pFci)
{
    if (!pFci) return NULL_PARAMETER;
    int err = _buildSelectPpse(gTmp1, &gSize);
    IS_SUCCESS(err);

    err = _select();
    IS_SUCCESS(err);

    err = _resolveSelectPpse(gTmp2, gSize-2, pFci);

    return err;
}

int _resolveSelectAid(const unsigned char* pData, int size, FciPtr fci)
{
    if (!pData || size == 0 || !fci) return NULL_PARAMETER;

    int res =  _parse(pData, size, (OnTag)OnTag_resolveAid, fci);
    return res;
}

//-----------------------------------------------------------------------

int _buildSelect(const unsigned char* aid, int size, unsigned char* pBuffer, unsigned long* pSize)
{
    if (!pBuffer || !pSize || !aid || size == 0) return NULL_PARAMETER;

    pBuffer[0] = 0x00;
    pBuffer[1] = 0xA4;
    pBuffer[2] = 0x04;
    pBuffer[3] = 0x00;
    pBuffer[4] = (unsigned char)size;
    memcpy(pBuffer+5, aid, size);
    *pSize = size + 5;

    return SUCCESS;
}

//-----------------------------------------------------------------------

int _buildSelectPpse(unsigned char* pBuffer, unsigned long* pSize)
{
    return _buildSelect((const unsigned char*)PPSE, sizeof(PPSE)-1, pBuffer, pSize);
}

//-----------------------------------------------------------------------

int _resolveSelectPpse(const unsigned char* pData, int size, FciPtr fci)
{
    if (!pData || size == 0 ||  !fci) return NULL_PARAMETER;

    int res =  _parse(pData, size, (OnTag)OnTag_resolvePpse, fci);
    return res;
}

//-----------------------------------------------------------------------
int OnTag_resolveAid(int tag, int len, int constructed, const unsigned char* val, FciPtr target)
{
    return SUCCESS;
}

int OnTag_resolvePpse(int tag, int len, int constructed, const unsigned char* val, FciPtr target)
{
    int err;
    if (!target || len == 0) return NULL_PARAMETER;
    // if (constructed == 1 && !val) return NULL_PARAMETER;
    switch(tag) {
        case 0x6F:  // check mandatory
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

