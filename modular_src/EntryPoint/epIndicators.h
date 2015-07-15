#ifndef _EPINDICATORS_H_
#define _EPINDICATORS_H_

#include "epCommon.h"

void epIndicators_reset(EpIndicatorsPtr epI);



#define SET_EPIND_STATUS_CHECK_REQ(ep)                      ((ep).statusCheckRequested          = 0x01)
#define SET_EPIND_CLESS_APP_NOT_ALLOWED(ep)                 ((ep).clessAppNotAllowed            = 0x01)
#define SET_EPIND_ZERO_AMOUNT(ep)                           ((ep).zeroAmount                    = 0x01)
#define SET_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(ep)         ((ep).readerCvmReqLimitExceeded     = 0x01)
#define SET_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(ep)     ((ep).readerClessFloorLimitExceeded = 0x01)

#define RESET_EPIND_STATUS_CHECK_REQ(ep)                    ((ep).statusCheckRequested          = 0x00)
#define RESET_EPIND_CLESS_APP_NOT_ALLOWED(ep)               ((ep).clessAppNotAllowed            = 0x00)
#define RESET_EPIND_ZERO_AMOUNT(ep)                         ((ep).zeroAmount                    = 0x00)
#define RESET_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(ep)       ((ep).readerCvmReqLimitExceeded     = 0x00)
#define RESET_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(ep)   ((ep).readerClessFloorLimitExceeded = 0x00)

#define IS_EPIND_STATUS_CHECK_REQ(ep)                       ((ep).statusCheckRequested          != 0x00)
#define IS_EPIND_CLESS_APP_NOT_ALLOWED(ep)                  ((ep).clessAppNotAllowed            != 0x00)
#define IS_EPIND_ZERO_AMOUNT(ep)                            ((ep).zeroAmount                    != 0x00)
#define IS_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(ep)          ((ep).readerCvmReqLimitExceeded     != 0x00)
#define IS_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(ep)      ((ep).readerClessFloorLimitExceeded != 0x00)


#endif// _EPINDICATORS_H_
