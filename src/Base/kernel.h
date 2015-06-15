#ifndef SRC_BASE_KERNEL_H_
#define SRC_BASE_KERNEL_H_

#include "../Hal/hal.h"

int initialize();
int release();
int start();
int getVersion();

int setCrOpen(void* /*cr_open*/ f);
int setCrClose(cr_close f);
int setCrSendRecv(cr_sendRecv f);

extern cr_open     gCrOpen;
extern cr_close    gCrClose;
extern cr_sendRecv gCrSendRecv;

#endif// SRC_BASE_KERNEL_H_
