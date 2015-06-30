#ifndef _TEST_EPCOMBINATIONSELECTIONTESTS_H_
#define _TEST_EPCOMBINATIONSELECTIONTESTS_H_

#include "../BaseTest.h"

extern "C" {
    #include "EntryPoint/epCombinationSelection.h"
    #include "Base/err.h"
    #include "Base/debug.h"
}

class Test_CombinationSelection : public BaseTest {
public:
};

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _step1_Negative) {
    int actual = _step1(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _3_3_2_2) {
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
                            Return(SUCCESS)
                        );

    Ep ep;
    memset(&ep, 0x00, sizeof(Ep));

    int actual = _step1(&ep);
}

TEST_F(Test_CombinationSelection, _3_3_2_3) {
    string ppseResponseStr( "6F""2D"
                                "84" "0E" "325041592E5359532E4444463031"
                                "A5" "1B"
                                    "BF0C""18"
                                        "61""16"
                                            "4F""07""A0000000010001"
                                            "50""04""41505031"
                                            "9F2A""01""23"
                                            "87""01""01"
                                            "9000");
    unsigned char ppseResponse[255];
    int len = TestUtils::str2bcd(ppseResponseStr, ppseResponse);
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
                            DoAll(
                                SetArrayArgument<2>(ppseResponse, ppseResponse+len),
                                SetArgPointee<3>((unsigned long)len),
                                Return(SUCCESS)
                            )
                        );

    Ep ep;
    memset(&ep, 0x00, sizeof(Ep));

    int actual = _step1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step2, t_getNextStep());
}

TEST_F(Test_CombinationSelection, _3_3_2_3_otherwise) {
    string ppseResponseStr( "6A85");
    unsigned char ppseResponse[255];
    int len = TestUtils::str2bcd(ppseResponseStr, ppseResponse);
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
                            DoAll(
                                SetArrayArgument<2>(ppseResponse, ppseResponse+len),
                                SetArgPointee<3>((unsigned long)len),
                                Return(SUCCESS)
                            )
                        );

    Ep ep;
    memset(&ep, 0x00, sizeof(Ep));

    int actual = _step1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step3, t_getNextStep());
    EXPECT_EQ(0, ep.candidateListCount);
}

TEST_F(Test_CombinationSelection, _3_3_2_4) {
    Ep ep;
    memset(&ep, 0x00, sizeof(Ep));

    int actual = _step2(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step3, t_getNextStep());
    EXPECT_EQ(0, ep.candidateListCount);
}

TEST_F(Test_CombinationSelection, _3_3_2_5) {
    Ep ep;
    memset(&ep, 0x00, sizeof(Ep));
    EpConfig config;
    SET_EPIND_CLESS_APP_NOT_ALLOWED(config.indicators);
    addEpConfig(&ep, config);
    
    Fci fci;
    _incFciIssDataCounter(&fci);
    ep.fci = fci;

    int actual = _step2(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step3, t_getNextStep());
    EXPECT_EQ(0, ep.candidateListCount);
}

TEST_F(Test_CombinationSelection, _3_3_2_5_A) {
    Ep ep;
    memset(&ep, 0x00, sizeof(Ep));
    EpConfig config;
    addEpConfig(&ep, config);
    
    Fci fci;
    _incFciIssDataCounter(&fci);
    ep.fci = fci;

    int actual = _step2(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step3, t_getNextStep());
    EXPECT_EQ(0, ep.candidateListCount);
}






























TEST_F(Test_CombinationSelection, _step1) {
    string ppseResponseStr( "6F""2D"
                                "84" "0E" "325041592E5359532E4444463031"
                                "A5" "1B"
                                    "BF0C""18"
                                        "61""16"
                                            "4F""07""A0000000010001"
                                            "50""04""41505031"
                                            "9F2A""01""23"
                                            "87""01""01"
                                            "9000");
    unsigned char ppseResponse[255];
    int len = TestUtils::str2bcd(ppseResponseStr, ppseResponse);
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
                            DoAll(
                                SetArrayArgument<2>(ppseResponse, ppseResponse+len),
                                SetArgPointee<3>((unsigned long)len),
                                Return(SUCCESS)
                            )
                        );

    Ep ep;
    memset(&ep, 0x00, sizeof(Ep));

    int actual = _step1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step2, t_getNextStep());
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _step1_6A85) {
    string ppseResponseStr( "6A85");
    unsigned char ppseResponse[255];
    int len = TestUtils::str2bcd(ppseResponseStr, ppseResponse);
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
                            DoAll(
                                SetArrayArgument<2>(ppseResponse, ppseResponse+len),
                                SetArgPointee<3>((unsigned long)len),
                                Return(SUCCESS)
                            )
                        );

    Ep ep;
    memset(&ep, 0x00, sizeof(Ep));
    t_setNextStep(Step1);

    int actual = _step1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0, ep.candidateListCount);
    EXPECT_EQ(Step3, t_getNextStep());
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _step1_invalid) {
    string ppseResponseStr( "6A");
    unsigned char ppseResponse[255];
    int len = TestUtils::str2bcd(ppseResponseStr, ppseResponse);
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
                            DoAll(
                                SetArrayArgument<2>(ppseResponse, ppseResponse+len),
                                SetArgPointee<3>((unsigned long)len),
                                Return(SUCCESS)
                            )
                        );

    Ep ep;
    memset(&ep, 0x00, sizeof(Ep));
    t_setNextStep(Step1);
    
    int actual = _step1(&ep);
    
    EXPECT_EQ(SW_NOT_FOUND, actual);
    EXPECT_EQ(0, ep.candidateListCount);
    EXPECT_EQ(1, t_getNextStep());
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _step1_Multiple) {
    string ppseResponseStr( "6F""45"
                                "84" "0E" "325041592E5359532E4444463031"
                                "A5" "33"
                                    "BF0C""30"
                                        "61""16"
                                            "4F""07""A0000000010001"
                                            "50""04""41505031"
                                            "9F2A""01""23"
                                            "87""01""01"
                                        "61""16"
                                            "4F""07""A0000000020001"
                                            "50""04""41505031"
                                            "9F2A""01""24"
                                            "87""01""01"
                                            "9000");
    unsigned char ppseResponse[255];
    int len = TestUtils::str2bcd(ppseResponseStr, ppseResponse);
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
                            DoAll(
                                SetArrayArgument<2>(ppseResponse, ppseResponse+len),
                                SetArgPointee<3>((unsigned long)len),
                                Return(SUCCESS)
                            )
                        );

    Ep ep;
    memset(&ep, 0x00, sizeof(Ep));

    int actual = _step1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step2, t_getNextStep());
}

TEST_F(Test_CombinationSelection, _step2_Negative) {
    int actual = _step2(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

TEST_F(Test_CombinationSelection, _step2_3_3_2_4) {
    Ep ep;
    memset(&ep, 0x00, sizeof(Ep));
    int actual = _step2(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(3, t_getNextStep());
    EXPECT_EQ(0, ep.candidateListCount);
}


#endif// _TEST_EPCOMBINATIONSELECTIONTESTS_H_