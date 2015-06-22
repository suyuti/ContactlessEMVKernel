#ifndef _EP_COMMON_H_
#define _EP_COMMON_H_

#include "../Hal/hal.h"

//--------------------------------------------------------------------
// Book A, Table 5-2
typedef struct {
    unsigned char   bitmap;
    unsigned char   statusCheck;
    unsigned char   zeroAmountAllowed;
    int             clessTrnxLimit;
    int             clessFloorLimit;
    int             termFloorLimit;
    int             cvmRequiredLimit;
    unsigned char   ttq[4];
    unsigned char   extendedSelectionSupport;
} EpConfigData, *EpConfigDataPtr;

// Book A, Table 5.3, Entry Point Pre-Processing Indicators
typedef struct {
    unsigned char   statusCheckRequested;
    unsigned char   clessAppNotAllowed;
    unsigned char   zeroAmount;
    unsigned char   readerCvmReqLimitExceeded;
    unsigned char   readerClessFloorLimitExceeded;
    unsigned char   ttq[4];
} EpIndicators, *EpIndicatorsPtr;

typedef struct {
    char            aid[20];
    unsigned char   kid;
    EpConfigData    configData;
    EpIndicators    indicators;
} EpConfig, *EpConfigPtr;

#define MAX_EP_CONFIG   200

typedef struct {
    HalInterfaces   hal;
    int             state;

    //- config data
    int             epConfigsCount;
    EpConfig        epConfigs[MAX_EP_CONFIG];

    char            configFolder[120];


} Ep, *EpPtr;

extern Ep gEp; // define in entryPoint.c





#endif// _EP_COMMON_H_
