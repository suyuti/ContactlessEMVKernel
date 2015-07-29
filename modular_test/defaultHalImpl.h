/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_TEST_DEFAULTHALIMPL_H_
#define MODULAR_TEST_DEFAULTHALIMPL_H_

#include "Common/hal.h"

int defaultCard_open();
int defaultCard_reset();
int defaultCard_close();
int defaultCard_transmit(const unsigned char*  pIn,
                  int                   inSize,
                  unsigned char*        pOut,
                  unsigned long*        pOutSize);

int defaultGenUnPredNum(unsigned char* pOut,
                            unsigned long* pOutSize);

int defaultFileOpen(const char* fileName, const char* mode);
int defaultFileClose(int file);
int defaultGetFileSize(int file);
int defaultFileRead(int file, char* buffer, int size);
void* defaultAllocate(int size);
void defaultRelease(void* p);
int defaultRfOpen(void);
int defaultRfClose(void);
int defaultPoll(void);
int defaultDisplayMessage(const char* msg);
#endif  // MODULAR_TEST_DEFAULTHALIMPL_H_
