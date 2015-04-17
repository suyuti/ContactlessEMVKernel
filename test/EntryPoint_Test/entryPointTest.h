/*
    Copyright 2015
*/

#ifndef TEST_ENTRYPOINT_TEST_ENTRYPOINTTEST_H_
#define TEST_ENTRYPOINT_TEST_ENTRYPOINTTEST_H_

#include "gtest/gtest.h"
using namespace std;


extern "C" {
    #include "EntryPoint/entryPoint.h"
    #include "Base/err.h"
}

class TestEntryPoint : public ::testing::Test {
};

TEST_F(TestEntryPoint, ep_init)
{
    int err             = ep_init();
    int expectedState   = EP_START_STATE_A;
    int actualState     = t_getEpState();

    EXPECT_EQ(SUCCESS,       err);
    EXPECT_EQ(expectedState, actualState);
}

TEST_F(TestEntryPoint, _ep_startA)
{
    int err             = _ep_startA();
    int expectedState   = EP_START_STATE_B;
    int actualState     = t_getEpState();

    EXPECT_EQ(SUCCESS,       err);
    EXPECT_EQ(expectedState, actualState);
}

TEST_F(TestEntryPoint, _ep_startB)
{
    int err             = _ep_startB();
    int expectedState   = EP_START_STATE_C;
    int actualState     = t_getEpState();

    EXPECT_EQ(SUCCESS,       err);
    EXPECT_EQ(expectedState, actualState);
}

TEST_F(TestEntryPoint, _ep_startC)
{
    int err             = _ep_startC();
    int expectedState   = EP_START_STATE_D;
    int actualState     = t_getEpState();

    EXPECT_EQ(SUCCESS,       err);
    EXPECT_EQ(expectedState, actualState);
}


#endif// TEST_ENTRYPOINT_TEST_ENTRYPOINTTEST_H_
