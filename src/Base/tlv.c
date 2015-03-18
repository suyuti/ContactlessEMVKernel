/*
    Copyright 2015
*/

#include <stdlib.h>
#include "./tlv.h"
#include "./err.h"

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

//-----------------------------------------------------------------------

int _len(const unsigned char* pData, int* pLenLen)
{
    if (!pData || !pLenLen) return -1;
    *pLenLen = 0;
    if (pData[*pLenLen] == 0x81) {
        *pLenLen += 1;
    }
    *pLenLen += 1;
    return pData[*pLenLen - 1];
}

//-----------------------------------------------------------------------

int _parse( const unsigned char* data,
            int size,
            OnTag onTag,
            void* target)
{
    int tagLen = 0;
    int lenLen = 0;
    int constructed = 0;
    int len;
    int tag;
    int err = SUCCESS;

    if (!data || !onTag || !target) return INVALID_PARAMETER;
    if (size<3) return INCORRECT_DATA;

    tag = _tag(data, &tagLen, &constructed);
    len = _len(data+tagLen, &lenLen);

    if (len+tagLen+lenLen > size) {
        return INCORRECT_DATA;}

    //gTagList[gTagListIndex++] = tag;
    if (constructed == 1) {
        err = onTag(tag, len, constructed, NULL, target);
        if (err != SUCCESS) return err;
        err = _parse(data+tagLen+lenLen, len, onTag, target);
        if (err != SUCCESS) return err;
    } else {
        err = onTag(tag, len, constructed, data+tagLen+lenLen, target);
        if (err != SUCCESS) return err;
    }
    if (tagLen+lenLen+len < size) {
        err = _parse(data+tagLen+lenLen+len, size-(tagLen+lenLen+len), onTag, target);
        if (err != SUCCESS) return err;
    }
    return err;
}

//-----------------------------------------------------------------------
