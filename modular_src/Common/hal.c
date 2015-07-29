/*
    Copyright 2015
*/

#include "./err.h"
#include "./hal.h"
#include "hal.h"

static HalInterfaces gHal;

int card_open()
{
    gHal.card_open();
    return SUCCESS;
}

int card_transmit(const unsigned char* pIn, int inSize, unsigned char* pOut, unsigned long* pOutSize)
{
    return gHal.card_transmit(pIn, inSize, pOut, pOutSize);
}

int fileOpen(const char* fileName, const char* mode)
{
    return gHal.fileOpen(fileName, mode);
}
int fileClose(int file)
{
    return gHal.fileClose(file);
}
int getFileSize(int file)
{
    return gHal.getFileSize(file);
}
int fileRead(int file, char* buffer, int size)
{
    return gHal.fileRead(file, buffer, size);
}
void* allocate(int size)
{
    return gHal.allocate(size);
}
void release(void* p)
{
    gHal.release(p);
}

int displayMessage(const char* msg)
{
    return gHal.displayMessage(msg);
}

int rf_open(void)
{
    return gHal.rfOpen();
}

int rf_close(void)
{
    return gHal.rfClose();
}

int poll(_on_card_detected hadler)
{
    return gHal.poll(hadler);
}







int setCardOpen(_card_open f)
{
    SET_DELEGATE_CARD_OPEN(&gHal, f);
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setCardReset(_card_reset f)
{
    SET_DELEGATE_CARD_RESET(&gHal, f);
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setCardClose(_card_close f)
{
    SET_DELEGATE_CARD_CLOSE(&gHal, f);
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setCardTransmit(_card_transmit f)
{
    SET_DELEGATE_CARD_TRANSMIT(&gHal, f);
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setFileOpen(_fileOpen f)
{
    SET_DELEGATE_FILE_OPEN(&gHal, f);
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setFileClose(_fileClose f)
{
    SET_DELEGATE_FILE_CLOSE(&gHal, f);
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setFileRead(_fileRead f)
{
    SET_DELEGATE_FILE_READ(&gHal, f);
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setGetFileSize(_getFileSize f)
{
    SET_DELEGATE_GET_FILE_SIZE(&gHal, f);
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setAllocate(_allocate f)
{
    SET_DELEGATE_ALLOCATE(&gHal, f);
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setRelease(_release f)
{
    SET_DELEGATE_RELEASE(&gHal, f);
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setGenUnPredNum(genUnPredNum f)
{
    SET_DELEGATE_GENUNPREDNUM(&gHal, f);
    return SUCCESS;
}

int setPoll(_poll f)
{
    gHal.poll = f;
    return SUCCESS;
}

int setRfOpen(_rf_open f)
{
    gHal.rfOpen = f;
    return SUCCESS;
}

int setRfClose(_rf_close f)
{
    gHal.rfClose = f;
    return SUCCESS;
}

int setDisplayMessage(_displayMessage f)
{
    gHal.displayMessage = f;
    return SUCCESS;
}


//------------------------------------------------------------------------------------

int checkHalInterfaces(void)
{
    if (!gHal.card_open     ||
        !gHal.card_reset    ||
        !gHal.card_close    ||
        !gHal.card_transmit ||
        !gHal.fileOpen      ||
        !gHal.fileClose     ||
        !gHal.fileRead      ||
        !gHal.getFileSize   ||
        !gHal.allocate      ||
        !gHal.release       ||
        !gHal._genUnPredNum
            )
        return HAL_INTERFACE_IS_NULL;
    return SUCCESS;
}

