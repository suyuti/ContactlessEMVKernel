#include <string.h> // memset
#include "epConfig.h"
#include "../Base/err.h"

int resetEpConfig(EpConfigPtr p)
{
    if (!p) return INVALID_PARAMETER;
    memset(p, 0x00, sizeof(EpConfig));
    return SUCCESS;
}
