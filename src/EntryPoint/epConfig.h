#ifndef _EP_CONFIG_H_
#define _EP_CONFIG_H_

#include "../Base/general.h"
//--------------------------------------------------------------------
// Book A, Table 5-2

typedef struct {
    unsigned char   bitmap;
    unsigned char   statusCheck;
    unsigned char   zeroAmountAllowed;
    int             clessTrnxLimit;
    int             clessFloorLimit;
    int             termFloorLimit;
    int             cvmRequiredLimit;
    unsigned char   ttq[4];
    unsigned char   extendedSelectionSupport;
} EpConfig, *EpConfigPtr;

int resetEpConfig(EpConfigPtr p);

#define IS_EXIST_STATUS_CHECK(p)                ((p).bitmap && 0x01)        
#define IS_EXIST_ZERO_AMOUNT_ALLOWED(p)         ((p).bitmap && 0x02)
#define IS_EXIST_CLESS_TRNX_LIMIT(p)            ((p).bitmap && 0x04)
#define IS_EXIST_CLESS_FLOOR_LIMIT(p)           ((p).bitmap && 0x08)
#define IS_EXIST_TERM_FLOOR_LIMIT(p)            ((p).bitmap && 0x10)
#define IS_EXIST_CVM_REQ_LIMIT(p)               ((p).bitmap && 0x20)
#define IS_EXIST_TTQ(p)                         ((p).bitmap && 0x40)
#define IS_EXIST_EXTENDED_SELECTION_SUPP(p)     ((p).bitmap && 0x80)

#define SET_EXIST_STATUS_CHECK(p)               ((p).bitmap |= 0x01)        
#define SET_EXIST_ZERO_AMOUNT_ALLOWED(p)        ((p).bitmap |= 0x02)
#define SET_EXIST_CLESS_TRNX_LIMIT(p)           ((p).bitmap |= 0x04)
#define SET_EXIST_CLESS_FLOOR_LIMIT(p)          ((p).bitmap |= 0x08)
#define SET_EXIST_TERM_FLOOR_LIMIT(p)           ((p).bitmap |= 0x10)
#define SET_EXIST_CVM_REQ_LIMIT(p)              ((p).bitmap |= 0x20)
#define SET_EXIST_TTQ(p)                        ((p).bitmap |= 0x40)
#define SET_EXIST_EXTENDED_SELECTION_SUPP(p)    ((p).bitmap |= 0x80)


#define SET_STATUS_CHECK(p)                     (p).statusCheck                 = SET; SET_EXIST_STATUS_CHECK(p)
#define SET_ZERO_AMOUT_ALLOWED(p)               (p).zeroAmountAllowed           = SET; SET_EXIST_ZERO_AMOUNT_ALLOWED(p)
#define SET_EXTENDED_SELECTION_SUPP(p)          (p).extendedSelectionSupport    = SET; SET_EXIST_EXTENDED_SELECTION_SUPP(p)

#define RESET_STATUS_CHECK(p)                   (p).statusCheck                 = RESET; SET_EXIST_STATUS_CHECK(p)
#define RESET_ZERO_AMOUT_ALLOWED(p)             (p).zeroAmountAllowed           = RESET; SET_EXIST_ZERO_AMOUNT_ALLOWED(p)
#define RESET_EXTENDED_SELECTION_SUPP(p)        (p).extendedSelectionSupport    = RESET; SET_EXIST_EXTENDED_SELECTION_SUPP(p)

#define IS_STATUS_CHECK(p)                      ((p).statusCheck                == SET)
#define IS_ZERO_AMOUT_ALLOWED(p)                ((p).zeroAmountAllowed          == SET)
#define IS_EXTENDED_SELECTION_SUPP(p)           ((p).extendedSelectionSupport   == SET)

#endif// _EP_CONFIG_H_
