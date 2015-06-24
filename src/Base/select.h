/*
    Copyright 2015
*/

#ifndef SRC_BASE_SELECT_H_
#define SRC_BASE_SELECT_H_

#include "./err.h"

/*----------------------------------------------------------------------
    Book B p.21
    Table 3-2
    SELECT Response Message Data Field (FCI) of the PPSE
*/
typedef struct {
    unsigned char   _4F     [1 + 16];   // ADF Name
    unsigned char   _50     [1 + 16];   // Application Label
    unsigned char   _87     [1 +  1];   // Application priority indicator
    unsigned char   _9F2A   [1 +  1];   // Kernel identifier
} FciIssData, *FciIssDataPtr;

typedef struct {
    unsigned char   _84     [1 + 16];
    FciIssData      _fciIssData[10    ];
    int             _fciIssDataCount;
} Fci, *FciPtr;

//--------------------------------

int _clearFci(FciPtr r);
int _setFciIssData(FciPtr r, int tag, const unsigned char* value, int size);
int _set84(FciPtr r, const unsigned char* val, int size);
int _incFciIssDataCounter(FciPtr r);

int selectPpse(FciPtr pFci);

int _buildSelect(const char* aid, int size, unsigned char* pBuffer, unsigned long* pSize);
int _buildSelectPpse(unsigned char* pBuffer, unsigned long* pSize);
int _resolveSelectPpse(const unsigned char* pData, int size, FciPtr fci);

int OnTag_resolvePpse(int tag, int len, int constructed, const unsigned char* val, FciPtr target);


#endif// SRC_BASE_SELECT_H_
