/*
    Copyright 2015
*/

#ifndef SRC_BASE_SELECT_H_
#define SRC_BASE_SELECT_H_

#include "./err.h"

typedef struct {
    unsigned char   _4F     [1 + 16];
    unsigned char   _50     [1 + 16];
    unsigned char   _87     [1 +  1];
    unsigned char   _9F2A   [1 +  1];
} FciIssData, *FciIssDataPtr;

typedef struct {
    unsigned char   _84     [1 + 16];
    FciIssData      _fciIssData[10    ];
    int             _fciIssDataCount;
} Fci, *FciPtr;

//--------------------------------

inline int _clearFci(FciPtr r)
{
    if (!r) return INVALID_PARAMETER;
    memset(r, 0x00, sizeof(Fci));
    return SUCCESS;
}

inline int _setFciIssData(FciPtr r, int tag, const unsigned char* value, int size)
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

inline int _set84(FciPtr r, const unsigned char* val, int size)
{
    r->_84[0] = 0x01;
    memcpy(r->_84+1, val, size);
}

inline int _incFciIssDataCounter(FciPtr r)
{
    if (r->_fciIssDataCount>=10) return -99; // TODO
    r->_fciIssDataCount++;
    return SUCCESS;
}


int selectPpse(FciPtr pFci);

int _buildSelect(const char* aid, int size, unsigned char* pBuffer, int* pSize);
int _buildSelectPpse(unsigned char* pBuffer, int* pSize);
int _resolveSelectPpse(const unsigned char* pData, int size, FciPtr fci);

int OnTag_resolvePpse(int tag, int len, int constructed, const unsigned char* val, FciPtr target);


#endif// SRC_BASE_SELECT_H_
