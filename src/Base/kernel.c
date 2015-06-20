#include <stdlib.h>
#include "./kernel.h"
#include "./err.h"

HalInterfaces gHal;

//------------------------------------------------------------------------------------

int initialize(const char *configFolder)
{
    // 1. Set terminal parameters
    int retVal = 0;

    retVal = ep_init(&gHal, configFolder);
    retVal = ep_process();

/*    
    gCardOpen();
    gCardReset();
    unsigned char cmd[] = {0x00, 0xA4, 0x04, 0x00,
                                    0x0E,
                                    '2', 'P', 'A', 'Y', '.', 'S', 'Y', 'S', '.', 'D', 'D', 'F', '0', '1', };
    unsigned char resp[1000] = {0x00};
    unsigned long len = 0;
    gCardTransmit(cmd, sizeof(cmd), resp, &len);


    unsigned char cmd2[] = {0x00, 0xA4, 0x04, 0x00, 0x07, 0xA0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01};
    gCardTransmit(cmd2, sizeof(cmd2), resp, &len);

    unsigned char cmd3[] = {0x80, 0xA8, 0x00, 0x00, 0x21, 0x83, 0x1F, 0x01, 
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                            0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
                            0x00, 0x00, 0x30, 0x32, 0x64, 0x49, 0x00, 0x00, 
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    gCardTransmit(cmd3, sizeof(cmd3), resp, &len);
    //gCardTransmit(cmd2, sizeof(cmd2), resp, &len);
    // 2. Set HAL interfaces
    */
    return 0;
}

//------------------------------------------------------------------------------------

int release()
{
    return 0;
}

//------------------------------------------------------------------------------------

int start()
{
    return 0;
}

//------------------------------------------------------------------------------------

int getVersion()
{
    return 99;
}

//------------------------------------------------------------------------------------

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

int setReadConfig(fReadConfig readConfig)
{
    SET_DELEGATE_READ_CONFIG(&gEp, readConfig);    
    return SUCCESS;
}

int setFileOpen(_fileOpen f)
{
    SET_DELEGATE_FILE_OPEN(&gHal, f);
    return SUCCESS;
}

int setFileClose(_fileClose f)
{
    SET_DELEGATE_FILE_CLOSE(&gHal, f);
    return SUCCESS;
}

int setFileRead(_fileRead f)
{
    SET_DELEGATE_FILE_READ(&gHal, f);
    return SUCCESS;
}

int setGetFileSize(_getFileSize f)
{
    SET_DELEGATE_GET_FILE_SIZE(&gHal, f);
    return SUCCESS;
}

int setAllocate(_allocate f)
{
    SET_DELEGATE_ALLOCATE(&gHal, f);
    return SUCCESS;
}

int setRelease(_release f)
{
    SET_DELEGATE_RELEASE(&gHal, f);
    return SUCCESS;
}
