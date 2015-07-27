/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#include <string.h>  // memset

#include "./fci.h"
#include "../Common/err.h"
#include "../Common/general.h"
#include "../Common/bits.h"
#include "fci.h"

//-----------------------------------------------------------------------

int _clearFci(FciPtr r)
{
    if (!r) return NULL_PARAMETER;
    memset(r, 0x00, sizeof(Fci));
    return SUCCESS;
}

//-----------------------------------------------------------------------

int _setDirectoryEntry(FciPtr r, int tag, const unsigned char *value, int size)
{
    if (!r || !value || size == 0) return NULL_PARAMETER;
    if (r->_directoryEntryCount == 0) return INDEX_OUT_OF_RANGE;

    switch(tag) {
        case 0x4F:
            if (size > 16) return INCORRECT_DATA;
            r->_directoryEntry[r->_directoryEntryCount -1]._4F[0] = size;
            memcpy(r->_directoryEntry[r->_directoryEntryCount -1]._4F+1, value, size);
        break;
        case 0x50:
            if (size > 16) return INCORRECT_DATA;
            r->_directoryEntry[r->_directoryEntryCount -1]._50[0] = size;
            memcpy(r->_directoryEntry[r->_directoryEntryCount -1]._50+1, value, size);
        break;
        case 0x87:
            if (size > 1) return INCORRECT_DATA;
            r->_directoryEntry[r->_directoryEntryCount -1]._87[0] = size;
            memcpy(r->_directoryEntry[r->_directoryEntryCount -1]._87+1, value, size);
        break;
        case 0x9F2A:
            if (size > 1) return INCORRECT_DATA;
            r->_directoryEntry[r->_directoryEntryCount -1]._9F2A[0] = size;
            memcpy(r->_directoryEntry[r->_directoryEntryCount -1]._9F2A+1, value, size);
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

int _incDirectoryEntryCounter(FciPtr r)
{
    if (!r) return NULL_PARAMETER;
    if (r->_directoryEntryCount >= 10) return INDEX_OUT_OF_RANGE;
    r->_directoryEntryCount++;
    return SUCCESS;
}

//-----------------------------------------------------------------------

int getAdfNameLen(DirectoryEntryPtr p)
{
    return (int)(p->_4F[0]);
}

//-----------------------------------------------------------------------

unsigned char* getAdfName(DirectoryEntryPtr p)
{
    return &(p->_4F[1]);
}

//-----------------------------------------------------------------------

int getApplicationLabelLen(DirectoryEntryPtr p)
{
    return (int)(p->_50[0]);
}

//-----------------------------------------------------------------------

unsigned char* getApplicationLabel(DirectoryEntryPtr p)
{
    return &(p->_50[1]);
}

//-----------------------------------------------------------------------

int getAPILen(DirectoryEntryPtr p)
{
    return (int)(p->_87[0]);
}

//-----------------------------------------------------------------------

int getAPI(DirectoryEntryPtr p)
{
    return (int)(p->_87[1]);
}

//-----------------------------------------------------------------------

int getKernelIdLen(DirectoryEntryPtr p)
{
    return (int)(p->_9F2A[0]);
}

//-----------------------------------------------------------------------

int getKernelId(DirectoryEntryPtr p)
{
    return MAKEWORD(p->_9F2A[1], p->_9F2A[2]);
}

//-----------------------------------------------------------------------

int isKernelIdExist(DirectoryEntryPtr p)
{
    return (p->_9F2A[0] != 0x00) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------

int isAdfNameExist(DirectoryEntryPtr p)
{
    return (p->_4F[0] != 0x00);
}

//-----------------------------------------------------------------------

int isAdfNameValid(DirectoryEntryPtr p)
{
    // TODO
    // EMV 4.2 Book 1 12.2.1
    /*
     * ADF and DF Names consists of two parts:
     *     1. RID (Registered Application Provider Identifier)              5 bytes
     *     2. PIX (Optional field assigned by application provider) up to   11 bytes, 0 is ok
     * */

    if (!p) return NULL_PARAMETER;

    if (p->_4F[0] < 5 || p->_4F[0] > 16)
        return FALSE;
    return TRUE;
}

//-----------------------------------------------------------------------

TypeOfKernels getKernelType(DirectoryEntryPtr p)
{
    /*
        Book B v2.5 p.23
        Table 3-4
    */
    printf("%d %d %d\n", CHECK_BIT(p->_9F2A[1], 8), CHECK_BIT(p->_9F2A[1], 7), CHECK_BIT(p->_9F2A[1], 6));

    if (CHECK_BIT(p->_9F2A[1], 8) == RESET && CHECK_BIT(p->_9F2A[1], 7) == RESET) {
        // b8, b7: 00b
        return InternationalKernel;
    } else if (CHECK_BIT(p->_9F2A[1], 8) == SET && CHECK_BIT(p->_9F2A[1], 7) == RESET) {
        // b8, b7: 10b
        return DomesticKernelEmvCoFormat;
    } else if (CHECK_BIT(p->_9F2A[1], 8) == SET && CHECK_BIT(p->_9F2A[1], 7) == SET) {
        // b8, b7: 11b
        return DomesticKernelPropFormat;
    }
    // b8, b7: 01b
    return RfuKernel;
}

//-----------------------------------------------------------------------

int getShortKernelId(DirectoryEntryPtr p)
{
    /*
        Book B v2.5 p.23
        Table 3-4
    */
    return (int)(p->_9F2A[1] & 0xC0);
}

int foo(FciPtr r, int tag, const unsigned char *value, int size)
{
    return SUCCESS;
}