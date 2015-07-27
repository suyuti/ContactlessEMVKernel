/*
    Copyright 2015
*/

#ifndef MODULAR_TEST_COMMONTESTS_BITSTESTS_H_
#define MODULAR_TEST_COMMONTESTS_BITSTESTS_H_

#include "gtest/gtest.h"

extern "C" {
    #include "Common/bits.h"
    #include "Common/general.h"
}
#include "../testUtils.h"
using namespace std;

class TestBits : public ::testing::Test {
};

TEST_F(TestBits, setBit)
{
    unsigned char v = 0x00;
    EXPECT_EQ(0x00, v);

    SET_BIT(v, BIT_1);
    EXPECT_EQ(0x01, v);

    SET_BIT(v, BIT_2);
    EXPECT_EQ(0x03, v);

    SET_BIT(v, BIT_3);
    EXPECT_EQ(0x07, v);
}

TEST_F(TestBits, resetBit)
{
    unsigned char v = 0xFF;
    EXPECT_EQ(0xFF, v);

    RESET_BIT(v, BIT_8);
    EXPECT_EQ(0x7F, v);

    RESET_BIT(v, BIT_1);
    EXPECT_EQ(0x7E, v);
}

TEST_F(TestBits, checkBit)
{
    unsigned char v = 0xFF;
    EXPECT_EQ(0xFF, v);

    EXPECT_EQ(SET, CHECK_BIT(v, BIT_1));
    EXPECT_EQ(SET, CHECK_BIT(v, BIT_2));
    EXPECT_EQ(SET, CHECK_BIT(v, BIT_3));
    EXPECT_EQ(SET, CHECK_BIT(v, BIT_4));
    EXPECT_EQ(SET, CHECK_BIT(v, BIT_5));
    EXPECT_EQ(SET, CHECK_BIT(v, BIT_6));
    EXPECT_EQ(SET, CHECK_BIT(v, BIT_7));
    EXPECT_EQ(SET, CHECK_BIT(v, BIT_8));

    RESET_BIT(v, BIT_5);
    EXPECT_EQ(RESET, CHECK_BIT(v, BIT_5));

    RESET_BIT(v, BIT_1);
    EXPECT_EQ(RESET, CHECK_BIT(v, BIT_1));

    RESET_BIT(v, BIT_8);
    EXPECT_EQ(RESET, CHECK_BIT(v, BIT_8));

    SET_BIT(v, BIT_1);
    EXPECT_EQ(SET, CHECK_BIT(v, BIT_1));
}

#endif  // MODULAR_TEST_COMMONTESTS_BITSTESTS_H_