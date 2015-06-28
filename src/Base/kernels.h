#ifndef _KERNELS_H_
#define _KERNELS_H_

/*
    Book B v2.5 p.28
    Table 3.6
    
*/
typedef enum {
    DefultKernel_AmericanExpress = 0x04; // 00000100b
    DefultKernel_Discover        = 0x06; // 00000110b
    DefultKernel_JCB             = 0x05; // 00000101b
    DefultKernel_MasterCard      = 0x02; // 00000010b
    DefultKernel_UnionPay        = 0x07; // 00000111b
    DefultKernel_Visa            = 0x03; // 00000011b
    DefultKernel_Other           = 0x00; // 00000000b
} DefaultKernels;

#endif// _KERNELS_H_
