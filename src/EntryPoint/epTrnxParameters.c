#include <string.h>
#include "epTrnxParameters.h"
#include "../Base/err.h"
#include "../Hal/hal.h"
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
    long size = sizeof(p->unpredictableNumber);

    GENERATE_UNPREDICT_NUMBER(pHal, unprdctnmbr, &size);
    if (size != sizeof(p->unpredictableNumber)) {
        return INCORRECT_DATA;
    }
    memset(p->unpredictableNumber, 0x00, sizeof(p->unpredictableNumber));
    memcpy(p->unpredictableNumber, unprdctnmbr, size);

    return SUCCESS;
}
