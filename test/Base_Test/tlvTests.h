#ifndef _TLV_TESTS_H_
#define _TLV_TESTS_H_

#include "gtest/gtest.h"

extern "C" {
    #include "Base/tlv.h"
}
using namespace std;

class TestTlv : public ::testing::Test {
};

TEST_F(TestTlv, _tag_negative) 
{
    unsigned char d[] = {0x00};
    int len = 0;
    int constructed = 0;

    int actual = _tag(NULL, NULL, NULL);
    EXPECT_EQ(-1, actual);
    
    actual = _tag(d, NULL, NULL);
    EXPECT_EQ(-1, actual);

    actual = _tag(NULL, &len, NULL);
    EXPECT_EQ(-1, actual);

    actual = _tag(NULL, NULL, &constructed);
    EXPECT_EQ(-1, actual);

    actual = _tag(d, NULL, &constructed);
    EXPECT_EQ(-1, actual);

    actual = _tag(d, &len, NULL);
    EXPECT_EQ(-1, actual);

    actual = _tag(NULL, &len, &constructed);
    EXPECT_EQ(-1, actual);
}

TEST_F(TestTlv, _tag) 
{
    unsigned char data1[] = {0x01, 0x01, 0x01};

    int actual = 0;
    int expected = 1;

    int actualTagLen = 0;
    int expectedTagLen = 1;

    int actualConstructed = 0;
    int expectedConstructed = 0;

    actual = _tag(data1, &actualTagLen, &actualConstructed);
    EXPECT_EQ(expected, actual);
    EXPECT_EQ(expectedTagLen, actualTagLen);
    EXPECT_EQ(expectedConstructed, actualConstructed);


    unsigned char data2[] = {0x02, 0x02, 0x01, 0x02};
    actual              = 0;
    expected            = 0x02;
    actualTagLen        = 0;
    expectedTagLen      = 1;
    actualConstructed   = 0;
    expectedConstructed = 0;

    actual = _tag(data2, &actualTagLen, &actualConstructed);
    EXPECT_EQ(expected, actual);
    EXPECT_EQ(expectedTagLen, actualTagLen);
    EXPECT_EQ(expectedConstructed, actualConstructed);

    // Two byte length tag
    unsigned char data3[] = {0x81, 0x05, 0x02, 0x01, 0x02};
    actual              = 0;
    expected            = 0x05;
    actualTagLen        = 0;
    expectedTagLen      = 2;
    actualConstructed   = 0;
    expectedConstructed = 0;

    actual = _tag(data3, &actualTagLen, &actualConstructed);
    EXPECT_EQ(expected, actual);
    EXPECT_EQ(expectedTagLen, actualTagLen);
    EXPECT_EQ(expectedConstructed, actualConstructed);

}

#endif// _TLV_TESTS_H_
