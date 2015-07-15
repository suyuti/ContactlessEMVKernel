/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#include <string.h>
#include "epTrnxParameters.h"
#include "../Common/err.h"
#include "../Common/hal.h"
//--------------------------------------------------------------------

int resetEpTrnxParameters(EpTrnxParamsPtr p)
{
    if (!p) return INVALID_PARAMETER;
    memset(p, 0x00, sizeof(EpTrnxParams));
    return SUCCESS;
}

//--------------------------------------------------------------------

int updateEpTrnxParameters(EpTrnxParamsPtr p, HalInterfacesPtr pHal)
{
    if (!p || !pHal) return INVALID_PARAMETER;

    resetEpTrnxParameters(p);

    unsigned char unprdctnmbr[32];
    unsigned long size = sizeof(p->unpredictableNumber);

    GENERATE_UNPREDICT_NUMBER(pHal, unprdctnmbr, &size);
    if (size != sizeof(p->unpredictableNumber)) {
        return INCORRECT_DATA;
    }
    memset(p->unpredictableNumber, 0x00, sizeof(p->unpredictableNumber));
    memcpy(p->unpredictableNumber, unprdctnmbr, size);

    return SUCCESS;
}
