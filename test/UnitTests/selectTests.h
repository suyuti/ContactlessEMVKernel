/*
    Copyright 2015
*/

#ifndef TEST_BASE_TEST_SELECTTESTS_H_
#define TEST_BASE_TEST_SELECTTESTS_H_

#include "gtest/gtest.h"
#include "../testUtils.h"
#include <string.h>

extern "C" {
    #include "Base/select.h"
    #include "Base/err.h"
}
using namespace std;

#define EXPECT_MEMEQ(a,b)   {                                                   \
                                unsigned char t[1024] = {0x00};                 \
                                int size = EmvTest::TestUtils::str2bcd((a), t); \
                                EXPECT_EQ(0, memcmp(t, (b), size));              \
                            }

class TestSelect : public ::testing::Test {
};


TEST_F(TestSelect, _clearFci)
{
    int actual = 0;
    int expected = INVALID_PARAMETER;
    Fci f;

    actual = _clearFci(NULL);
    EXPECT_EQ(expected, actual);

    expected = SUCCESS;
    actual = _clearFci(&f);
    EXPECT_EQ(expected, actual);

    unsigned char* p = reinterpret_cast<unsigned char*>(&f);
    for (int i = 0; i < sizeof(Fci); ++i) {
        EXPECT_EQ(0, p[i]);
    }
}

TEST_F(TestSelect, _setFciIssData)
{
    int actual = 0;
    int expected = 0;
    unsigned char data1[] = {0x01};
    Fci f;
    _clearFci(&f);

    actual = _setFciIssData(NULL, 0x4F, data1, sizeof(data1));
    EXPECT_EQ(INVALID_PARAMETER, actual);
    
    _clearFci(&f);
    actual = _setFciIssData(&f, 0x4F, data1, sizeof(data1));
    EXPECT_EQ(-99, actual);

    unsigned char data2[] = {0x01, 0x02, 0x03, 0x04, 0x05,
                             0x11, 0x12, 0x13, 0x14, 0x15,
                             0x21, 0x22, 0x23, 0x24, 0x25,
                             0x31, 0x32, 0x33, 0x34, 0x35};
    _clearFci(&f);
    _incFciIssDataCounter(&f);
    actual = _setFciIssData(&f, 0x4F, data2, sizeof(data2));
    EXPECT_EQ(INCORRECT_DATA, actual);
}

TEST_F(TestSelect, _setFciIssData_50)
{
    int actual = 0;
    int expected = 0;
    unsigned char data1[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                             0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
                             0x0D, 0x0E, 0x0F};
    Fci f;

    _clearFci(&f);
    _incFciIssDataCounter(&f);
    actual = _setFciIssData(&f, 0x50, data1, sizeof(data1));
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_MEMEQ("010102030405060708090A0B0C0D0E0F", f._fciIssData[f._fciIssDataCount-1]._50);

    unsigned char data2[] = {0x01, 0x02, 0x03, 0x04, 0x05,
                             0x11, 0x12, 0x13, 0x14, 0x15,
                             0x21, 0x22, 0x23, 0x24, 0x25,
                             0x31, 0x32, 0x33, 0x34, 0x35};
    _clearFci(&f);
    _incFciIssDataCounter(&f);
    actual = _setFciIssData(&f, 0x50, data2, sizeof(data2));
    EXPECT_EQ(INCORRECT_DATA, actual);
}

TEST_F(TestSelect, _setFciIssData_87)
{
    int actual = 0;
    int expected = 0;
    unsigned char data1[] = {0x01};
    Fci f;

    _clearFci(&f);
    _incFciIssDataCounter(&f);
    actual = _setFciIssData(&f, 0x87, data1, sizeof(data1));
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_MEMEQ("0101", f._fciIssData[f._fciIssDataCount-1]._87);

    unsigned char data2[] = {0x01, 0x02, 0x03, 0x04, 0x05,
                             0x11, 0x12, 0x13, 0x14, 0x15,
                             0x21, 0x22, 0x23, 0x24, 0x25,
                             0x31, 0x32, 0x33, 0x34, 0x35};
    _clearFci(&f);
    _incFciIssDataCounter(&f);
    actual = _setFciIssData(&f, 0x87, data2, sizeof(data2));
    EXPECT_EQ(INCORRECT_DATA, actual);
}

TEST_F(TestSelect, _setFciIssData_9F2A)
{
    int actual = 0;
    int expected = 0;
    unsigned char data1[] = {0x01};
    Fci f;

    _clearFci(&f);
    _incFciIssDataCounter(&f);
    actual = _setFciIssData(&f, 0x9F2A, data1, sizeof(data1));
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_MEMEQ("0101", f._fciIssData[f._fciIssDataCount-1]._9F2A);

    unsigned char data2[] = {0x01, 0x02, 0x03, 0x04, 0x05,
                             0x11, 0x12, 0x13, 0x14, 0x15,
                             0x21, 0x22, 0x23, 0x24, 0x25,
                             0x31, 0x32, 0x33, 0x34, 0x35};
    _clearFci(&f);
    _incFciIssDataCounter(&f);
    actual = _setFciIssData(&f, 0x9F2A, data2, sizeof(data2));
    EXPECT_EQ(INCORRECT_DATA, actual);
}

TEST_F(TestSelect, _setFciIssData_unknownTag)
{
    int actual = 0;
    int expected = 0;
    unsigned char data1[] = {0x01};
    Fci f;

    _clearFci(&f);
    _incFciIssDataCounter(&f);
    actual = _setFciIssData(&f, 0xFFFF, data1, sizeof(data1));
    EXPECT_EQ(SUCCESS, actual);
}

TEST_F(TestSelect, _incFciIssDataCounter)
{
    int actual = 0;
    int expected = 0;
    Fci f;
    _clearFci(&f);

    actual = _incFciIssDataCounter(&f); EXPECT_EQ(SUCCESS, actual); EXPECT_EQ(1, f._fciIssDataCount);
    actual = _incFciIssDataCounter(&f); EXPECT_EQ(SUCCESS, actual); EXPECT_EQ(2, f._fciIssDataCount);
    actual = _incFciIssDataCounter(&f); EXPECT_EQ(SUCCESS, actual); EXPECT_EQ(3, f._fciIssDataCount);
    actual = _incFciIssDataCounter(&f); EXPECT_EQ(SUCCESS, actual); EXPECT_EQ(4, f._fciIssDataCount);
    actual = _incFciIssDataCounter(&f); EXPECT_EQ(SUCCESS, actual); EXPECT_EQ(5, f._fciIssDataCount);
    actual = _incFciIssDataCounter(&f); EXPECT_EQ(SUCCESS, actual); EXPECT_EQ(6, f._fciIssDataCount);
    actual = _incFciIssDataCounter(&f); EXPECT_EQ(SUCCESS, actual); EXPECT_EQ(7, f._fciIssDataCount);
    actual = _incFciIssDataCounter(&f); EXPECT_EQ(SUCCESS, actual); EXPECT_EQ(8, f._fciIssDataCount);
    actual = _incFciIssDataCounter(&f); EXPECT_EQ(SUCCESS, actual); EXPECT_EQ(9, f._fciIssDataCount);
    actual = _incFciIssDataCounter(&f); EXPECT_EQ(SUCCESS, actual); EXPECT_EQ(10, f._fciIssDataCount);
    actual = _incFciIssDataCounter(&f); EXPECT_EQ(-99, actual); 
}


TEST_F(TestSelect, _buildSelect)
{
    char            aid[]           = {0xA0, 0x00, 0x00, 0x00, 0x01};
    int             ret             = 0;
    unsigned char   actual[255]     = {0x00};
    unsigned long   size            = 0;
    unsigned char   expected[255]   = {0x00, 0xA4, 0x04, 0x00, 0x05, 0xA0, 0x00, 0x00, 0x00, 0x01};
    int             expectedSize    = 10;

    ret = _buildSelect(aid, sizeof(aid), actual, &size);

    EXPECT_EQ(0, ret);
    EXPECT_EQ(expectedSize, size);
    EXPECT_EQ(0, memcmp(expected, actual, expectedSize));

    //----------------------------------------------

    ret = _buildSelect(aid, sizeof(aid), NULL, NULL);
    EXPECT_EQ(-1, ret);

    //----------------------------------------------

    ret = _buildSelect(NULL, 0, actual, &size);
    EXPECT_EQ(-1, ret);

    ret = _buildSelect(NULL, 0, 0, NULL);
    EXPECT_EQ(-1, ret);

    //----------------------------------------------
}

TEST_F(TestSelect, _buildSelectPPSE)
{
    int             ret             = 0;
    unsigned char   actual[255]     = {0x00};
    unsigned char   expected[255]   = {0x00, 0xA4, 0x04, 0x00, 0x0E,
                    '2','P','A','Y','.','S','Y','S','.','D','D','F','0','1'};
    int             expectedSize    = 19;
    unsigned long   size            = 0;

    ret = _buildSelectPpse(actual, &size);

    EXPECT_EQ(0, ret);
    EXPECT_EQ(expectedSize, size);
    EXPECT_EQ(0, memcmp(expected, actual, expectedSize));

}

//-----------------------------------------------------------------------------------

TEST_F(TestSelect, selectPPSE)
{
    int             ret             = 0;


    EXPECT_EQ(0, ret);

}

//-----------------------------------------------------------------------------------

TEST_F(TestSelect, resolveSelectPpse_negative)
{
    int             ret             = 0;
    unsigned char   answer[1024]    = {0xA0};
    int             size            = 0;
    Fci _6f;

    EXPECT_EQ(INVALID_PARAMETER, _resolveSelectPpse(NULL, 10, &_6f));
    EXPECT_EQ(INVALID_PARAMETER, _resolveSelectPpse(NULL, 10, NULL));
    EXPECT_EQ(INVALID_PARAMETER, _resolveSelectPpse(NULL,  0, &_6f));
    EXPECT_EQ(INVALID_PARAMETER, _resolveSelectPpse(NULL,  0, NULL));
    EXPECT_EQ(INVALID_PARAMETER, _resolveSelectPpse(answer, 10, NULL));
    EXPECT_EQ(INVALID_PARAMETER, _resolveSelectPpse(answer,  0, &_6f));
    EXPECT_EQ(INVALID_PARAMETER, _resolveSelectPpse(answer,  0, NULL));
}

TEST_F(TestSelect, resolveSelectPpse)
{
    int             ret             = 0;

    unsigned char   answer[1024]    = {0x00};
    int             size            = 0;
    size = EmvTest::TestUtils::str2bcd("6F59840E325041592E53"
                                       "59532E4444463031A547"
                                       "BF0C44610C4F07A00000"
                                       "00041010870101610C4F"
                                       "07A00000000430608701"
                                       "03610A4F05B012345678"
                                       "870109610C4F07B01234"
                                       "56781020870108610C4F"
                                       "07B01234567810308701"
                                       "07", answer);
    Fci _6f;
    memset(&_6f, 0x00, sizeof(_6f));

    ret = _resolveSelectPpse(answer, size, &_6f);
    EXPECT_EQ(SUCCESS, ret);

    //EmvTest::TestUtils::log(_6f._84, sizeof(_6f._84));
    EXPECT_MEMEQ("01325041592E5359532E4444463031", _6f._84);
    //EXPECT_MEMEQ("01A0000000041010", _6f._a5._bf0c[0]._61[0]._4F);
}

//-----------------------------------------------------------------------------------

#endif// TEST_BASE_TEST_SELECTTESTS_H_
