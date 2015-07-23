/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_TEST_ENTRYPOINT_H_
#define MODULAR_TEST_ENTRYPOINT_H_

#include "../BaseTest.h"
extern "C" {
    #include "Common/err.h"
    #include "EntryPoint/entryPoint.h"
};

class Test_EntryPoint : public BaseTest {
};

TEST_F(Test_EntryPoint, clearEntryPoint_Negative) {
    int actual = clearEntryPoint(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

TEST_F(Test_EntryPoint, clearEntryPoint) {
    Ep ep;

    int actual = clearEntryPoint(&ep);
    EXPECT_EQ(SUCCESS, actual);

    bool nonZero = false;
    unsigned char* p = (unsigned char*)&ep;
    for(int i = 0; i < sizeof(Ep); ++i) {
        if (*p!=0x00) {
            nonZero = true;
            break;
        }
    }
    EXPECT_TRUE(!nonZero);
}


#endif  // MODULAR_TEST_ENTRYPOINT_H_
