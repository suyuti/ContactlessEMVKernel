#ifndef _ENTRY_POINT_H_
#define _ENTRY_POINT_H_

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

int ep_process();


//--------------------------------------------------------------------
int _ep_startA(int amount, int otherAmount);
int _ep_startB();
int _ep_startC();

#endif// _ENTRY_POINT_H_
