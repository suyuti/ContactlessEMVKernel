/*
    Copyright 2015
*/

#ifndef TEST_BASE_TEST_TLVTESTS_H_
#define TEST_BASE_TEST_TLVTESTS_H_

#include "gtest/gtest.h"

extern "C" {
    #include "Base/tlv.h"
    #include "Base/err.h"
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
    //EXPECT_EQ(expected, actual);
    //EXPECT_EQ(expectedTagLen, actualTagLen);
    //EXPECT_EQ(expectedConstructed, actualConstructed);

    unsigned char data4[] = {0x20, 0x03, 0x01, 0x01, 0xAA};
    actual              = 0;
    expected            = 0x20;
    actualTagLen        = 0;
    expectedTagLen      = 1;
    actualConstructed   = 0;
    expectedConstructed = 1;

    actual = _tag(data4, &actualTagLen, &actualConstructed);
    EXPECT_EQ(expected, actual);
    EXPECT_EQ(expectedTagLen, actualTagLen);
    EXPECT_EQ(expectedConstructed, actualConstructed);
}

TEST_F(TestTlv, _len_negative)
{
    unsigned char d[] = {0x00};
    int len = 0;

    int actual = _len(NULL, NULL);
    EXPECT_EQ(-1, actual);

    actual = _len(d, NULL);
    EXPECT_EQ(-1, actual);

    actual = _len(NULL, &len);
    EXPECT_EQ(-1, actual);
}

TEST_F(TestTlv, _len)
{
    unsigned char data1[] = {0x01, 0x02, 0x01, 0x02};

    int actual = 0;
    int expected = 2;

    int actualLenLen = 0;
    int expectedLenLen = 1;

    actual = _len(data1+1, &actualLenLen);
    EXPECT_EQ(expected, actual);
    EXPECT_EQ(expectedLenLen, actualLenLen);

    unsigned char data2[] = {0x01, 0x81, 0x02, 0x01, 0x02};

    actual = 0;
    expected = 2;

    actualLenLen = 0;
    expectedLenLen = 2;

    actual = _len(data2+1, &actualLenLen);
    EXPECT_EQ(expected, actual);
    EXPECT_EQ(expectedLenLen, actualLenLen);

}


typedef struct {
    unsigned char dfName[32];
} DummyTestTarget;

int onTag_Test(int tag, int len, int constructed, const unsigned char* val, void* target)
{
    return SUCCESS;
}

int onTag_Test_False(int tag, int len, int constructed, const unsigned char* val, void* target)
{
    return -99;
}


TEST_F(TestTlv, _parse_negative)
{
    char target;

    EXPECT_EQ(INVALID_PARAMETER, _parse(NULL, 0, NULL, NULL));
    EXPECT_EQ(INVALID_PARAMETER, _parse(NULL, 1, NULL, NULL));
    EXPECT_EQ(INVALID_PARAMETER, _parse(NULL, 0, NULL, reinterpret_cast<int*>(&target)));

    unsigned char data[1024] = {0x00};
    int size = EmvTest::TestUtils::str2bcd( "6FFF840E325041592E53"
                                            "59532E4444463031A547"
                                            "BF0C44610C4F07A00000"
                                            "00041010870101610C4F"
                                            "07A00000000430608701"
                                            "03610A4F05B012345678"
                                            "870109610C4F07B01234"
                                            "56781020870108610C4F"
                                            "07B01234567810308701"
                                            "07", data);
    // 6F FF (invalid size)
    int actual = _parse(data, size, onTag_Test, &target);
    EXPECT_EQ(INCORRECT_DATA, actual);

}

TEST_F(TestTlv, _parse)
{
    DummyTestTarget target;
    unsigned char data[1024] = {0x00};
    int size = EmvTest::TestUtils::str2bcd( "6F59840E325041592E53"
                                            "59532E4444463031A547"
                                            "BF0C44610C4F07A00000"
                                            "00041010870101610C4F"
                                            "07A00000000430608701"
                                            "03610A4F05B012345678"
                                            "870109610C4F07B01234"
                                            "56781020870108610C4F"
                                            "07B01234567810308701"
                                            "07", data);
    int actual = _parse(data, size, onTag_Test, &target);
    EXPECT_EQ(SUCCESS, actual);

    actual = _parse(data, size, onTag_Test_False, &target);
    EXPECT_EQ(-99, actual);
}

#endif// TEST_BASE_TEST_TLVTESTS_H_
