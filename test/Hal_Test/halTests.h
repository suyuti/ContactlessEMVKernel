/*
    Copyright 2015
*/

#ifndef TEST_HAL_TEST_HALTEST_H_
#define TEST_HAL_TEST_HALTEST_H_

#include "gtest/gtest.h"
using namespace std;


extern "C" {
    #include "EntryPoint/entryPoint.h"
    #include "Base/err.h"
    #include "Hal/halInjection.h"
    #include "Hal/linux/unPredNumGen.h"
}

class TestHal : public ::testing::Test {
protected:
    HalInterfaces hal;

    virtual void SetUp() {
        injectInterface(&hal, RandomNumberGenerator, (void*)&generateUnpredictableNumberDefaultImpl);
    }
};

TEST_F(TestHal, generateUnpredictableNumberDefaultImpl)
{
    unsigned char tmp[10];
    long len = 0;
    int actual;

    actual = generateUnpredictableNumberDefaultImpl(NULL, &len);
    EXPECT_EQ(INVALID_PARAMETER, actual);

    actual = generateUnpredictableNumberDefaultImpl(tmp, NULL);
    EXPECT_EQ(INVALID_PARAMETER, actual);

    len = 4;
    actual = generateUnpredictableNumberDefaultImpl(tmp, &len);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(4, len);
    EXPECT_TRUE(tmp[0]!=tmp[1]);
    EXPECT_TRUE(tmp[1]!=tmp[2]);
    EXPECT_TRUE(tmp[2]!=tmp[3]);
    EXPECT_TRUE(tmp[3]!=tmp[0]);


}
#endif //TEST_HAL_TEST_HALTEST_H_