/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#include <string.h> // memset

#include "./fci.h"
#include "../Common/err.h"
#include "../Common/general.h"
#include "../Common/bits.h"

//-----------------------------------------------------------------------

int _clearFci(FciPtr r)
{
    if (!r) return NULL_PARAMETER;
    memset(r, 0x00, sizeof(Fci));
    return SUCCESS;
}

//-----------------------------------------------------------------------

int _setFciIssData(FciPtr r, int tag, const unsigned char* value, int size)
{
    if (!r || !value || size == 0) return NULL_PARAMETER;
    if (r->_fciIssDataCount == 0) return INDEX_OUT_OF_RANGE;

    switch(tag) {
        case 0x4F:
            if (size > 16) return INCORRECT_DATA;
            r->_fciIssData[r->_fciIssDataCount-1]._4F[0] = size;
            memcpy(r->_fciIssData[r->_fciIssDataCount-1]._4F+1, value, size);
        break;
        case 0x50:
            if (size > 16) return INCORRECT_DATA;
            r->_fciIssData[r->_fciIssDataCount-1]._50[0] = size;
            memcpy(r->_fciIssData[r->_fciIssDataCount-1]._50+1, value, size);
        break;
        case 0x87:
            if (size > 1) return INCORRECT_DATA;
            r->_fciIssData[r->_fciIssDataCount-1]._87[0] = size;
            memcpy(r->_fciIssData[r->_fciIssDataCount-1]._87+1, value, size);
        break;
        case 0x9F2A:
            if (size > 1) return INCORRECT_DATA;
            r->_fciIssData[r->_fciIssDataCount-1]._9F2A[0] = size;
            memcpy(r->_fciIssData[r->_fciIssDataCount-1]._9F2A+1, value, size);
        break;
        default:
            return UNKNOWN_TAG;
        break;
    }
    return SUCCESS;
}

//-----------------------------------------------------------------------

int _set84(FciPtr r, const unsigned char* val, int size)
{
    r->_84[0] = 0x01;
    memcpy(r->_84+1, val, size);
    return SUCCESS;
}

//-----------------------------------------------------------------------

int _incFciIssDataCounter(FciPtr r)
{
    if (!r) return NULL_PARAMETER;
    if (r->_fciIssDataCount>=10) return INDEX_OUT_OF_RANGE;
    r->_fciIssDataCount++;
    return SUCCESS;
}

//-----------------------------------------------------------------------

int getAdfNameLen(FciIssDataPtr p)
{
    return static_cast<int>(p->_4F[0]);
}

//-----------------------------------------------------------------------

unsigned char* getAdfName(FciIssDataPtr p)
{
    return &(p->_4F[1]);
}

//-----------------------------------------------------------------------

int getApplicationLabelLen(FciIssDataPtr p)
{
    return static_cast<int>(p->_50[0]);
}

//-----------------------------------------------------------------------

unsigned char* getApplicationLabel(FciIssDataPtr p)
{
    return &(p->_50[1]);
}

//-----------------------------------------------------------------------

int getAPILen(FciIssDataPtr p)
{
    return static_cast<int>(p->_87[0]);
}

//-----------------------------------------------------------------------

int getAPI(FciIssDataPtr p)
{
    return static_cast<int>(p->_87[1]);
}

//-----------------------------------------------------------------------

int getKernelIdLen(FciIssDataPtr p)
{
    return static_cast<int>(p->_9F2A[0]);
}

//-----------------------------------------------------------------------

int getKernelId(FciIssDataPtr p)
{
    return MAKEWORD(p->_9F2A[1], p->_9F2A[2]);
}

//-----------------------------------------------------------------------

int isKernelIdExist(FciIssDataPtr p)
{
    return (p->_9F2A[0] != 0x00) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------

int isAdfNameExist(FciIssDataPtr p)
{
    return (p->_4F[0] != 0x00);
}

//-----------------------------------------------------------------------

int isAdfNameValid(FciIssDataPtr p)
{
    // TODO
    // EMV 4.2 Book 1 12.2.1
    return TRUE;
}

//-----------------------------------------------------------------------

TypeOfKernels getKernelType(FciIssDataPtr p)
{
    /*
        Book B v2.5 p.23
        Table 3-4
    */
    if (CHECK_BIT(p->_9F2A[0], 8) == RESET && CHECK_BIT(p->_9F2A[0], 7) == RESET) {
        // b8, b7: 00b
        return InternationalKernel;
    } else if (CHECK_BIT(p->_9F2A[0], 8) == SET && CHECK_BIT(p->_9F2A[0], 7) == RESET) {
        // b8, b7: 10b
        return DomesticKernelEmvCoFormat;
    } else if (CHECK_BIT(p->_9F2A[0], 8) == SET && CHECK_BIT(p->_9F2A[0], 7) == SET) {
        // b8, b7: 11b
        return DomesticKernelPropFormat;
    }
    // b8, b7: 01b
    return RfuKernel;
}

//-----------------------------------------------------------------------

int getShortKernelId(FciIssDataPtr p)
{
    /*
        Book B v2.5 p.23
        Table 3-4
    */
    return static_Cast<int>(p->_9F2A[1] & 0xC0);
}
