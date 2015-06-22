#include "defaultHalImpl.h"
#include "Base/err.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

int defaultCard_open() {return SUCCESS;};
int defaultCard_reset() {return SUCCESS;};
int defaultCard_close() {return SUCCESS;};
int defaultCard_transmit(const unsigned char*  pIn, 
                  int                   inSize, 
                  unsigned char*        pOut, 
                  unsigned long*        pOutSize) {
    return SUCCESS;
}

int defaultGenUnPredNum(unsigned char* pOut, 
                            unsigned long* pOutSize)
{ return SUCCESS;}


int defaultFileOpen(const char* fileName, const char* mode)
{
    return open (fileName, O_RDONLY);
}
int defaultFileClose(int file)
{
    close(file);
    return 0;
}
int defaultGetFileSize(int file)
{
    struct stat buf;
    fstat(file, &buf);
    return buf.st_size;
}
int defaultFileRead(int file, char* buffer, int size)
{
    return read(file, buffer, size);
}
void* defaultAllocate(int size)
{
    return malloc(size);
}
int defaultRelease(void* p)
{
    free(p);
}
