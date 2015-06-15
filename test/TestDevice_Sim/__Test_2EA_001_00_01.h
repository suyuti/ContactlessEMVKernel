#ifndef _TEST_2EA_001_00_01_H_
#define _TEST_2EA_001_00_01_H_

#include "BaseTest.h"
#include "ConfigFactory/configFactory.h"

extern "C" {
    #include "../../src/Base/general.h"
}

class Test_2EA_001_00_01 : public BaseTest {
public:
    Test_2EA_001_00_01() : BaseTest("2EA_001_00_01") {};
    virtual ~ Test_2EA_001_00_01() {};

};

TEST_F(Test_2EA_001_00_01, case01) {
    TerminalConfigs config = TerminalConfigs::TerminalConfigBuilder()
                            .Build();
    addCommandResponse("","");
    executeTest();
    EXPECT_EQ(0,0);
}

#endif //_TEST_2EA_001_00_01_H_