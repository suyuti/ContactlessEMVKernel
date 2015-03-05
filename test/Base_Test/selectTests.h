#ifndef _SELECT_TEST_H_
#define _SELECT_TEST_H_

#include "gtest/gtest.h"

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


#endif// _SELECT_TEST_H_
