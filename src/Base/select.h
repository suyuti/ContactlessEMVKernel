/*
    Copyright 2015
*/

#ifndef SRC_BASE_SELECT_H_
#define SRC_BASE_SELECT_H_

#include "./err.h"
#include "./fci.h"



//--------------------------------


int selectPpse(FciPtr pFci);

int _buildSelect(const char* aid, int size, unsigned char* pBuffer, unsigned long* pSize);
int _buildSelectPpse(unsigned char* pBuffer, unsigned long* pSize);
int _resolveSelectPpse(const unsigned char* pData, int size, FciPtr fci);

int OnTag_resolvePpse(int tag, int len, int constructed, const unsigned char* val, FciPtr target);

unsigned short getLastSw();


#endif// SRC_BASE_SELECT_H_
