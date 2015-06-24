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

//-------------------------------------------------------------------
typedef enum {
    StartA,
    StartB,
    StartC,
    StartD,
    Start_NA
} OutcomeStartTypes;

typedef enum {
    Cvm_OnlinePin,
    Cvm_ConfirmationCodeVerified,
    Cvm_ObtainSignature,
    Cvm_NoCvm,
    Cvm_NA,
} CvmTypes;

typedef enum {
    Interface_ContactChip,
    Interface_MagStripe,
    Interface_NA
} InterfaceTypes;

#define MAX_DATA_LEN        256
typedef struct {
    OutcomeStartTypes   start;
    int                 onlineResponseDataLen;
    unsigned char       onlineResponseData[MAX_DATA_LEN];
    CvmTypes            cvm;
    int                 uiRequestOnOutcomePresent;
    int                 uiRequestOnRestartPresent;
    int                 dataRecordPresent;
    int                 discreationaryDataPresent;
    InterfaceTypes      alternateInterfacePreference;
    int                 receipt;
    int                 fieldOffRequest;
    int                 removalTimeout;
} EpOutcome, *EpOutcomePtr;



#define MAX_EP_CONFIG   200

typedef struct {
    HalInterfaces   hal;
    int             state;

    //- Config data
    int             epConfigsCount;
    EpConfig        epConfigs[MAX_EP_CONFIG];
    char            configFolder[120];

    //- Outcome
    EpOutcome       outcome;

    //- Started by reader
    int             startedByReader;
} Ep, *EpPtr;

extern Ep gEp; // define in entryPoint.c





#endif// _EP_COMMON_H_
