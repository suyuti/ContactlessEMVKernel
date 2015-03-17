#ifndef _TLV_H_
#define _TLV_H_

typedef int (*OnTag)(int tag, int len, const unsigned char* val, void* target);

int _tag(const unsigned char* pData, int* pTagLen, int* pConstructed);
int _len(const unsigned char* pData, int* pLenLen);
int _parse(const unsigned char* data, 
            int size, 
            OnTag onTag, 
            void* target);

#endif// _TLV_H_
