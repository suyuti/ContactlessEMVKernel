#ifndef _EP_COMMON_H_
#define _EP_COMMON_H_

#include "../Hal/hal.h"
#include "epConfig.h"

typedef struct {
    HalInterfaces   hal;
    EpConfigs       epConfigs;
    char            configFolder[120];
} Ep, *EpPtr;

extern Ep gEp; // define in entryPoint.c





#endif// _EP_COMMON_H_
