#ifndef _ENTRY_POINT_TEST_H_
#define _ENTRY_POINT_TEST_H_

#include "gtest/gtest.h"
using namespace std;

class TestEntryPoint : public ::testing::Test {
};

TEST_F(TestEntryPoint, f)
{
    EXPECT_TRUE(1==1);
}

#endif// _ENTRY_POINT_TEST_H_
