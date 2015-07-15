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
using ::testing::Invoke;
using ::testing::SetArgPointee;
using ::testing::SetArrayArgument;
using ::testing::WithArg;
using ::testing::Args;
using ::testing::ElementsAre;
using ::testing::ElementsAreArray;
using ::testing::NotNull;
using ::testing::Gt;
using ::testing::InSequence;
using namespace std;

class TestMockups : public ::testing::Test {
public:
    TestMockups() {
        setCrOpen(&reset_Mock);
        setCrSendRecv(&sendrecv_Mock);

    }
protected:
    virtual void SetUp() {

    }
    virtual void TearDown() {

    }

    StrictMockReaderFunctions readerApi;
};

int foo(const unsigned char*  pIn, 
                      int                   inSize, 
                      unsigned char*        pOut, 
                      unsigned long*        pOutSize)
{
    printf("%d\n\n", inSize);
    for(int i = 0; i < inSize; ++i) {
        printf("%02X ", pIn[i]);
    }
    printf("\n");
    return 0;
}

/*
TEST_F(TestMockups, f)
{
    EXPECT_CALL(readerApi, reset())
        .Times(Exactly(1))
        .WillOnce(Return(SUCCESS));

    EXPECT_CALL(readerApi, sendRecv(_,_,_,_))
        .Times(AtLeast(1))
        .WillOnce(Invoke(foo))
        .WillOnce(Invoke(foo));
//            Return(SUCCESS));

    initialize();    
    ep_process();
}
*/
TEST_F(TestMockups, _2EA_001_00_01)
{
    // case 01:
  
    unsigned char c1[] = {0x00, 0xA4, 0x04, 0x00, 0x0E, 0x32, 0x50, 
                          0x41, 0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 
                          0x44, 0x44, 0x46, 0x30, 0x31};
    unsigned char r1[] = {0x6F, 0x2D, 0x84, 0x0E, 0x32, 0x50, 0x41, 
                          0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 
                          0x44, 0x46, 0x30, 0x31, 0xA5, 0x1B, 0xBF, 
                          0x0C, 0x18, 0x61, 0x16, 0x4F, 0x07, 0xA0, 
                          0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x50, 
                          0x04, 0x41, 0x50, 0x50, 0x31, 0x9F, 0x2A, 
                          0x01, 0x23, 0x87, 0x01, 0x01};
    EXPECT_CALL(readerApi, reset()).Times(Exactly(1)).WillOnce(Return(SUCCESS));

    EXPECT_CALL(readerApi, sendRecv(_,Gt(0),_,_))
        .With(Args<0,1>(ElementsAreArray(c1, sizeof(c1))))
        .Times(AtLeast(1))
        .WillOnce(
            DoAll(
                SetArrayArgument<2>(r1, r1+sizeof(r1)),
                SetArgPointee<3>((unsigned long)sizeof(r1)),
                Return(SUCCESS)
            )
        );

    initialize();    
    ep_process();
}
/*
TEST_F(TestMockups, xxxx)
{
    unsigned char c1[] = {0xAA};
    unsigned char c2[] = {0xBB, 0xCC};
    unsigned char r1[] = {0x6F, 0x2D, 0x84, 0x0E, 0x32, 0x50, 0x41, 
                          0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 
                          0x44, 0x46, 0x30, 0x31, 0xA5, 0x1B, 0xBF, 
                          0x0C, 0x18, 0x61, 0x16, 0x4F, 0x07, 0xA0, 
                          0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x50, 
                          0x04, 0x41, 0x50, 0x50, 0x31, 0x9F, 0x2A, 
                          0x01, 0x23, 0x87, 0x01, 0x01};

    InSequence s1;
    EXPECT_CALL(readerApi, reset()).Times(Exactly(1)).WillOnce(Return(SUCCESS));

    EXPECT_CALL(readerApi, sendRecv(_,Gt(0),_,_))
        .With(Args<0,1>(ElementsAreArray(c1, sizeof(c1))))
        .WillOnce(
            DoAll(
                SetArrayArgument<2>(r1, r1+sizeof(r1)),
                SetArgPointee<3>((unsigned long)sizeof(r1)),
                Return(SUCCESS)
            )
        );
    EXPECT_CALL(readerApi, sendRecv(_,Gt(0),_,_))
        .With(Args<0,1>(ElementsAreArray(c2, sizeof(c2))))
        .WillOnce(
            DoAll(
                SetArrayArgument<2>(r1, r1+sizeof(r1)),
                SetArgPointee<3>((unsigned long)sizeof(r1)),
                Return(SUCCESS)
            )
        );

    initialize();    
    ep_process();
}
*/


#endif// _TEST_MOCKUPS_H_
