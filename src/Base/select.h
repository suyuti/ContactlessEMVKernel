#ifndef _SELECT_H_
#define _SELECT_H_

int selectPpse();

int _buildSelect(const char* aid, int size, unsigned char* pBuffer, int* pSize);
int _buildSelectPpse(unsigned char* pBuffer, int* pSize);
int _resolveSelectPpse();

#endif// _SELECT_H_
