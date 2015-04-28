#ifndef _EP_CONFIG_H_
#define _EP_CONFIG_H_

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
    unsigned char   ttq[4];
    unsigned char   extendedSelectionSupport;
} EpConfig, *EpConfigPtr;


#endif// _EP_CONFIG_H_
