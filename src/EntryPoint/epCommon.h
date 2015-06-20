#ifndef _EP_COMMON_H_
#define _EP_COMMON_H_

#include "../Hal/hal.h"
#include "epConfig.h"
    
typedef int (*fReadConfig)(const char* name, EpConfigPtr obj);


typedef struct {
    HalInterfaces   hal;
    EpConfigs       epConfigs;
    char            configFolder[120];

    fReadConfig     readConfigDelegate;
} Ep, *EpPtr;



#define SET_DELEGATE_READ_CONFIG(epPtr, foo)       (epPtr)->readConfigDelegate = foo


extern Ep gEp;





#endif// _EP_COMMON_H_
