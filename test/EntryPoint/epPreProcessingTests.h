#ifndef _TEST_PREPROCESSING_H_
#define _TEST_PREPROCESSING_H_

#include "../BaseTest.h"

class TestPreProcessing : public BaseTest {
};

TEST_F(TestPreProcessing, _3_1_1_1) {
    int actual =  _3_1_1_1(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}


#endif// _TEST_PREPROCESSING_H_
