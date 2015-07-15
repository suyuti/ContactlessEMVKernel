/*
    Copyright 2015
*/

#ifndef MODULAR_TEST_COMMONTESTS_UTILSTESTS_H_
#define MODULAR_TEST_COMMONTESTS_UTILSTESTS_H_

#include "gtest/gtest.h"

extern "C" {
    #include "Common/utils.h"
}
using namespace std;

class TestUtils : public ::testing::Test {
};

TEST_F(TestUtils, toInt_Negative)
{
    int actual = 0;
    unsigned char v1[] = {0x01};

    actual = toInt(NULL, 0);
    EXPECT_EQ(-1, actual);

    actual = toInt(v1, 0);
    EXPECT_EQ(-1, actual);

    actual = toInt(NULL, 1);
    EXPECT_EQ(-1, actual);
}

TEST_F(TestUtils, toInt)
{
    int expected = 1;
    unsigned char v1[] = {0x01};
    int actual = 0;
    actual = toInt(v1, sizeof(v1));
    EXPECT_EQ(expected, actual);

    expected = 142;
    unsigned char v2[] = {0x8E};
    actual = toInt(v2, sizeof(v2));
    EXPECT_EQ(expected, actual);

    expected = 2;
    unsigned char v3[] = {0x00, 0x02};
    actual = toInt(v3, sizeof(v3));
    EXPECT_EQ(expected, actual);

    expected = 6850;
    unsigned char v4[] = {0x1A, 0xC2};
    actual = toInt(v4, sizeof(v4));
    EXPECT_EQ(expected, actual);
}

#endif  // MODULAR_TEST_COMMONTESTS_UTILSTESTS_H_
