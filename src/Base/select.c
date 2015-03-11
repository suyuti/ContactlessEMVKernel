/*
    Copyright 2015
*/

#include "./select.h"

#define PPSE        "2PAY.SYS.DDF01"


//-----------------------------------------------------------------------

int selectPPSE()
{
    return 0;
}

//-----------------------------------------------------------------------

int _buildSelect(const char* aid, int size, unsigned char* pBuffer, int* pSize)
{
    if (!pBuffer || !pSize || !aid || size==0) return -1;

    pBuffer[0] = 0x00;
    pBuffer[1] = 0xA4;
    pBuffer[2] = 0x04;
    pBuffer[3] = 0x00;
    pBuffer[4] = (unsigned char)size;
    memcpy(pBuffer+5, (unsigned char*)aid, size);
    *pSize = size + 5;

    return 0;
}

//-----------------------------------------------------------------------

int _buildSelectPpse(unsigned char* pBuffer, int* pSize)
{
    return _buildSelect(PPSE, sizeof(PPSE)-1, pBuffer, pSize);
}

//-----------------------------------------------------------------------

int _resolveSelectPpse()
{

}
