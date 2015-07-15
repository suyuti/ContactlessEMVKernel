/*
    Copyright 2015
*/

#ifndef MODULAR_SRC_ENTRYPOINT_ENTRYPOINT_H_
#define MODULAR_SRC_ENTRYPOINT_ENTRYPOINT_H_
#include "epCommon.h"
#include "epConfig.h"
#include "epIndicators.h"
#include "epOutcome.h"
#include "../Common/hal.h"

/**
* Functionality
* 1. PreProcessing
* 2. Protocol activation
* 3. Combination selection
* 4. Kernel activation
* 5. Outcome processing
*/


int clearEntryPoint(EpPtr pEp);

int ep_process(int amount, int amountAuthorized);
int ep_init(HalInterfacesPtr, const char* configFolder);


//--------------------------------------------------------------------
//  private



//--------------------------------------------------------------------
// Entry Point states. Should be private.
#define EP_START_STATE_A        1
#define EP_START_STATE_B        2
#define EP_START_STATE_C        3
#define EP_START_STATE_D        4
#define EP_START_STATE_NONE     5



//--------------------------------------------------------------------
int _ep_startA(int amount, int amountAuthorized);
int _ep_startB();
int _ep_startC();
int _ep_startD();
int _outcomeProcessing(EpOutcomePtr pOutcome);
int _readConfigData();
void setEpNextState(EpStates next);
int _kernelProcessing();


//--------------------------------------------------------------------
//  testing

int t_getEpState();


#endif  // MODULAR_SRC_ENTRYPOINT_ENTRYPOINT_H_
