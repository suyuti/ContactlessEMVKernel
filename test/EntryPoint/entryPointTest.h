/*
    Copyright 2015
*/

#ifndef TEST_ENTRYPOINT_TEST_ENTRYPOINTTEST_H_
#define TEST_ENTRYPOINT_TEST_ENTRYPOINTTEST_H_

#include "../BaseTest.h"

extern "C" {
    #include "EntryPoint/entryPoint.h"
    #include "Base/err.h"
    #include "Hal/halInjection.h"
    #include "Hal/linux/unPredNumGen.h"
}

class TestEntryPoint : public BaseTest {
};

TEST_F(TestEntryPoint, ep_init)
{
    int err             = ep_init(&hal, "./test/Runner2/termsetting1");
    int expectedState   = EpStateStartA;
    int actualState     = t_getEpState();

    EXPECT_EQ(SUCCESS,       err);
    EXPECT_EQ(expectedState, actualState);
}

TEST_F(TestEntryPoint, _ep_startA)
{
    int err             = _ep_startA(0, 0);
    int expectedState   = EpStateStartB;
    int actualState     = t_getEpState();

    EXPECT_EQ(SUCCESS,       err);
    EXPECT_EQ(expectedState, actualState);
}

TEST_F(TestEntryPoint, _ep_startB)
{
    int err             = _ep_startB();
    int expectedState   = EpStateStartC;
    int actualState     = t_getEpState();

    EXPECT_EQ(SUCCESS,       err);
    EXPECT_EQ(expectedState, actualState);
}
/*
TEST_F(TestEntryPoint, _ep_startC)
{
    int err             = _ep_startC();
    int expectedState   = EpStateStartD;
    int actualState     = t_getEpState();

    EXPECT_EQ(SUCCESS,       err);
    EXPECT_EQ(expectedState, actualState);
}
*/

TEST_F(TestEntryPoint, ep_process)
{
//    int err = ep_init(&hal, "./test/Runner2/termsetting1");
//    err     = ep_process(0, 0);
//    EXPECT_EQ(SUCCESS,       err);
}


#endif// TEST_ENTRYPOINT_TEST_ENTRYPOINTTEST_H_
