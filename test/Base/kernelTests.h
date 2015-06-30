/*
    Copyright 2015
*/

#ifndef TEST_KERNELTESTS_H_
#define TEST_KERNELTESTS_H_

#include "../BaseTest.h"

extern "C" {
    #include "Base/err.h"
    #include "Base/kernel.h"
}

class TestKernel : public BaseTest {
};

//------------------------------------------------------------------------------------

TEST_F(TestKernel, getVersion)
{
    int actual = getVersion();
    EXPECT_EQ(99, actual);
}

//------------------------------------------------------------------------------------

TEST_F(TestKernel, initialize_Negative)
{
    int err = initialize(NULL);
    EXPECT_EQ(NULL_PARAMETER, err);

    err = initialize("");
    EXPECT_EQ(FILE_NOT_FOUND, err);

    err = initialize("./non_existent_folder");
    EXPECT_EQ(FILE_NOT_FOUND, err);
}

//------------------------------------------------------------------------------------

TEST_F(TestKernel, initialize_Negative2)
{
    setCardOpen(NULL);
    int err = initialize("./test/Runner2/termsetting1");
    EXPECT_EQ(HAL_INTERFACE_IS_NULL, err);
}

//------------------------------------------------------------------------------------

TEST_F(TestKernel, initialize)
{
    int err = initialize("./test/Runner2/termsetting1");
    EXPECT_EQ(SUCCESS, err);
    EXPECT_EQ(EpStateStartA, t_getEpState());
    
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

#endif //TEST_KERNELTESTS_H_