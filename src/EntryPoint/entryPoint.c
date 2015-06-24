/*
    Copyright 2015
*/
#include <stdlib.h>
#include <stdio.h>
#include "entryPoint.h"
#include "../Base/kernel.h"
#include "../Base/select.h"
#include "../Base/err.h"
#include "epPreProcessing.h"
#include "epProtocolActivation.h"
#include "../Hal/hal.h"

// TODO

Ep gEp;

int clearEntryPoint(EpPtr pEp)
{
    if (!pEp) return NULL_PARAMETER;

    clearEpConfigs(pEp);

    return SUCCESS;
}

int ep_init(HalInterfacesPtr pHal, const char* configFolder) 
{
    int err;

    SET_DELEGATE_CARD_OPEN      (&gEp.hal,  pHal->card_open     );
    SET_DELEGATE_CARD_RESET     (&gEp.hal,  pHal->card_reset    );
    SET_DELEGATE_CARD_CLOSE     (&gEp.hal,  pHal->card_close    );
    SET_DELEGATE_CARD_TRANSMIT  (&gEp.hal,  pHal->card_transmit );
    SET_DELEGATE_FILE_OPEN      (&gEp.hal,  pHal->fileOpen      );
    SET_DELEGATE_FILE_CLOSE     (&gEp.hal,  pHal->fileClose     );
    SET_DELEGATE_FILE_READ      (&gEp.hal,  pHal->fileRead      );
    SET_DELEGATE_GET_FILE_SIZE  (&gEp.hal,  pHal->getFileSize   );
    SET_DELEGATE_ALLOCATE       (&gEp.hal,  pHal->allocate      );
    SET_DELEGATE_RELEASE        (&gEp.hal,  pHal->release       );

    gEp.state = EP_START_STATE_A;

    sprintf(gEp.configFolder, "%s/config.txt", configFolder);
    err = loadConfigs(&gEp);
    if (err != SUCCESS) return err;

    return SUCCESS;
}

//--------------------------------------------------------------------

int ep_process(int amount, int amountAuthorized)
{
    int err = SUCCESS;
    for (;;) {
        switch(gEp.state) {
            case EP_START_STATE_A:
                err = _ep_startA(amount, amountAuthorized);
            break;
            case EP_START_STATE_B:
                err = _ep_startB();
            break;
            case EP_START_STATE_C:
                err = _ep_startC();
            break;
            case EP_START_STATE_D:
                err = _ep_startD();
            break;
            default:
                return err;
            break;
        }
        if (err != SUCCESS)
            break;
    }
    return err;
}

//--------------------------------------------------------------------
// Pre-processing

int _ep_startA(int amount, int amountAuthorized)
{
    int err = epPreProcessing(&gEp, amount, amountAuthorized);
    gEp.state = EP_START_STATE_B;
    return err;
}

//--------------------------------------------------------------------
// Protocol Activation

int _ep_startB()
{
    int err = epProtocolActivation();
    gEp.state = EP_START_STATE_C;
    return SUCCESS;
}

//--------------------------------------------------------------------
// Combination Selection

int _ep_startC()
{
    gEp.state = EP_START_STATE_D;
    return SUCCESS;
}

//--------------------------------------------------------------------
// Kernel Activation

int _ep_startD()
{
    gEp.state = EP_START_STATE_NONE;
    return SUCCESS;
}

//--------------------------------------------------------------------

int _outcomeProcessing(EpOutcomePtr pOutcome)
{
    /*
    if (pOutcome->outcomeType == SELECT_NEXT) {
        gEp.state = EP_START_STATE_C;
    }
    else if (pOutcome->outcomeType == TRY_AGAIN) {
        gEp.state = EP_START_STATE_B;
    }
    */
    return SUCCESS;
}

//--------------------------------------------------------------------

int _readConfigData()
{
    typedef enum {
        SALE = 0, 
        CASH, 
        CASHBACK, 
        REFUND
    } TransactionTypes;
    return SUCCESS;
}

//--------------------------------------------------------------------
// TODO for Testing purposes

int t_getEpState()
{
    return gEp.state;
}
