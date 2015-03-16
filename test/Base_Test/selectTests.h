#ifndef _SELECT_TEST_H_
#define _SELECT_TEST_H_

#include "gtest/gtest.h"
#include "../testUtils.h"
#include <string.h>

extern "C" {
    #include "Base/select.h"
}
using namespace std;

class TestSelect : public ::testing::Test {
};

TEST_F(TestSelect, _buildSelect)
{
    char            aid[]           = {0xA0, 0x00, 0x00, 0x00, 0x01};
    int             ret             = 0;
    unsigned char   actual[255]     = {0x00};
    int             size            = 0;
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
    int             size            = 0;

    ret = _buildSelectPpse(actual, &size);

    EXPECT_EQ(0, ret);
    EXPECT_EQ(expectedSize, size);
    EXPECT_EQ(0, memcmp(expected, actual, expectedSize));

}

//-----------------------------------------------------------------------------------

TEST_F(TestSelect, selectPPSE)
{
    int             ret             = 0;

    ret = selectPpse();

    EXPECT_EQ(0, ret);

}

//-----------------------------------------------------------------------------------
#define EXPECT_MEMEQ(a,b)   {                                                   \
                                unsigned char t[1024] = {0x00};                 \
                                int size = EmvTest::TestUtils::str2bcd((a), t); \
                                EXPECT_EQ(0, memcmp(t, (b), size));              \
                            }

TEST_F(TestSelect, resolveSelectPpse)
{
    int             ret             = 0;

    unsigned char   answer[1024]    = {0xA0};
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
    T6F _6f;
    memset(&_6f, 0x00, sizeof(_6f));

    // Branch 1
    ret = _resolveSelectPpse(NULL, 0, NULL);
    EXPECT_EQ(-1, ret);

    // Branch 2
    ret = _resolveSelectPpse(NULL, 10, NULL);
    EXPECT_EQ(-1, ret);

    // Branch 3
    ret = _resolveSelectPpse(answer, 0, NULL);
    EXPECT_EQ(-1, ret);

    ret = _resolveSelectPpse(answer, size, &_6f);
    EXPECT_EQ(0, ret);

    EmvTest::TestUtils::log(_6f._84, sizeof(_6f._84));
    EXPECT_MEMEQ("325041592E5359532E4444463031", _6f._84);
}

//-----------------------------------------------------------------------------------

#endif// _SELECT_TEST_H_
