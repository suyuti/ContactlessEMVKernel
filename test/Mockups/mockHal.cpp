/*
 * MockHal.cpp
 *
 *  Created on: 15.06.2015
 *      Author: suyuti
 */

#include "./mockHal.h"

//-------------------------------------------------------------------------
/**
 * Free mock functions.
 *
 */

int mockCardOpen(void)
{
    return MockHalFunctions::instance().cardOpen();
}

int mockCardReset(void)
{
    return MockHalFunctions::instance().cardReset();
}

//-------------------------------------------------------------------------

int mockCardClose(void)
{
    return MockHalFunctions::instance().cardClose();
}

//-------------------------------------------------------------------------

int mockCardTransmit(const unsigned char*   p1,
                  int                    p2,
                  unsigned char*         p3,
                  unsigned long*         p4)
{
    return MockHalFunctions::instance().cardTransmit(p1, p2, p3, p4);
}
