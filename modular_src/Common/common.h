/*
    Copyright 2015
*/

#ifndef MODULAR_SRC_COMMON_COMMON_H_
#define MODULAR_SRC_COMMON_COMMON_H_

#include "./hal.h"

extern HalInterfaces gHal;


//------------------------------------------------------------------------------------
HalInterfacesPtr  getHal();

int setCardOpen(_card_open f);
int setCardReset(_card_reset f);
int setCardClose(_card_close f);
int setCardTransmit(_card_transmit f);
int setFileOpen(_fileOpen f);
int setFileClose(_fileClose f);
int setFileRead(_fileRead f);
int setGetFileSize(_getFileSize f);
int setAllocate(_allocate f);
int setRelease(_release f);
int setGenUnPredNum(genUnPredNum f);


#endif  // MODULAR_SRC_COMMON_COMMON_H_
