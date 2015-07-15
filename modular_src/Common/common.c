#include "./common.h"
#include "./err.h"

HalInterfaces gHal;

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
