/*
    Copyright 2015
*/

#ifndef MODULAR_SRC_COMMON_TLV_H_
#define MODULAR_SRC_COMMON_TLV_H_

typedef int (*OnTag)(int tag, int len, int constructed, const unsigned char* val, void* target);

int _tag(const unsigned char* pData, int* pTagLen, int* pConstructed);
int _len(const unsigned char* pData, int* pLenLen);
int _parse(const unsigned char* data,
            int size,
            OnTag onTag,
            void* target);

#endif// MODULAR_SRC_COMMON_TLV_H_
