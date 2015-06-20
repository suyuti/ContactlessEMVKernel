#ifndef _DEFAULT_HAL_IMPL_H_
#define _DEFAULT_HAL_IMPL_H_

#include "../src/Hal/hal.h"


int defaultFileOpen(const char* fileName, const char* mode);
int defaultFileClose(int file);
int defaultGetFileSize(int file);
int defaultFileRead(int file, char* buffer, int size);
void* defaultAllocate(int size);
int defaultRelease(void* p);


#endif// _DEFAULT_HAL_IMPL_H_
