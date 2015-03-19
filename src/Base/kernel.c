#include <stdlib.h>
#include "./kernel.h"
#include "./err.h"

cr_open     gCrOpen     = NULL;
cr_close    gCrClose    = NULL;
cr_sendRecv gCrSendRecv = NULL;

int initialize()
{
    return 0;
}

int start()
{
    return 0;
}

int getVersion()
{
    return 0;
}

int setCrOpen(cr_open f)
{
    gCrOpen = f;
    return SUCCESS;
}

int setCrClose(cr_close f)
{
    gCrClose = f;
    return SUCCESS;
}

int setCrSendRecv(cr_sendRecv f)
{
    gCrSendRecv = f;
    return SUCCESS;
}
