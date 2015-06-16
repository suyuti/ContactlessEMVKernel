/*
    Copyright 2015
*/

#ifndef SRC_BASE_UTILS_H_
#define SRC_BASE_UTILS_H_

#define MIN(a,b) ((a)<(b) ? (a) : (b))

int toInt(const unsigned char* ptag, int size);
int bcd2str(const unsigned char* pIn, int size, unsigned char* pOut, int* pOutSize);
int str2bcd(const unsigned char* str, int size, unsigned char* pOut, int* pOutSize);


#endif// SRC_BASE_UTILS_H_
