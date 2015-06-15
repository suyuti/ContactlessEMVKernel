/*
    Copyright 2015
*/

#ifndef SRC_HAL_HAL_H_
#define SRC_HAL_HAL_H_

#define CR_OPEN()
#define CR_CLOSE()
#define CR_SENDRECV(o, os, i, is)   0


typedef int (*card_open)(void);
typedef int (*card_reset)(void);
typedef int (*card_close)(void);
typedef int (*card_transmit)(const unsigned char*  pIn, 
                           int                   inSize, 
                           unsigned char*        pOut, 
                           unsigned long*        pOutSize);

typedef int (*genUnPredNum)(unsigned char* pOut, unsigned long* pOutSize);

#define GENERATE_UNPREDICT_NUMBER(p, n,l)  (p)->_genUnPredNum((n), (l))

typedef struct {
    card_open       _card_open;
    card_reset      _card_reset;
    card_close      _card_close;
    card_transmit   _card_transmit;
    genUnPredNum    _genUnPredNum;
} HalInterfaces, *HalInterfacesPtr;

typedef enum {
    RandomNumberGenerator,
    CardReaderOpen,
    CardReaderClose,
} HalInterfaceTypes;




#endif// SRC_HAL_HAL_H_
