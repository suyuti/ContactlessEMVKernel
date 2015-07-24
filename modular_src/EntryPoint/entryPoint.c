/*
    Copyright 2015
*/

#include <stdlib.h>
#include <stdio.h>
#include "entryPoint.h"
// #include "../Base/kernel.h"
#include "../Emv/select.h"
#include "../Common/err.h"
#include "epPreProcessing.h"
#include "epProtocolActivation.h"
#include "../Common/hal.h"
#include "./epConfig.h"
#include "./epCombinationSelection.h"
#include "epCommon.h"

// TODO

Ep gEp;

//--------------------------------------------------------------------
/**
 *
 * Clears EntryPoint object
 *
 * */

int clearEntryPoint(EpPtr pEp)
{
    if (!pEp) return NULL_PARAMETER;

    clearEpConfigs(pEp);
    pEp->candidateListCount = 0;
    clearCandidateList(pEp->candidateList, MAX_CANDIDATE_LIST);

    return SUCCESS;
}

//--------------------------------------------------------------------
/**
 *
 * Initialize EntryPoint object.
 * Clears it and loads entry point configuration from related folder.
 * This folder is given in configFolder parameter.
 * Entry point configuration data stored on config.txt file.
 *
 * */
int ep_init(const char* configFolder)
{
    int err;

    err = clearEntryPoint(&gEp);
    if (err != SUCCESS) return err;

    setEpNextState(EpStateStartA);

    sprintf(gEp.configFolder, "%s/config.txt", configFolder);
    err = loadConfigs(&gEp);
    if (err < 0) return err;
    if (err == 0) return NO_CONFIG;

    return SUCCESS;
}

//--------------------------------------------------------------------

int ep_process(int amount, int amountAuthorized)
{
    int err = SUCCESS;

    for (;;) {
        switch(gEp.state) {
            case EpStateStartA:
                err = _ep_startA(amount, amountAuthorized);
            break;
            case EpStateStartB:
                err = _ep_startB();
            break;
            case EpStateStartC:
                err = _ep_startC();
            break;
            case EpStateStartD:
                err = _ep_startD();
            break;
            case EpStateKernelProcessing:
                err = _kernelProcessing();
            break;
            case EpStateOutcomeProcessing:
                err = _outcomeProcessing(&(gEp.outcome));
            break;
            case EpStateFinalOutcomeProcessing:
                goto EXIT;
            break;
            default:
                return err;
            break;
        }
        if (err != SUCCESS)
            break;
    }
EXIT:
    return err;
}

//--------------------------------------------------------------------
// Pre-processing

int _ep_startA(int amount, int amountAuthorized)
{
    int err = epPreProcessing(&gEp, amount, amountAuthorized);
    setEpNextState(EpStateStartB);
    return err;
}

//--------------------------------------------------------------------
// Protocol Activation

int _ep_startB()
{
    int err = epProtocolActivation(&gEp);
    setEpNextState(EpStateStartC);
    return SUCCESS;
}

//--------------------------------------------------------------------
// Combination Selection

int _ep_startC()
{
    int err = epCombinationSelection(&gEp);
    // TODO
    err = epFinalCombinationSelection(&gEp);
    setEpNextState(EpStateStartD);
    return SUCCESS;
}

//--------------------------------------------------------------------
// Kernel Activation

int _ep_startD()
{
    setEpNextState(EpStateKernelProcessing);
    return SUCCESS;
}

//--------------------------------------------------------------------

int _kernelProcessing()
{
    setEpNextState(EpStateOutcomeProcessing);
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
    setEpNextState(EpStateFinalOutcomeProcessing);
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

void setEpNextState(EpStates next)
{
    gEp.state = next;
}

//--------------------------------------------------------------------
// TODO for Testing purposes

int t_getEpState()
{
    return gEp.state;
}
