/*
    Copyright 2015
*/

#ifndef TEST_ENTRYPOINT_TEST_EPCONFIG_H_
#define TEST_ENTRYPOINT_TEST_EPCONFIG_H_

#include "../BaseTest.h"
using namespace std;


extern "C" {
    #include "EntryPoint/epConfig.h"
    #include "Base/err.h"
}

class TestEpConfig : public BaseTest {
};

TEST_F(TestEpConfig, resetAllConfigs)
{
    int expected = SUCCESS;
    int actual = resetAllConfigs();
    EXPECT_EQ(expected, actual);

    EXPECT_EQ(0, t_getAidKidCount());
    EXPECT_EQ(0, t_getEpConfigCount());
}

TEST_F(TestEpConfig, addConfigByAidKid)
{
    int expected = SUCCESS;
    char aid[] = "A01020304";
    unsigned char kid = 0xAB;
    EpConfig    config;

    resetAllConfigs();

    int actual = addConfigByAidKid(aid, kid, config);
    EXPECT_EQ(expected, actual);

    EXPECT_EQ(1, t_getAidKidCount());
    EXPECT_EQ(1, t_getEpConfigCount());

    char anotherAid[] = "AABBCC";
    actual = addConfigByAidKid(anotherAid, kid, config);
    EXPECT_EQ(expected, actual);

    EXPECT_EQ(2, t_getAidKidCount());
    EXPECT_EQ(2, t_getEpConfigCount());
}

TEST_F(TestEpConfig, addConfigByAidKid_outofindex)
{
    int expected = SUCCESS;
    char aid[] = "A01020304";
    unsigned char kid = 0xAB;
    EpConfig    config;

    resetAllConfigs();
    int actual;
    for (int i = 0; i<200; ++i) {
        actual = addConfigByAidKid(aid, kid, config);
        EXPECT_EQ(expected, actual);
    }

    EXPECT_EQ(200, t_getAidKidCount());
    EXPECT_EQ(200, t_getEpConfigCount());

    actual = addConfigByAidKid(aid, kid, config);
    EXPECT_EQ(INDEX_OUT_OF_RANGE, actual);

}

TEST_F(TestEpConfig, findConfigByAidKid)
{
    int actual = resetAllConfigs();
    EXPECT_EQ(SUCCESS, actual);


    char aid[] = "A01020304";
    unsigned char kid = 0xAB;
    EpConfig    config;
    SET_STATUS_CHECK(config);
    SET_ZERO_AMOUT_ALLOWED(config);

    actual = addConfigByAidKid(aid, kid, config);
    EXPECT_EQ(SUCCESS, actual);

    EpConfigPtr p = findConfigByAidKid("", 0x00);
    EXPECT_EQ(NULL, p);

    p = findConfigByAidKid(aid, kid);
    EXPECT_TRUE(NULL != p);
    EXPECT_TRUE(IS_STATUS_CHECK(*p));
    EXPECT_TRUE(IS_ZERO_AMOUT_ALLOWED(*p));


    char aid2[] = "DEADBEEF";
    unsigned char kid2 = 0x01;
    EpConfig    config2;
    SET_STATUS_CHECK(config2);
    RESET_ZERO_AMOUT_ALLOWED(config2);

    actual = addConfigByAidKid(aid2, kid2, config2);
    EXPECT_EQ(SUCCESS, actual);

    EpConfigPtr p2 = findConfigByAidKid("", 0x00);
    EXPECT_EQ(NULL, p2);

    p2 = findConfigByAidKid(aid2, kid2);
    EXPECT_TRUE(NULL != p2);
    EXPECT_TRUE(IS_STATUS_CHECK(*p2));
    EXPECT_FALSE(IS_ZERO_AMOUT_ALLOWED(*p2));

}

TEST_F(TestEpConfig, findConfigByAidKid_2)
{
    int actual = resetAllConfigs();
    EXPECT_EQ(SUCCESS, actual);

    EpConfigPtr p = findConfigByAidKid("AB010101", 0x01);
    EXPECT_EQ(NULL, p);
}

TEST_F(TestEpConfig, findConfigByAidKid_3)
{
    int actual = resetAllConfigs();
    EXPECT_EQ(SUCCESS, actual);


    char aid[] = "A01020304";
    unsigned char kid = 0xAB;
    EpConfig    config;
    SET_STATUS_CHECK(config);
    SET_ZERO_AMOUT_ALLOWED(config);

    actual = addConfigByAidKid(aid, kid, config);
    EXPECT_EQ(SUCCESS, actual);

    EpConfigPtr p = findConfigByAidKid(aid, kid);
    EXPECT_TRUE(NULL != p);
    EXPECT_TRUE(IS_STATUS_CHECK(*p));
    EXPECT_TRUE(IS_ZERO_AMOUT_ALLOWED(*p));

    actual = resetAllConfigs();
    EXPECT_EQ(SUCCESS, actual);

    p = findConfigByAidKid(aid, kid);
    EXPECT_TRUE(NULL == p);
}

extern "C" {
    #include "EntryPoint/entryPoint.h"
}

TEST_F(TestEpConfig, loadConfigs)
{
    ep_init(&hal, "./test/Runner2/termsetting1/config.txt");
    int actual = resetAllConfigs();
    EXPECT_EQ(SUCCESS, actual);

    actual = loadConfigs("./test/Runner2/termsetting1/config.txt");
    EXPECT_EQ(SUCCESS, actual);

// TODO
    EpConfigPtr p;
    // p = findConfigByAidKid("A0000001523010", 0x06);
    //EXPECT_TRUE(NULL != p);

    p = findConfigByAidKid("UNKNOWN_AID", 0xFF);
    EXPECT_TRUE(NULL == p);
}

#endif// TEST_ENTRYPOINT_TEST_EPCONFIG_H_
