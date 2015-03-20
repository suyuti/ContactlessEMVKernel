/*
    Copyright 2015
*/

#include "entryPoint.h"
#include "../Base/kernel.h"
#include "../Base/select.h"

int ep_process()
{

    Fci f;
    gCrOpen();

    selectPpse(&f);
    return 0;
}

//--------------------------------------------------------------------

int _ep_startA(int amount, int otherAmount)
{
    return 0;
}
