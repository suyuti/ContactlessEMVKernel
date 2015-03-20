/*
    Copyright 2015
*/

#include <string.h>
#include "./select.h"
#include "./tlv.h"
#include "./err.h"
#include "../Hal/hal.h"
#include "./kernel.h"

#define PPSE        "2PAY.SYS.DDF01"

static unsigned char gTmp1[1024];
static unsigned char gTmp2[1024];
static unsigned long gSize = 0;

//-----------------------------------------------------------------------

int selectPpse(FciPtr pFci)
{
    int err = _buildSelectPpse(gTmp1, &gSize);
    if (err != SUCCESS) return err;

    err = gCrSendRecv(gTmp1, gSize, gTmp2, &gSize);
    if (err != SUCCESS) return err;

    err = _resolveSelectPpse(gTmp2, gSize, pFci);
    return err;
}

//-----------------------------------------------------------------------

int _buildSelect(const char* aid, int size, unsigned char* pBuffer, unsigned long* pSize)
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

int _buildSelectPpse(unsigned char* pBuffer, unsigned long* pSize)
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
//    printf("Tag: %X\n", tag);
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

//-----------------------------------------------------------------------

int _clearFci(FciPtr r)
{
    if (!r) return INVALID_PARAMETER;
    memset(r, 0x00, sizeof(Fci));
    return SUCCESS;
}

//-----------------------------------------------------------------------

int _setFciIssData(FciPtr r, int tag, const unsigned char* value, int size)
{
    if (!r) return INVALID_PARAMETER;
    if (r->_fciIssDataCount == 0) return -99; // TODO

    switch(tag) {
        case 0x4F:
            if (size > 16) return INCORRECT_DATA;
            r->_fciIssData[r->_fciIssDataCount-1]._4F[0] = 0x01;
            memcpy(r->_fciIssData[r->_fciIssDataCount-1]._4F+1, value, size);
        break;
        case 0x50:
            if (size > 16) return INCORRECT_DATA;
            r->_fciIssData[r->_fciIssDataCount-1]._50[0] = 0x01;
            memcpy(r->_fciIssData[r->_fciIssDataCount-1]._50+1, value, size);
        break;
        case 0x87:
            if (size > 1) return INCORRECT_DATA;
            r->_fciIssData[r->_fciIssDataCount-1]._87[0] = 0x01;
            memcpy(r->_fciIssData[r->_fciIssDataCount-1]._87+1, value, size);
        break;
        case 0x9F2A:
            if (size > 1) return INCORRECT_DATA;
            r->_fciIssData[r->_fciIssDataCount-1]._9F2A[0] = 0x01;
            memcpy(r->_fciIssData[r->_fciIssDataCount-1]._9F2A+1, value, size);
        break;
        default:
        break;
    }
    return SUCCESS;
}

//-----------------------------------------------------------------------

int _set84(FciPtr r, const unsigned char* val, int size)
{
    r->_84[0] = 0x01;
    memcpy(r->_84+1, val, size);
}

//-----------------------------------------------------------------------

int _incFciIssDataCounter(FciPtr r)
{
    if (r->_fciIssDataCount>=10) return -99; // TODO
    r->_fciIssDataCount++;
    return SUCCESS;
}
