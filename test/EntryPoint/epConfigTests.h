/*
    Copyright 2015
*/

#ifndef TEST_ENTRYPOINT_TEST_EPCONFIG_H_
#define TEST_ENTRYPOINT_TEST_EPCONFIG_H_

#include "../BaseTest.h"
using namespace std;


extern "C" {
    #include "EntryPoint/entryPoint.h"
    #include "EntryPoint/epConfig.h"
    #include "Base/err.h"
}

class TestEpConfig : public BaseTest {
};

//-----------------------------------------------------------------------------

TEST_F(TestEpConfig, clearEpConfigData)
{
    EpConfigData epConfigData;

    SET_STATUS_CHECK(epConfigData);

    int actual = clearEpConfigData(&epConfigData);

    EXPECT_EQ(SUCCESS, actual);
    EXPECT_TRUE(IS_STATUS_CHECK(epConfigData) == FALSE);
}

//-----------------------------------------------------------------------------

TEST_F(TestEpConfig, clearEpConfigDataNegative)
{
    int actual = clearEpConfigData(NULL);

    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestEpConfig, clearEpConfigs)
{
    Ep ep;
    int actual = clearEpConfigs(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0, ep.epConfigsCount);
}

//-----------------------------------------------------------------------------

TEST_F(TestEpConfig, clearEpConfigsNegative)
{
    int actual = clearEpConfigs(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestEpConfig, addEpConfig)
{
    Ep          ep;
    EpConfig    epConfig;

    sprintf(epConfig.aid, "TEST_AID");
    epConfig.kid = 0xAB;
    SET_STATUS_CHECK(epConfig.configData);

    int actual = addEpConfig(&ep, epConfig);

    EXPECT_EQ(SUCCESS,  actual);
    EXPECT_EQ(1,        ep.epConfigsCount);
    EXPECT_EQ(0xAB,     ep.epConfigs[0].kid);
    EXPECT_TRUE(IS_STATUS_CHECK(ep.epConfigs[0].configData));
}

//-----------------------------------------------------------------------------

TEST_F(TestEpConfig, addEpConfigNegative)
{
    Ep          ep;
    EpConfig    epConfig;

    int actual = addEpConfig(NULL, epConfig);

    EXPECT_EQ(NULL_PARAMETER,  actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestEpConfig, findEpConfig)
{
    Ep          ep;
    EpConfig    epConfig;

    clearEntryPoint(&ep);

    sprintf(epConfig.aid, "TEST_AID_AB");
    epConfig.kid = 0xAB;
    SET_STATUS_CHECK(epConfig.configData);
    addEpConfig(&ep, epConfig);
    EXPECT_EQ(1, ep.epConfigsCount);

    sprintf(epConfig.aid, "TEST_AID_AC");
    epConfig.kid = 0xAC;
    SET_STATUS_CHECK(epConfig.configData);
    addEpConfig(&ep, epConfig);

    EXPECT_EQ(2, ep.epConfigsCount);

    int actual = findEpConfig(&ep, "TEST_AID_AB", 0xAB, &epConfig);

    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0xAB, epConfig.kid);

    actual = findEpConfig(&ep, "TEST_AID_UNKNOWN", 0xFF, &epConfig);

    EXPECT_EQ(OBJECT_NOT_FOUND, actual);
}

//-----------------------------------------------------------------------------

TEST_F(TestEpConfig, findEpConfigNegative)
{
    Ep          ep;
    EpConfig    epConfig;

    int actual = findEpConfig(&ep, "TEST_AID_AB", 0xAB, NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);

    actual = findEpConfig(NULL, "TEST_AID_AB", 0xAB, &epConfig);
    EXPECT_EQ(NULL_PARAMETER, actual);

    actual = findEpConfig(NULL, "TEST_AID_AB", 0xAB, NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/*
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
*/
#endif// TEST_ENTRYPOINT_TEST_EPCONFIG_H_
