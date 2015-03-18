#ifndef _SCARD_READER_H_
#define _SCARD_READER_H_

int reset();
int sendrecv(const unsigned char* pIn, int inSize, unsigned char* pOut, unsigned long* pOutSize);
int close();

#endif// _SCARD_READER_H_
