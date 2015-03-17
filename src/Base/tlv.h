/*
    Copyright 2015
*/

#ifndef SRC_BASE_TLV_H_
#define SRC_BASE_TLV_H_

typedef int (*OnTag)(int tag, int len, const unsigned char* val, void* target);

int _tag(const unsigned char* pData, int* pTagLen, int* pConstructed);
int _len(const unsigned char* pData, int* pLenLen);
int _parse(const unsigned char* data,
            int size,
            OnTag onTag,
            void* target);

#endif// SRC_BASE_TLV_H_
