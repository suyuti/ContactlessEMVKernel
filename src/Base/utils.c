/*
    Copyright 2015
*/

#include "./utils.h"

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
