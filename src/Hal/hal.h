/*
    Copyright 2015
*/

#ifndef SRC_HAL_HAL_H_
#define SRC_HAL_HAL_H_

#define CR_OPEN()
#define CR_CLOSE()
#define CR_SENDRECV(o, os, i, is)   0


typedef int (*cr_open)(void);
typedef int (*cr_close)(void);
typedef int (*cr_sendRecv)(const unsigned char*  pIn, 
                           int                   inSize, 
                           unsigned char*        pOut, 
                           unsigned long*        pOutSize);

#endif// SRC_HAL_HAL_H_
