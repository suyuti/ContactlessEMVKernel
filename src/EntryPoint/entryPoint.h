/*
    Copyright 2015
*/

#ifndef SRC_ENTRYPOINT_ENTRYPOINT_H_
#define SRC_ENTRYPOINT_ENTRYPOINT_H_
#include "epCommon.h"
#include "epConfig.h"
#include "epIndicators.h"
#include "epOutcome.h"
#include "../Hal/hal.h"

/**
* Functionality
* 1. PreProcessing
* 2. Protocol activation
* 3. Combination selection
* 4. Kernel activation
* 5. Outcome processing
*/



int ep_process();
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
int _ep_startA(/*int amount, int otherAmount*/);
int _ep_startB();
int _ep_startC();
int _ep_startD();
int _outcomeProcessing(EpOutcomePtr pOutcome);
int _readConfigData();



//--------------------------------------------------------------------
//  testing

int t_getEpState();


#endif// SRC_ENTRYPOINT_ENTRYPOINT_H_
