#ifndef _SELECT_H_
#define _SELECT_H_


typedef struct {
    unsigned char _4F  [1 + 16];
    unsigned char _50  [1 + 16];
    unsigned char _87  [1 + 1];
    unsigned char _9F2A[1 + 1];
    //unsigned char _9F29[];
} T61, *T61Ptr; 

typedef struct {
    int size;
    T61 _61[10];
} TBF0C, *TBF0CPtr;

typedef struct {
    int     size;
    TBF0C   _bf0c[10];
} TA5, *TA5Ptr;

typedef struct {
    unsigned char _84[1 + 16];
    TA5           _a5;    
} T6F, *T6FPtr;

int selectPpse();

int _buildSelect(const char* aid, int size, unsigned char* pBuffer, int* pSize);
int _buildSelectPpse(unsigned char* pBuffer, int* pSize);
int _resolveSelectPpse(const unsigned char* pData, int size, T6FPtr t6F);

#endif// _SELECT_H_
