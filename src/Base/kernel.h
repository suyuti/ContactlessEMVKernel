#ifndef SRC_BASE_KERNEL_H_
#define SRC_BASE_KERNEL_H_

#include "../Hal/hal.h"
#include "../EntryPoint/epCommon.h"

int initialize(const char* configFolder);
int release();
int start();
int getVersion();

int setCardOpen (_card_open f);
int setCardClose(_card_close f);
int setCardReset(_card_reset f);
int setCardTransmit(_card_transmit f);
int setFileOpen(_fileOpen fileOpen);
int setFileClose(_fileClose fileClose);
int setFileRead(_fileRead fileRead);
int setGetFileSize(_getFileSize getFileSize);

int setAllocate(_allocate allocate);
int setRelease(_release release);

extern HalInterfaces    gHal;

#endif// SRC_BASE_KERNEL_H_
