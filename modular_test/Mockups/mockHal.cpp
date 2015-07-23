/*
 * MockHal.cpp
 * Copyright 2015 Suyuti  [legal/copyright]
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
    printf(">\n");
    for (int i = 0; i < p2; ++i) {
        printf("%02X ", p1[i]);
    }
    printf("\n");
    int r = MockHalFunctions::instance().cardTransmit(p1, p2, p3, p4);

    printf("<\n");
    for (int i = 0; i < *p4; ++i) {
        printf("%02X ", p3[i]);
    }
    printf("\n");
    return r;
}

//-------------------------------------------------------------------------
int mockFileOpen(const char* fileName, const char* mode)
{
    return MockHalFunctions::instance().fileOpen(fileName, mode);
}
//-------------------------------------------------------------------------
int mockFileClose(int file)
{
    return MockHalFunctions::instance().fileClose(file);
}
//-------------------------------------------------------------------------
int mockFileRead(int file, char* buffer, int size)
{
    return MockHalFunctions::instance().fileRead(file, buffer, size);
}
//-------------------------------------------------------------------------
int mockReadConfig(const char* configName, EpConfigPtr pConfig)
{
    return MockHalFunctions::instance().readConfig(configName, pConfig);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
