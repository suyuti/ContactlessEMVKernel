/*
    Copyright 2015
*/

#include "entryPoint.h"
#include "../Base/kernel.h"
#include "../Base/select.h"
#include "../Base/err.h"
#include "epPreProcessing.h"

// TODO

static int gEpState;

int ep_init() 
{
    gEpState = EP_START_STATE_A;
    return SUCCESS;
}

//--------------------------------------------------------------------

int ep_process()
{
    int err = SUCCESS;
    for (;;) {
        switch(gEpState) {
            case EP_START_STATE_A:
                err = epPreProcessing();
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
    }
    return err;
}

//--------------------------------------------------------------------
// Pre-processing

int _ep_startA(/*int amount, int otherAmount*/)
{
    gEpState = EP_START_STATE_B;
    return SUCCESS;
}

//--------------------------------------------------------------------
// Protocol Activation

int _ep_startB()
{
    gEpState = EP_START_STATE_C;
    return SUCCESS;
}

//--------------------------------------------------------------------
// Combination Selection

int _ep_startC()
{
    gEpState = EP_START_STATE_D;
    return SUCCESS;
}

//--------------------------------------------------------------------
// Kernel Activation

int _ep_startD()
{
    gEpState = EP_START_STATE_NONE;
    return SUCCESS;
}

//--------------------------------------------------------------------

int _outcomeProcessing(EpOutcomePtr pOutcome)
{
    if (pOutcome->outcomeType == SELECT_NEXT) {
        gEpState = EP_START_STATE_C;
    }
    else if (pOutcome->outcomeType == TRY_AGAIN) {
        gEpState = EP_START_STATE_B;
    }
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
    return gEpState;
}
