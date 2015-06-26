/*
    Copyright 2015
*/

#include <stdio.h>
#include "./utils.h"
#include "./err.h"

int toInt(const unsigned char* ptag, int size)
{
    if (!ptag || size==0) return -1;

    unsigned int val = 0;
    int digit = 1;
    while (size--) {
        val += digit * (unsigned char)ptag[size];
        digit *= 0x100;
    }
    return val;
}

//-----------------------------------------------------------------------------
int str2bcd(const unsigned char* str, int size, unsigned char* pOut, int* pOutSize) 
{
    if ((size % 2) != 0) return INCORRECT_DATA;
    int j = 0;
    int i = 0;
    char c;
    for(i = 0; i<size;++i) {
        c = str[i];
        if (c>='0' && c<='9') {
            c -= '0';
        }
        else if (c>='a' && c<='f') {
            c -= 'a';
            c+=0x0A;
        }
        else if (c>='A' && c<='F') {
            c -= 'A';
            c+=0x0A;
        }
        else {
            return INCORRECT_DATA;
        }

        if ((i%2) == 0) {
            pOut[j] = c << 4;
        }
        else {
            pOut[j] |= c & 0x0f;
            j++;
        }
    }
    *pOutSize = j;
    return SUCCESS;
}

//-----------------------------------------------------------------------------
int bcd2str(const unsigned char* pIn, int size, unsigned char* pOut, int* pOutSize) 
{
    if (size <= 0 || pIn == NULL) return NULL_PARAMETER;
    char c, t;
    //string s = "";
    *pOutSize = 0;
    int i = 0;
    for (i = 0;i < size; ++i) {
        c = pIn[i] >> 4;
        if (c >= 0x00 && c <= 0x09) {
            c += '0';
        }
        else if (c>=0x0A && c <= 0x0F) {
            c += 'A' - 0x0a;
        }
        pOut[(*pOutSize)++] = c;

        c = pIn[i] & 0x0F;
        if (c >= 0x00 && c <= 0x09) {
            c += '0';
        }
        else if (c>=0x0A && c <= 0x0F) {
            c += 'A' - 0x0A;
        }
        pOut[(*pOutSize)++] = c;
    }
    return SUCCESS;
}

//-----------------------------------------------------------------------------

    int _debugBin(unsigned char* buffer, int len) 
    {
        int i = 0;
        for(i=0; i < len; ++i) {
            fprintf(stderr, "%02X ", buffer[i]);
            if ((i%16)==0 && i!=0) fprintf(stderr, "\n");
        }
        fprintf(stderr, "\n");
    }