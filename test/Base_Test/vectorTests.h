/*
    Copyright 2015
*/

#ifndef TEST_BASE_TEST_VECTORTESTS_H_
#define TEST_BASE_TEST_VECTORTESTS_H_

#include "gtest/gtest.h"

extern "C" {
    #include "Utils/_vector.h"
}
using namespace std;

class TestVector : public ::testing::Test {
};

TEST_F(TestVector, toInt_Negative)
{
    _vector *pV = _vector_create(sizeof(int), 10);
    EXPECT_TRUE(pV != NULL);

    int s = _vector_size(pV);
    EXPECT_EQ(0, s);

    VECTOR_INSERT(int, pV, 1, pV->size);
    
    s = _vector_size(pV);
    EXPECT_EQ(1, s);



    _vector_clear(pV);
}

#endif// TEST_BASE_TEST_VECTORTESTS_H_
