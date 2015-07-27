#ifndef _KERNEL_IDENTIFIER_H_
#define _KERNEL_IDENTIFIER_H_

typedef unsigned char KernelIdentifier[8];

#define Kid_InternationalKernel(kid)                RESET_BIT((kid)[0], 8); RESET_BIT((kid)[0], 7);
#define Kid_DomesticKernel_EmvCoFormat(kid)           SET_BIT((kid)[0], 8); RESET_BIT((kid)[0], 7);
#define Kid_DomesticKernel_propFormat(kid)            SET_BIT((kid)[0], 8);   SET_BIT((kid)[0], 7);

#define Kid_Reset(kid)                              memset((kid), 0x00, sizeof(KernelIdentifier))

#endif// _KERNEL_IDENTIFIER_H_
