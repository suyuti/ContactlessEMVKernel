/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#include <string.h>

#include "epIndicators.h"

void epIndicators_reset(EpIndicatorsPtr epI)
{
    memset(epI, 0x00, sizeof(EpIndicators));
}
