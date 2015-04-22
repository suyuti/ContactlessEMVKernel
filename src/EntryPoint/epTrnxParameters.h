#ifndef _EP_TRANSACTION_PARAMETERS_H_
#define _EP_TRANSACTION_PARAMETERS_H_

#include "../Hal/hal.h"

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

#endif// _EP_TRANSACTION_PARAMETERS_H_
