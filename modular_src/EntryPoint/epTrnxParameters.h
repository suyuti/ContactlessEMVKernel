/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_SRC_ENTRYPOINT_EPTRNXPARAMETERS_H_
#define MODULAR_SRC_ENTRYPOINT_EPTRNXPARAMETERS_H_

#include "../Common/hal.h"

// Book A Table 5.6, Type of Transaction
typedef enum {
    Purchase                = 0x00,
    PurchaseWithCashBack    = 0x00,
    CashAdvance             = 0x01,
    Refund                  = 0x20
} TrnxTypes;

// Bok A Table 5.5, Transaction specific Data Elements
typedef struct {
    TrnxTypes       trnxType;
    int             amount;
    int             otherAmount;
    unsigned char   unpredictableNumber[4];
    int             trnxCurrencyCode;
} EpTrnxParams, *EpTrnxParamsPtr;

int resetEpTrnxParameters(EpTrnxParamsPtr p);
int updateEpTrnxParameters(EpTrnxParamsPtr p, HalInterfacesPtr pHal);

#endif// MODULAR_SRC_ENTRYPOINT_EPTRNXPARAMETERS_H_
