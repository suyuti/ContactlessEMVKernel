#ifndef _TEST_MOCKUPS_H_
#define _TEST_MOCKUPS_H_

#include <gtest/gtest.h>
#include "./mockReader.h"

extern "C" {
    #include "../../src/Base/kernel.h"
    #include "../../src/Base/err.h"
    #include "../../src/EntryPoint/entryPoint.h"
}
using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::SetArgPointee;
using ::testing::SetArrayArgument;
using namespace std;

class TestMockups : public ::testing::Test {
};

TEST_F(TestMockups, f)
{
    StrictMockReaderFunctions readerApi;

    EXPECT_CALL(readerApi, reset())
        .Times(Exactly(1))
        .WillOnce(Return(SUCCESS));

    setCrOpen(&reset_Mock);
    initialize();    
    ep_process();
}


#endif// _TEST_MOCKUPS_H_
