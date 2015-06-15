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
    Test_2EA_001_00() : BaseTest("2EA_001_00") {
        useTerminalConfig(TerminalConfigs::Config01);
    };
    virtual ~Test_2EA_001_00() {};
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
