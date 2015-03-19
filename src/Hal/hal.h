/*
    Copyright 2015
*/

#ifndef SRC_HAL_HAL_H_
#define SRC_HAL_HAL_H_

#define CR_OPEN()
#define CR_CLOSE()
#define CR_SENDRECV(o, os, i, is)   0


int cr_open();
int cr_close();
int cr_sendRecv();

#endif// SRC_HAL_HAL_H_
