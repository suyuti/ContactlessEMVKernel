/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_TEST_PROTOCOLACTIVATION_H_
#define MODULAR_TEST_PROTOCOLACTIVATION_H_

#include <EntryPoint/epCommon.h>
#include <Emv/candidateList.h>
#include "../BaseTest.h"

extern "C" {
    #include "Common/err.h"
    #include "EntryPoint/epProtocolActivation.h"
    #include "EntryPoint/epCommon.h"
    #include "EntryPoint/ttq.h"
};

class Test_ProtocolActivation : public BaseTest {
};

TEST_F(Test_ProtocolActivation, _3_2_1_1_negative) {
    int actual = _3_2_1_1(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

TEST_F(Test_ProtocolActivation, _3_2_1_1) {
    /*
     * Ep nesnesi olusturuldu.
     * Uzerinde iki konfigurasyon var. Test icin bunlarin indicatorlari set edildi ve
     * config data TTQ set edildi.
     *
     * Degisiklik olmayan akis sonucunda ep nesnesinin indicatorlari degismedigi gorludu.
     * Degisiklik akisinda indicatorlarin reset oldugu, indicator TTQlarin set edildigi goruldu.
     * */

    Ep ep;
    ep.epConfigsCount = 2;
    SET_EPIND_STATUS_CHECK_REQ(ep.epConfigs[0].indicators);
    SET_EPIND_STATUS_CHECK_REQ(ep.epConfigs[1].indicators);
    SET_MAGSTRIPE_SUPP(ep.epConfigs[0].configData.ttq);
    SET_MAGSTRIPE_SUPP(ep.epConfigs[1].configData.ttq);
    ep.candidateListCount = 2;
    ep.candidateList[0]._50[0] = '1';
    ep.candidateList[1]._50[0] = '2';

    EXPECT_TRUE(IS_EPIND_STATUS_CHECK_REQ(ep.epConfigs[0].indicators));
    EXPECT_TRUE(IS_EPIND_STATUS_CHECK_REQ(ep.epConfigs[1].indicators));
    EXPECT_TRUE(IS_MAGSTRIPE_SUPP(ep.epConfigs[0].configData.ttq));
    EXPECT_TRUE(IS_MAGSTRIPE_SUPP(ep.epConfigs[1].configData.ttq));

    //--------------------------------
    ep.restartFlag = SET;
    int actual = _3_2_1_1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    // be sure unchanged
    EXPECT_TRUE(IS_EPIND_STATUS_CHECK_REQ(ep.epConfigs[0].indicators));
    EXPECT_TRUE(IS_EPIND_STATUS_CHECK_REQ(ep.epConfigs[1].indicators));
    EXPECT_FALSE(IS_MAGSTRIPE_SUPP(ep.epConfigs[0].indicators.ttq));
    EXPECT_FALSE(IS_MAGSTRIPE_SUPP(ep.epConfigs[1].indicators.ttq));
    EXPECT_EQ(2, ep.candidateListCount);
    EXPECT_EQ('1', ep.candidateList[0]._50[0]);
    EXPECT_EQ('2', ep.candidateList[1]._50[0]);

    //--------------------------------
    ep.restartFlag = RESET;
    ep.startPoint = StartedAtA;
    actual = _3_2_1_1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    // be sure unchanged
    EXPECT_TRUE(IS_EPIND_STATUS_CHECK_REQ(ep.epConfigs[0].indicators));
    EXPECT_TRUE(IS_EPIND_STATUS_CHECK_REQ(ep.epConfigs[1].indicators));
    EXPECT_FALSE(IS_MAGSTRIPE_SUPP(ep.epConfigs[0].indicators.ttq));
    EXPECT_FALSE(IS_MAGSTRIPE_SUPP(ep.epConfigs[1].indicators.ttq));
    EXPECT_EQ(0, ep.candidateListCount);
    EXPECT_EQ(0x00, ep.candidateList[0]._50[0]);
    EXPECT_EQ(0x00, ep.candidateList[1]._50[0]);

    // set again
    ep.candidateListCount = 2;
    ep.candidateList[0]._50[0] = '1';
    ep.candidateList[1]._50[0] = '2';

    //--------------------------------

    ep.restartFlag      = RESET;
    ep.startPoint       = StartedAtB;
    actual              = _3_2_1_1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    // be sure they are reset
    EXPECT_FALSE(IS_EPIND_STATUS_CHECK_REQ(ep.epConfigs[0].indicators));
    EXPECT_FALSE(IS_EPIND_STATUS_CHECK_REQ(ep.epConfigs[1].indicators));
    EXPECT_TRUE(IS_MAGSTRIPE_SUPP(ep.epConfigs[0].indicators.ttq));
    EXPECT_TRUE(IS_MAGSTRIPE_SUPP(ep.epConfigs[1].indicators.ttq));
    EXPECT_EQ(0, ep.candidateListCount);
    EXPECT_EQ(0x00, ep.candidateList[0]._50[0]);
    EXPECT_EQ(0x00, ep.candidateList[1]._50[0]);
}

#endif  // MODULAR_TEST_PROTOCOLACTIVATION_H_
