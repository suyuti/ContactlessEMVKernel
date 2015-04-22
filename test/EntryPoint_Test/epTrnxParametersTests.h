/*
    Copyright 2015
*/

#ifndef TEST_ENTRYPOINT_TEST_EPTRNXPARAMETERSTEST_H_
#define TEST_ENTRYPOINT_TEST_EPTRNXPARAMETERSTEST_H_

#include "gtest/gtest.h"
using namespace std;


extern "C" {
    #include "EntryPoint/epTrnxParameters.h"
    #include "Base/err.h"
    #include "Base/utils.h"
}

int GenerateUnPredictNum_1(unsigned char* pOut, unsigned long* pOutSize)
{
    unsigned char randomNumber[] = {
        0xDE, 0xAD, 0xBE, 0xEF
    };
    memcpy(pOut, randomNumber, MIN(sizeof(randomNumber), *pOutSize));
    return SUCCESS;
}

int GenerateUnPredictNum_2(unsigned char* pOut, unsigned long* pOutSize)
{
    *pOutSize = 10;
    return SUCCESS;
}


class TestEpTrnxParameters : public ::testing::Test {
    protected:
    HalInterfaces hal;

    virtual void SetUp() {
        injectInterface(&hal, RandomNumberGenerator, (void*)&generateUnpredictableNumberDefaultImpl);
    }
};

//--------------------------------------------------------------------

TEST_F(TestEpTrnxParameters, reset)
{
    EpTrnxParams epTrnx;
    int actual;

    actual = resetEpTrnxParameters(NULL);
    EXPECT_EQ(INVALID_PARAMETER, actual);

    actual = resetEpTrnxParameters(&epTrnx);
    EXPECT_EQ(SUCCESS, actual);
}

//--------------------------------------------------------------------

TEST_F(TestEpTrnxParameters, updateEpTrnxParameters_negative)
{
    EpTrnxParams epTrnxParams;
    int actual;

    actual = updateEpTrnxParameters(NULL, NULL);
    EXPECT_EQ(INVALID_PARAMETER, actual);

    actual = updateEpTrnxParameters(&epTrnxParams, NULL);
    EXPECT_EQ(INVALID_PARAMETER, actual);

    actual = updateEpTrnxParameters(NULL, &hal);
    EXPECT_EQ(INVALID_PARAMETER, actual);
}

TEST_F(TestEpTrnxParameters, updateEpTrnxParameters_negative_2)
{
    EpTrnxParams epTrnxParams;
    int actual;

    // special random number generator injected for this test purposes.
    injectInterface(&hal, RandomNumberGenerator, (void*)&GenerateUnPredictNum_2);

    actual = updateEpTrnxParameters(&epTrnxParams, &hal);
    EXPECT_EQ(INCORRECT_DATA, actual);
}

TEST_F(TestEpTrnxParameters, updateEpTrnxParameters_1)
{
    EpTrnxParams epTrnxParams;
    int actual;

    // special random number generator injected for this test purposes.
    injectInterface(&hal, RandomNumberGenerator, (void*)&GenerateUnPredictNum_1);

    actual = updateEpTrnxParameters(&epTrnxParams, &hal);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0xDE, epTrnxParams.unpredictableNumber[0]);
    EXPECT_EQ(0xAD, epTrnxParams.unpredictableNumber[1]);
    EXPECT_EQ(0xBE, epTrnxParams.unpredictableNumber[2]);
    EXPECT_EQ(0xEF, epTrnxParams.unpredictableNumber[3]);
}

#endif //TEST_ENTRYPOINT_TEST_EPTRNXPARAMETERSTEST_H_