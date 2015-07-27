#ifndef _AID_H_
#define _AID_H_

typedef enum {
    Visa = 0,
    Mastercard,
    AmericanExpress,
    // Interac,
    Discover,
    // UnionPay,
    // Jcb,
    Other,

    KernelRidTypesCount
} KernelRidTypes;

typedef enum {
    VisaDefaultKernelId             = 0x03,
    MastercardDefaultKernelId       = 0x02,
    AmericanExpressDefaultKernelId  = 0x04,
    // InteracDefaultKernelId,
    DiscoverDefaultKernelId         = 0x06,
    // UnionPayDefaultKernelId      = 0x07,
    // JcbDefaultKernelId           = 0x05,
    OtherDefaultKernelId            = 0x00,
} DefaulKernelIds;

typedef struct {
    unsigned char   rid[5];
    KernelRidTypes  type;
    DefaulKernelIds defaultKernelId;
} KernelRids, *KernelRidsPtr;

extern KernelRids gKernelRids[];

#endif// _AID_H_
