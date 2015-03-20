/*
 * MockReader.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: suyuti
 */

#include "./mockReader.h"

//-------------------------------------------------------------------------
/**
 * Free mock functions.
 *
 */

int reset_Mock(void)
{
    return MockReaderFunctions::instance().reset();
}

//-------------------------------------------------------------------------

int close_Mock(void)
{
    return MockReaderFunctions::instance().close();
}

//-------------------------------------------------------------------------

int sendrecv_Mock(const unsigned char*   p1,
                  int                    p2,
                  unsigned char*         p3,
                  unsigned long*         p4)
{
    return MockReaderFunctions::instance().sendRecv(p1, p2, p3, p4);
}
