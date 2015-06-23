#ifndef _TEST_PREPROCESSING_H_
#define _TEST_PREPROCESSING_H_

#include "../BaseTest.h"
extern "C" {
    #include "EntryPoint/epPreProcessing.h"
    #include "EntryPoint/epIndicators.h"
    #include "EntryPoint/ttq.h"
}

class TestPreProcessing : public BaseTest {
};

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_1) {
    EpConfig config;
    memset(&config, 0x00, sizeof(EpConfig));
    int actual =  _3_1_1_1(&config);

    EXPECT_EQ(SUCCESS, actual);
    EXPECT_FALSE(IS_EPIND_STATUS_CHECK_REQ(config.indicators));
    EXPECT_FALSE(IS_EPIND_CLESS_APP_NOT_ALLOWED(config.indicators));
    EXPECT_FALSE(IS_EPIND_ZERO_AMOUNT(config.indicators));
    EXPECT_FALSE(IS_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(config.indicators));
    EXPECT_FALSE(IS_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(config.indicators));
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_1_Negative) {
    int actual =  _3_1_1_1(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_2) {
    EpConfig config;
    memset(&config, 0x00, sizeof(EpConfig));
    
    int actual =  _3_1_1_2(&config);
    EXPECT_EQ(SUCCESS, actual);

    memset(&config, 0x00, sizeof(EpConfig));
    SET_EXIST_TTQ(config.configData);

    actual =  _3_1_1_2(&config);

    EXPECT_EQ(FALSE, IS_ONLINE_CRYPT_REQ(config.indicators.ttq));
    EXPECT_EQ(FALSE, IS_CVM_REQ(config.indicators.ttq));
    EXPECT_EQ(SUCCESS, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_2_Negative) {
    int actual =  _3_1_1_2(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_3_Negative) {
    int actual =  _3_1_1_3(NULL, 0, 0);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_3) {
    EpConfig config;
    memset(&config, 0x00, sizeof(EpConfig));
    int actual =  _3_1_1_3(&config, 0, 0);
    EXPECT_EQ(SUCCESS, actual);

    SET_EXIST_STATUS_CHECK(config.configData);
    actual =  _3_1_1_3(&config, 0, 0);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_FALSE(IS_EPIND_STATUS_CHECK_REQ(config.indicators));

    SET_EXIST_STATUS_CHECK(config.configData);
    SET_STATUS_CHECK(config.configData);
    actual =  _3_1_1_3(&config, 0, 0);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_TRUE(IS_EPIND_STATUS_CHECK_REQ(config.indicators));
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_4_Negative) {
    int actual =  _3_1_1_4(NULL, 0, 0);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_4) {
    EpConfig config;
    memset(&config, 0x00, sizeof(EpConfig));

    int actual =  _3_1_1_4(&config, 0, 10);
    EXPECT_EQ(SUCCESS, actual);

    actual =  _3_1_1_4(&config, 0, 0);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_TRUE(IS_EPIND_ZERO_AMOUNT(config.indicators));
}

#endif// _TEST_PREPROCESSING_H_
