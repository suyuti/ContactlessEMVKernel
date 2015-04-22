#include "l2.h"

#include "../Base/err.h"

static HalInterfaces gHal;

int setHalInteface(HalInterfaceTypes t, void* fp)
{
    injectInterface(&gHal, t, fp);        
}

int init(void)
{

    return SUCCESS;
}

