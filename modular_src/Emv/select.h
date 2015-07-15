/*
    Copyright 2015
*/

#ifndef MODULAR_SRC_EMV_SELECT_H_
#define MODULAR_SRC_EMV_SELECT_H_

#include "./err.h"
#include "./fci.h"



//--------------------------------


int selectPpse(FciPtr pFci);
int selectAid(FciPtr pFci, const unsigned char* aid, int aidLen);

int _select();
int OnTag_resolveAid(int tag, int len, int constructed, const unsigned char* val, FciPtr target);

int _buildSelect(const unsigned char* aid, int size, unsigned char* pBuffer, unsigned long* pSize);
int _buildSelectPpse(unsigned char* pBuffer, unsigned long* pSize);
int _resolveSelectPpse(const unsigned char* pData, int size, FciPtr fci);

int OnTag_resolvePpse(int tag, int len, int constructed, const unsigned char* val, FciPtr target);

unsigned short getLastSw();
int _resolveSelectAid(const unsigned char* pData, int size, FciPtr fci);



#endif  // MODULAR_SRC_EMV_SELECT_H_
