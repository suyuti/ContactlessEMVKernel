#include "tlv.h"

int _tag(const unsigned char* pData, int* pTagLen, int* pConstructed)
{
    if (!pData||!pTagLen||!pConstructed) return -1;
    int tagSize = 1;
    if ((pData[0] & 0x20) == 0x20) *pConstructed = 1;
    if ((pData[0] & 0x1F) == 0x1F) {
        tagSize++;
        int i = 0;
        while((pData[++i] & 0x80) == 0x80) {
            tagSize++;
        }
    }
    *pTagLen += tagSize;
    return toInt(pData, tagSize);
}

int _len(const unsigned char* pData, int* pLenLen)
{
    *pLenLen = 0;
    if (pData[*pLenLen] == 0x81) {
        *pLenLen += 1;
    }
    *pLenLen += 1;
    return pData[*pLenLen - 1];
}

