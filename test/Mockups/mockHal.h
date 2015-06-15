/*
 * MockHal.h
 *
 *  Created on: 15.06.2015
 *      Author: suyuti
 */

#ifndef MOCKHAL_H_
#define MOCKHAL_H_

#include <gmock/gmock.h>
#include "./mockerC.h"


extern "C" {
    // Card functions
    int mockCardOpen(void);
    int mockCardReset(void);
    int mockCardTransmit(const unsigned char*  pIn, 
                        int                   inSize, 
                        unsigned char*        pOut, 
                        unsigned long*        pOutSize);
    int mockCardClose(void);
}

//---------------------------------------------------------------------

class MockHalFunctions : public testing::MockerC<MockHalFunctions> {
public:
    MOCK_CONST_METHOD0(cardOpen,        int(void));
    MOCK_CONST_METHOD0(cardReset,       int(void));
    MOCK_CONST_METHOD0(cardClose,       int(void));
    MOCK_CONST_METHOD4(cardTransmit,    int(const unsigned char*  pIn, 
                                        int                   inSize, 
                                        unsigned char*        pOut, 
                                        unsigned long*        pOutSize));
};

typedef ::testing::StrictMock<MockHalFunctions> StrictMockHalFunctions;
#endif /* MOCKHAL_H_ */
