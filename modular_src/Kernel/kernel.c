/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#include "./kernel.h"
#include "../Common/hal.h"
#include "../Common/err.h"
#include "../EntryPoint/entryPoint.h"

int initialize(const char* path)
{
    int err = 0;
    if (!path) return NULL_PARAMETER;

    err = checkHalInterfaces();
    if (err != SUCCESS) return err;

    err = ep_init(path);
    if (err != SUCCESS) return err;

    return err;
}

int execute(int amount, int amountOther)
{
    int err = ep_process(amount, amountOther);
    return SUCCESS;
}
