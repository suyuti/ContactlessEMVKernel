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

static unsigned char    gsTmp1[256 + 1];    // output buffer: Terminal writes
static unsigned char    gsTmp2[256 + 1];    // input buffer : Card writes
static unsigned long    gsSize1 = 0;
static unsigned long    gsSize2 = 0;
static unsigned short   gLastSW;

//-----------------------------------------------------------------------

unsigned short getLastSw()
{
    return gLastSW;
}

//-----------------------------------------------------------------------

int _select(void)
{
    memset(gsTmp2, 0x00, sizeof(gsTmp2));
    int err = card_transmit(gsTmp1, gsSize1, gsTmp2, &gsSize2);
    if (err != SUCCESS) return err;
    if (gsSize2 < 2) return SW_NOT_FOUND;
    gLastSW = MAKE_SW(gsTmp2, gsSize2);
    if (gLastSW != MAKEWORD(0x90, 0x00)) {
        return SW_NOT_SUCCESS;
    }
    return SUCCESS;
}

//-----------------------------------------------------------------------

int selectAid(FciPtr pFci, const unsigned char* aid, int aidLen)
{
    int err = _buildSelect(aid, aidLen, gsTmp1, &gsSize1);
    IS_SUCCESS(err);

    err = _select();
    IS_SUCCESS(err);

    err = _resolveSelectAid(gsTmp2, gsSize2-2, pFci);
    IS_SUCCESS(err);

    return err;
}

int selectPpse(FciPtr pFci)
{
    if (!pFci) return NULL_PARAMETER;
    int err = _buildSelectPpse(gsTmp1, &gsSize1);
    IS_SUCCESS(err);

    err = _select();
    IS_SUCCESS(err);

    err = _resolveSelectPpse(gsTmp2, gsSize2 - 2, pFci);

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

