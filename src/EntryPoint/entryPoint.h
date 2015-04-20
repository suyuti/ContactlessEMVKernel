/*
    Copyright 2015
*/

#ifndef SRC_ENTRYPOINT_ENTRYPOINT_H_
#define SRC_ENTRYPOINT_ENTRYPOINT_H_

/**
* Functionality
* 1. PreProcessing
* 2. Protocol activation
* 3. Combination selection
* 4. Kernel activation
* 5. Outcome processing
*/

//--------------------------------------------------------------------
// Book A, Table 5-2

typedef struct {
    unsigned char   statusCheck;
    unsigned char   zeroAmountAllowed;
    int             clessTrnxLimit;
    int             clessFloorLimit;
    int             termFloorLimit;
    int             cvmRequiredLimit;
    // Terminal Transaction Qualifiers
    unsigned char   extendedSelectionSupport;
} EpConfig, *EpConfigPtr;



typedef struct {
    int outcomeType;
} EpOutcome, *EpOutcomePtr;

int ep_process();
int ep_init();


//--------------------------------------------------------------------
//  private

//--------------------------------------------------------------------
// Outcome types
#define SELECT_NEXT                 1
#define TRY_AGAIN                   2
#define APPROVED                    3
#define DECLINED                    4
#define ONLINE_REQUEST              5
#define TRY_ANOTHER_INTERFACE       6
#define END_APPLICATION             7


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
