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
    #include "../../modular_src/EntryPoint/epCommon.h"
}

extern "C" {
    // SmartCard IO
    int mockCardOpen(void);
    int mockCardReset(void);
    int mockCardTransmit(const unsigned char*  pIn, 
                        int                   inSize, 
                        unsigned char*        pOut, 
                        unsigned long*        pOutSize);
    int mockCardClose(void);

    //- File IO
    int mockFileOpen(const char* fileName, const char* mode);
    int mockFileClose(int file);
    int mockFileRead(int file, char* buffer, int size);

    //- config
    int mockReadConfig(const char* configName, EpConfigPtr pConfig);


}

//---------------------------------------------------------------------

class MockHalFunctions : public testing::MockerC<MockHalFunctions> {
public:
    //- SmartCard IO
    MOCK_CONST_METHOD0(cardOpen,        int(void));
    MOCK_CONST_METHOD0(cardReset,       int(void));
    MOCK_CONST_METHOD0(cardClose,       int(void));
    MOCK_CONST_METHOD4(cardTransmit,    int(const unsigned char*  pIn, 
                                        int                   inSize, 
                                        unsigned char*        pOut, 
                                        unsigned long*        pOutSize));
    //- File IO
    MOCK_CONST_METHOD2(fileOpen,        int(const char* fileName, const char* mode));
    MOCK_CONST_METHOD1(fileClose,       int(int file));
    MOCK_CONST_METHOD3(fileRead,        int(int file, char* buffer, int size));

    //- Config
    MOCK_CONST_METHOD2(readConfig,      int(const char*, EpConfigPtr));

};

typedef ::testing::StrictMock<MockHalFunctions> StrictMockHalFunctions;
#endif /* MOCKHAL_H_ */
