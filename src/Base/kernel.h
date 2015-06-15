#ifndef SRC_BASE_KERNEL_H_
#define SRC_BASE_KERNEL_H_

#include "../Hal/hal.h"

int initialize();
int release();
int start();
int getVersion();

int setCardOpen(card_open f);
int setCardClose(card_close f);
int setCardReset(card_reset f);
int setCardTransmit(card_transmit f);

extern card_open        gCardOpen;
extern card_close       gCardClose;
extern card_reset       gCardReset;
extern card_transmit    gCardTransmit;

#endif// SRC_BASE_KERNEL_H_
