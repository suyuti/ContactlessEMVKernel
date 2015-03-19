/*
 * MockReader.h
 *
 *  Created on: Oct 22, 2014
 *      Author: suyuti
 */

#ifndef MOCKREADER_H_
#define MOCKREADER_H_

#include <gmock/gmock.h>
#include "./mockerC.h"


extern "C" {
    int reset_Mock(void);
    int sendrecv_Mock(const unsigned char*  pIn, 
                      int                   inSize, 
                      unsigned char*        pOut, 
                      unsigned long*        pOutSize);
    int close_Mock(void);
}

//---------------------------------------------------------------------

class MockReaderFunctions : public testing::MockerC<MockReaderFunctions> {
public:
    MOCK_CONST_METHOD0(reset,       int(void));
    MOCK_CONST_METHOD0(close,       int(void));
    MOCK_CONST_METHOD4(sendrecv,    int(const unsigned char*  pIn, 
                                        int                   inSize, 
                                        unsigned char*        pOut, 
                                        unsigned long*        pOutSize));
};

typedef ::testing::StrictMock<MockReaderFunctions> StrictMockReaderFunctions;
#endif /* MOCKREADER_H_ */
