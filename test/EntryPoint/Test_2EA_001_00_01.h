#ifndef _TEST_2EA_001_00_H_
#define _TEST_2EA_001_00_H_

#include "../BaseTest.h"


/**
    Objective:
        To ensure that when Autorun is ‘No’, or Autorun option not supported, 
        and a single type of transaction is supported, the Amount Authorized entered 
        in the terminal is correctly retrieved in the kernel data.
    
    Reference BOOK A/B:
        Book A – version 2.3 - Requirement 8.1.1.3
    
    Procedure:
        Entry Point transactions are performed for [Termsetting2] with different LT settings
**/
//-------------------------------------------------------------------------------------------------

class Test_2EA_001_00 : public BaseTest {
public:
    //Test_2EA_001_00() : BaseTest("2EA_001_00") {
    //    useTerminalConfig(TerminalConfigs::Config01);
    //};
    //virtual ~Test_2EA_001_00() {};
};

//-------------------------------------------------------------------------------------------------
/**
    Condition: 
        Entry Point transaction is performed with [LTsetting1.1] with an Amount Authorized of 10.
    Pass Criteria: 
        Case01: The LT shall receive in the GET PROCESSING OPTIONS data field: Amount Authorized = 10
        Case01: The LT shall receive in the GET PROCESSING OPTIONS data field: Transaction Type = value supported for the configuration 
        Case01: The LT shall receive in the GET PROCESSING OPTIONS data field: Amount Other = 0
**/

TEST_F(Test_2EA_001_00, case01) {
    InSequence s1;
    EXPECT_CALL(halApi, rfOpen()).Times(Exactly(1));
    EXPECT_CALL(halApi, cardOpen()).Times(Exactly(1));
    EXPECT_CALL(halApi, cardReset()).Times(Exactly(1)).WillOnce(Return(SUCCESS));

    // From Kernel: 00A404000E325041592E5359532E444446303100
    char selectPPSEResponse[]   = "6F2D840E325041592E5359532E4444463031A51BBF0C1861164F07A00000000100015004415050319F2A0123870101";
    unsigned char ppseResponse[255];
    int len = TestUtils::str2bcd(selectPPSEResponse, ppseResponse);
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
                            DoAll(
                                SetArrayArgument<2>(ppseResponse, ppseResponse+len),
                                SetArgPointee<3>((unsigned long)len),
                                Return(SUCCESS)
                            )
                        );
                        /*

    // From Kernel: 00A4040007A000000001000100
    char selectAIPResponse[]    = "6F2A8407A0000000010001A51F5004415050318701019F3813D1029F66049F02069F03069C019F37049F2A08";
    EXPECT_CALL(halApi, cardTransmit(isSelectAIP("A0000000010001"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
        Return(SUCCESS));

    // From Kernel : Gpo: 80A8000021831F0100000000000000000000100000000000000030326449000000000000000000
    char gpoResponse[] = "771DD40A030000000000FFFF0000D50F030500000000000000000000000000";
    EXPECT_CALL(halApi, cardTransmit(isApdu("80A8000021831F0100000000000000000000100000000000000030326449000000000000000000"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
        Return(SUCCESS));

    */
    int err = initialize("./test/Runner2/termsetting1");
    EXPECT_EQ(SUCCESS, err);

    err = start(10, 0);
    EXPECT_EQ(SUCCESS, err);
}


//-------------------------------------------------------------------------------------------------
/**
    Condition: 
        Entry Point transaction is performed with[ LTsetting1.2] with an Amount Authorized of 75.
    Pass Criteria: 
        Case02: The LT shall receive in the GET PROCESSING OPTIONS data field: Amount Authorized = 75 
        Case02: The LT shall receive in the GET PROCESSING OPTIONS data field: Transaction Type = value supported for the configuration 
        Case02: The LT shall receive in the GET PROCESSING OPTIONS data field: Amount Other = 0
**/
TEST_F(Test_2EA_001_00, case02) {
    /*
    InSequence s1;
    EXPECT_CALL(halApi, cardOpen()).Times(Exactly(1));
    EXPECT_CALL(halApi, cardReset()).Times(Exactly(1)).WillOnce(Return(SUCCESS));

    // From Kernel: 00A404000E325041592E5359532E4444463031
    char selectPPSEResponse[]   = "6F2D840E325041592E5359532E4444463031A51BBF0C1861164F07A00000000200025004415050329F2A0122870101";
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
                            DoAll(
                                SetArrayArgument<2>(selectPPSEResponse, selectPPSEResponse+sizeof(selectPPSEResponse)),
                                SetArgPointee<3>((unsigned long)sizeof(selectPPSEResponse)),
                                Return(SUCCESS)
                            )
                        );

    // From Kernel: 00A4040007A0000000020002
    char selectAIPResponse[]    = "6F2A8407A0000000020002A51F5004415050328701019F3813D1029F66049F02069F03069C019F37049F2A08";
    EXPECT_CALL(halApi, cardTransmit(isSelectAIP("A0000000020002"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
        Return(SUCCESS));

    // From Kernel : Gpo: 80A8000021831F0100000000000000000000750000000000000075769326000000000000000000
    char gpoResponse[] = "771DD40A030000000000FFFF0000D50F030500000000000000000000000000";
    EXPECT_CALL(halApi, cardTransmit(isApdu("80A8000021831F0100000000000000000000750000000000000075769326000000000000000000"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
        Return(SUCCESS));


    initialize();
    */
}

//-------------------------------------------------------------------------------------------------
/**
    Condition: 
        Entry Point transaction is performed with[ LTsetting1.97] with an Amount Authorized of 45.
    Pass Criteria: 
        Case03: The LT shall receive in the GET PROCESSING OPTIONS data field: Amount Authorized = 45 
        Case03: The LT shall receive in the GET PROCESSING OPTIONS data field: Transaction Type = value supported for the configuration 
        Case03: The LT shall receive in the GET PROCESSING OPTIONS data field: Amount Other = 0
**/
TEST_F(Test_2EA_001_00, case03) {
}

#endif// _TEST_2EA_001_00_H_
