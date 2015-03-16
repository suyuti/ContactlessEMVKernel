#ifndef _TLV_H_
#define _TLV_H_

int _tag(const unsigned char* pData, int* pTagLen, int* pConstructed);
int _len(const unsigned char* pData, int* pLenLen);

#endif// _TLV_H_
