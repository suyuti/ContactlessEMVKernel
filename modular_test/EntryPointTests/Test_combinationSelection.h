/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_TEST_COMBINATIONSELECTION_H_
#define MODULAR_TEST_COMBINATIONSELECTION_H_

#include <EntryPoint/epCommon.h>
#include "../BaseTest.h"
#include "../Factories/EntryPointConfigFactory.h"
#include "../Factories/FciFactory.h"
#include "../Factories/DirectoryEntryFactory.h"

extern "C" {
    #include "Common/err.h"
    #include "EntryPoint/epCombinationSelection.h"
};

class Test_CombinationSelection : public BaseTest {
};

TEST_F(Test_CombinationSelection, epCombinationSelection_Negative)
{
    int actual = epCombinationSelection(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, 3_3_2_1_Negative)
{
    int actual = _3_3_2_1(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, 3_3_2_1)
{
    Ep ep;
    clearEntryPoint(&ep);

    ep.startPoint = StartedAtA;

    int actual = _3_3_2_1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step1, t_getNextStep());      // be sure unchanged


    ep.startPoint = StartedAtC;
    actual = _3_3_2_1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step3, t_getNextStep());

    // TODO

}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _step1_Negative)
{
    int actual = _step1(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _step1)
{
    Ep ep;
    clearEntryPoint(&ep);

    InSequence s1;
    char            selectPPSEResponse[]   = "6F""2D"
                                                "840E""325041592E5359532E4444463031A51B"
                                                "BF0C""18"
                                                    "61""16"
                                                        "4F""07"   "A0000000010001"
                                                        "50""04"   "41505031"
                                                        "9F2A""01" "23"
                                                        "87""01"   "01"
                                             "9000";
    unsigned char   selectPPSEResponseBCD[255];
    int             len = EmvTest::TestUtils::str2bcd(selectPPSEResponse, selectPPSEResponseBCD);
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
            .Times(Exactly(1))
            .WillOnce(
                    DoAll(
                            SetArrayArgument<2>(selectPPSEResponseBCD, selectPPSEResponseBCD + len),
                            SetArgPointee<3>((unsigned long)len),
                            Return(SUCCESS)));


    int actual = _step1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step2, t_getNextStep());
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _step1_PPSE_SWNot_9000)
{
    Ep ep;
    clearEntryPoint(&ep);

    InSequence s1;
    char            selectPPSEResponse[]   = "6A81";
    unsigned char   selectPPSEResponseBCD[255];
    int             len = EmvTest::TestUtils::str2bcd(selectPPSEResponse, selectPPSEResponseBCD);
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
            .Times(Exactly(1))
            .WillOnce(
                    DoAll(
                            SetArrayArgument<2>(selectPPSEResponseBCD, selectPPSEResponseBCD + len),
                            SetArgPointee<3>((unsigned long)len),
                            Return(SUCCESS)));


    int actual = _step1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step3, t_getNextStep());
    EXPECT_EQ(0, ep.candidateListCount);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _step1_3_3_2_4)
{
    Ep ep;
    clearEntryPoint(&ep);

    InSequence s1;
    char            selectPPSEResponse[]   = "6F""10"
            "840E""325041592E5359532E4444463031A51B"
            "9000";
    unsigned char   selectPPSEResponseBCD[255];
    int             len = EmvTest::TestUtils::str2bcd(selectPPSEResponse, selectPPSEResponseBCD);
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
            .Times(Exactly(1))
            .WillOnce(
                    DoAll(
                            SetArrayArgument<2>(selectPPSEResponseBCD, selectPPSEResponseBCD + len),
                            SetArgPointee<3>((unsigned long)len),
                            Return(SUCCESS)));


    int actual = _step1(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step2, t_getNextStep());
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _3_3_2_5)
{
    Ep ep;

    clearEntryPoint(&ep);

    EntryPointConfigs config = EntryPointConfigs::EntryPointConfigBuilder()
            .WithAid("A00001")
            .WithClessAppNotAllowed(false)
            .Build();
    config.copy(&(ep.epConfigs[0]));
    ep.epConfigsCount++;

    FciFactory::FciBuilder()
            .WithDirectoryEntry(
                    DirectoryEntryFactory::DirectoryEntryBuilder()
                            .WithADFName("A00001")
                            .WithKernelIdentifier(1)
                            .WithApplicationLabel("LABEL")
                            .Build()
                            .getData()
            )
            .WithDirectoryEntry(
                    DirectoryEntryFactory::DirectoryEntryBuilder()
                            .WithADFName("A00002")
                            .WithKernelIdentifier(2)
                            .WithApplicationLabel("LABEL2")
                            .Build()
                            .getData()
            )
            .WithDirectoryEntry(
                    DirectoryEntryFactory::DirectoryEntryBuilder()
                            .WithADFName("A00003")
                            .WithKernelIdentifier(3)
                            .WithApplicationLabel("LABEL2")
                            .Build()
                            .getData()
            )
    .Build()
    .copy(&ep.fci);


    int actual = _3_3_2_5(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step3, t_getNextStep());
    EXPECT_EQ(0, ep.candidateListCount);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _3_3_2_5_A)
{

}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // MODULAR_TEST_COMBINATIONSELECTION_H_