/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#include <string.h>
#include "./epOutcome.h"
#include "../Common/general.h"
#include "../Common/err.h"

int resetOutcome(EpOutcomePtr p)
{
    memset(p, 0x00, sizeof(EpOutcome));

    p->start                        = Start_NA;
    p->cvm                          = Cvm_NA;
    p->alternateInterfacePreference = Interface_NA;
    return SUCCESS;
}

//-----------------------------------------------------------------------------

EpOutcomePtr withStartType(EpOutcomePtr p, OutcomeStartTypes t)
{
    p->start = t;
    return p;
}

//-----------------------------------------------------------------------------

EpOutcomePtr withOnlineResponseData(EpOutcomePtr p, unsigned char* data, int len)
{
    if (len < MAX_DATA_LEN) {
        memcpy(p->onlineResponseData, data, len);
        p->onlineResponseDataLen = len;
    }
    return p;
}

//-----------------------------------------------------------------------------

EpOutcomePtr withCvm(EpOutcomePtr p, CvmTypes t)
{
    p->cvm = t;
    return p;
}

//-----------------------------------------------------------------------------

EpOutcomePtr withUiRequestOnOutcomePresent(EpOutcomePtr p)
{
    p->uiRequestOnOutcomePresent = SET;
    return p;
}

//-----------------------------------------------------------------------------

EpOutcomePtr withUiRequestOnRestartPresent(EpOutcomePtr p)
{
    p->uiRequestOnRestartPresent = SET;
    return p;
}

//-----------------------------------------------------------------------------

EpOutcomePtr withDataRecordPresent(EpOutcomePtr p)
{
    p->dataRecordPresent = SET;
    return p;
}

//-----------------------------------------------------------------------------

EpOutcomePtr withDiscreationaryDataPresent(EpOutcomePtr p)
{
    p->discreationaryDataPresent = SET;
    return p;
}

//-----------------------------------------------------------------------------

EpOutcomePtr withAlternateInterface(EpOutcomePtr p, InterfaceTypes t)
{
    p->alternateInterfacePreference = t;
    return p;
}

//-----------------------------------------------------------------------------

EpOutcomePtr withReceipt(EpOutcomePtr p)
{
    p->receipt = SET;
    return p;
}
//-----------------------------------------------------------------------------
EpOutcomePtr withFieldOff(EpOutcomePtr p)
{
    p->fieldOffRequest = SET;
    return p;
}
//-----------------------------------------------------------------------------
EpOutcomePtr withRemovalTimeout(EpOutcomePtr p, int t)
{
    p->removalTimeout = t;
    return p;
}
