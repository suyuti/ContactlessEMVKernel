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

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_5_Negative) {
    int actual =  _3_1_1_5(NULL, 0);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_6_Negative) {
    int actual =  _3_1_1_6(NULL, 0);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_6) {
    EpConfig config;

    memset(&config, 0x00, sizeof(EpConfig));
    
    int actual =  _3_1_1_6(&config, 0);
    EXPECT_EQ(SUCCESS, actual);

    // Branch 1
    SET_EXIST_CLESS_FLOOR_LIMIT(config.configData);
    actual =  _3_1_1_6(&config, 0);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_FALSE(IS_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(config.indicators));

    // Branch 2
    SET_EXIST_CLESS_FLOOR_LIMIT(config.configData);
    config.configData.clessFloorLimit = 9;
    actual =  _3_1_1_6(&config, 8);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_FALSE(IS_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(config.indicators));

    // Branch 3
    SET_EXIST_CLESS_FLOOR_LIMIT(config.configData);
    config.configData.clessFloorLimit = 9;
    actual =  _3_1_1_6(&config, 10);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_TRUE(IS_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(config.indicators));
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_7_Negative) {
    int actual =  _3_1_1_7(NULL, 0);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_7) {
    EpConfig config;
    memset(&config, 0x00, sizeof(EpConfig));

    // B1
    int actual =  _3_1_1_7(&config, 0);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_FALSE(IS_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(config.indicators));

    // B2
    memset(&config, 0x00, sizeof(EpConfig));
    SET_TERM_FLOOR_LIMIT(config.configData, 10);
    actual =  _3_1_1_7(&config, 11);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_TRUE(IS_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(config.indicators));

    // B3
    memset(&config, 0x00, sizeof(EpConfig));
    SET_TERM_FLOOR_LIMIT(config.configData, 10);
    actual =  _3_1_1_7(&config, 9);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_FALSE(IS_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(config.indicators));

    // B4
    memset(&config, 0x00, sizeof(EpConfig));
    RESET_EXIST_TERM_FLOOR_LIMIT(config.configData);
    actual =  _3_1_1_7(&config, 9);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_FALSE(IS_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(config.indicators));

}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_8_Negative) {
    int actual =  _3_1_1_8(NULL, 0);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_8) {
    EpConfig config;
    memset(&config, 0x00, sizeof(EpConfig));

    // B1
    SET_CVM_REQ_LIMIT(config.configData, 10);
    int actual =  _3_1_1_8(&config, 9);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_FALSE(IS_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(config.indicators));

    //B2
    memset(&config, 0x00, sizeof(EpConfig));
    SET_CVM_REQ_LIMIT(config.configData, 10);
    actual =  _3_1_1_8(&config, 10);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_TRUE(IS_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(config.indicators));

    //B3
    memset(&config, 0x00, sizeof(EpConfig));
    SET_CVM_REQ_LIMIT(config.configData, 10);
    actual =  _3_1_1_8(&config, 11);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_TRUE(IS_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(config.indicators));

    //B3
    memset(&config, 0x00, sizeof(EpConfig));
    RESET_EXIST_CVM_REQ_LIMIT(config.configData);
    actual =  _3_1_1_8(&config, 11);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_FALSE(IS_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(config.indicators));
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_9_Negative) {
    int actual =  _3_1_1_9(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestPreProcessing, _3_1_1_9) {
    EpConfig config;
    memset(&config, 0x00, sizeof(EpConfig));

    // B1
    int actual =  _3_1_1_9(&config);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_FALSE(IS_ONLINE_CRYPT_REQ(config.indicators.ttq));

    // B2
    memset(&config, 0x00, sizeof(EpConfig));
    SET_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(config.indicators);
    actual =  _3_1_1_9(&config);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_TRUE(IS_ONLINE_CRYPT_REQ(config.indicators.ttq));

}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif// _TEST_PREPROCESSING_H_
