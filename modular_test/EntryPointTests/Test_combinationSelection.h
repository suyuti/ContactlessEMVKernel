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
    #include "Common/aid.h"
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
/*
 *
 * For each reader Combination {AID – Kernel ID} supported by the reader for
 * which the ‘Contactless Application Not Allowed’ indicator is 0, Entry Point
 * shall process each Directory Entry (Tag '61') from the FCI
 *
 * */

TEST_F(Test_CombinationSelection, _3_3_2_5_there_is_no_cless_app)
{
    Ep ep;
    clearEntryPoint(&ep);

    EntryPointConfigs::EntryPointConfigBuilder()
            .WithAid("A00001")
            .WithClessAppNotAllowed()  // <- Contactless application not allowed
            .Build()
            .copy(&(ep.epConfigs[0]));
    ep.epConfigsCount++;

    EntryPointConfigs::EntryPointConfigBuilder()
            .WithAid("A00002")
            .WithClessAppNotAllowed()  // <- Contactless application not allowed
            .Build()
            .copy(&(ep.epConfigs[1]));
    ep.epConfigsCount++;

    // Two entry point configuration those have Contactless Application Not Allowed added.


    int actual = _3_3_2_5(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(Step3, t_getNextStep());
    EXPECT_EQ(0, ep.candidateListCount);
}

//-----------------------------------------------------------------------------
/**
 *
 * Entry Point shall examine the format of the ADF Name of the Directory Entry.
 *
 * IF the ADF Name is missing
 * OR is not coded according to [EMV 4.2 Book 1], section 12.2.1,
 * THEN Entry Point shall proceed with the next Directory Entry.
 *
 * */

TEST_F(Test_CombinationSelection, _3_3_2_5_A_without_adfName)
{
    Ep ep;

    clearEntryPoint(&ep);

    EntryPointConfigs::EntryPointConfigBuilder()
            .WithAid("A00001")
            .Build()
            .copy(&(ep.epConfigs[0]));
    ep.epConfigsCount++;

    FciFactory::FciBuilder()
            .WithDirectoryEntry(
                    DirectoryEntryFactory::DirectoryEntryBuilder()
                            // .WithADFName("A00001")              // <- without ADFName
                            //.WithKernelIdentifier(1)
                            .WithApplicationLabel("LABEL")
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

TEST_F(Test_CombinationSelection, _3_3_2_5_A_adfName_misformatted_smallAdfName)
{
    Ep ep;

    clearEntryPoint(&ep);

    EntryPointConfigs::EntryPointConfigBuilder()
            .WithAid("A00001")
            .Build()
            .copy(&(ep.epConfigs[0]));
    ep.epConfigsCount++;

    FciFactory::FciBuilder()
            .WithDirectoryEntry(
                    DirectoryEntryFactory::DirectoryEntryBuilder()
                            .WithADFName("A00001")              // <- ADFName must be min 5 bytes len
                            .WithApplicationLabel("LABEL")
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

TEST_F(Test_CombinationSelection, _3_3_2_5_A_adfName_misformatted_longAdfName)
{
    Ep ep;

    clearEntryPoint(&ep);

    EntryPointConfigs::EntryPointConfigBuilder()
            .WithAid("A00001")
            .Build()
            .copy(&(ep.epConfigs[0]));
    ep.epConfigsCount++;

    FciFactory::FciBuilder()
            .WithDirectoryEntry(
                    DirectoryEntryFactory::DirectoryEntryBuilder()
                            .WithADFName("A00102030405060708090A0B0C0D0E0F111213") // <- ADFName must be max 16 bytes len
                            .WithApplicationLabel("LABEL")
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

/*
 *
 * Entry Point shall examine whether the ADF Name matches the AID of the reader Combination.
 *
 * IF        the ADF Name has the same length and value as the AID (full match),
 * OR        the ADF Name begins with the AID (partial match),
 * THEN      the ADF Name matches the AID and the AID is referred to as the “matching AID”.
 * OTHERWISE Entry Point shall return to bullet A and proceed with the next Directory Entry.
 *
 * */

TEST_F(Test_CombinationSelection, _3_3_2_5_B_fullMatch)
{
    Ep ep;

    clearEntryPoint(&ep);

    EntryPointConfigs::EntryPointConfigBuilder()
            .WithAid("A102030405")
            .Build()
            .copy(&(ep.epConfigs[0]));
    ep.epConfigsCount++;

    FciFactory::FciBuilder()
            .WithDirectoryEntry(
                    DirectoryEntryFactory::DirectoryEntryBuilder()
                            .WithADFName("A102030405")
                            .WithApplicationLabel("LABEL")
                            .Build()
                            .getData()
            )
            .Build()
            .copy(&ep.fci);


    int actual = _3_3_2_5(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(5, t_getMatchingAidLen());
    unsigned char expectedMatchingAid[] = {0x05, 0xA1, 0x02, 0x03, 0x04, 0x05};
    EXPECT_EQ(0, memcmp(t_getMatchingAid(), expectedMatchingAid, sizeof(expectedMatchingAid)));

    //EXPECT_EQ(Step3, t_getNextStep());
    //EXPECT_EQ(0, ep.candidateListCount);

}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _3_3_2_5_B_partialMatch)
{
    Ep ep;

    clearEntryPoint(&ep);

    EntryPointConfigs::EntryPointConfigBuilder()
            .WithAid("A102030405")
            .Build()
            .copy(&(ep.epConfigs[0]));
    ep.epConfigsCount++;

    FciFactory::FciBuilder()
            .WithDirectoryEntry(
                    DirectoryEntryFactory::DirectoryEntryBuilder()
                            .WithADFName("A102030405AABBCCDDEEFF")    // <- Adf begins with AID
                            .WithApplicationLabel("LABEL")
                            .Build()
                            .getData()
            )
            .Build()
            .copy(&ep.fci);


    int actual = _3_3_2_5(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(5, t_getMatchingAidLen());
    unsigned char expectedMatchingAid[] = {0x05, 0xA1, 0x02, 0x03, 0x04, 0x05};
    EXPECT_EQ(0, memcmp(t_getMatchingAid(), expectedMatchingAid, sizeof(expectedMatchingAid)));

    //EXPECT_EQ(Step3, t_getNextStep());
    //EXPECT_EQ(0, ep.candidateListCount);

}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _3_3_2_5_B_NoMatch)
{
    Ep ep;

    clearEntryPoint(&ep);

    EntryPointConfigs::EntryPointConfigBuilder()
            .WithAid("A102030405")
            .Build()
            .copy(&(ep.epConfigs[0]));
    ep.epConfigsCount++;

    FciFactory::FciBuilder()
            .WithDirectoryEntry(
                    DirectoryEntryFactory::DirectoryEntryBuilder()
                            .WithADFName("AABBCCDDEEFF001122334455")    // <- Adf does not match with AID
                            .WithApplicationLabel("LABEL")
                            .Build()
                            .getData()
            )
            .Build()
            .copy(&ep.fci);


    int actual = _3_3_2_5(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0, t_getMatchingAidLen());
    // TODO step?

    //EXPECT_EQ(Step3, t_getNextStep());
    EXPECT_EQ(0, ep.candidateListCount);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _3_3_2_5_C_9F2A_absent_fullMatch)
{
    Ep ep;

    clearEntryPoint(&ep);

    EntryPointConfigs::EntryPointConfigBuilder()
            .WithAid("A000000004")
            .Build()
            .copy(&(ep.epConfigs[0]));
    ep.epConfigsCount++;

    FciFactory::FciBuilder()
            .WithDirectoryEntry(
                    DirectoryEntryFactory::DirectoryEntryBuilder()
                            .WithADFName("A000000004")
                            .WithApplicationLabel("LABEL")
                            .Build()
                            .getData()
            )
            .Build()
            .copy(&ep.fci);


    int actual = _3_3_2_5(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(5, t_getMatchingAidLen());
    EXPECT_EQ(MastercardDefaultKernelId, t_getRequestedKernelId());
    // TODO step?
    //EXPECT_EQ(Step3, t_getNextStep());
    EXPECT_EQ(0, ep.candidateListCount);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _3_3_2_5_C_9F2A_absent_partialMatch)
{
    Ep ep;

    clearEntryPoint(&ep);

    EntryPointConfigs::EntryPointConfigBuilder()
            .WithAid("A000000004")
            .Build()
            .copy(&(ep.epConfigs[0]));
    ep.epConfigsCount++;

    FciFactory::FciBuilder()
            .WithDirectoryEntry(
                    DirectoryEntryFactory::DirectoryEntryBuilder()
                            .WithADFName("A0000000040101")
                            .WithApplicationLabel("LABEL")
                            .Build()
                            .getData()
            )
            .Build()
            .copy(&ep.fci);


    int actual = _3_3_2_5(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(5, t_getMatchingAidLen());
    EXPECT_EQ(MastercardDefaultKernelId, t_getRequestedKernelId());
    // TODO step?
    //EXPECT_EQ(Step3, t_getNextStep());
    EXPECT_EQ(0, ep.candidateListCount);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CombinationSelection, _3_3_2_5_C_9F2A_exists_but_zero_len)
{
    Ep ep;

    clearEntryPoint(&ep);

    EntryPointConfigs::EntryPointConfigBuilder()
            .WithAid("A000000152")
            .Build()
            .copy(&(ep.epConfigs[0]));
    ep.epConfigsCount++;

    FciFactory::FciBuilder()
            .WithDirectoryEntry(
                    DirectoryEntryFactory::DirectoryEntryBuilder()
                            .WithADFName("A0000001520101")
                            .WithKernelIdentifierWithZeroLen()
                            .WithApplicationLabel("DISCOVER")
                            .Build()
                            .getData()
            )
            .Build()
            .copy(&ep.fci);


    int actual = _3_3_2_5(&ep);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(5, t_getMatchingAidLen());
    EXPECT_EQ(DiscoverDefaultKernelId, t_getRequestedKernelId());
    // TODO step?
    //EXPECT_EQ(Step3, t_getNextStep());
    EXPECT_EQ(0, ep.candidateListCount);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // MODULAR_TEST_COMBINATIONSELECTION_H_