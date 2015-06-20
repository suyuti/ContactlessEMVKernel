#ifndef _BASE_TEST_H_
#define _BASE_TEST_H_

#include <string>
#include <vector>
#include <utility>
#include <gtest/gtest.h>

#include "Config/ConfigFactory/configFactory.h"
#include "Mockups/mockHal.h"
extern "C" {
    #include "../src/Base/kernel.h"
    #include "../src/Base/err.h"
    #include "./defaultHalImpl.h"
}

#include "matchers.h"

using namespace std; 
using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::SetArgPointee;
using ::testing::SetArrayArgument;
using ::testing::WithArg;
using ::testing::Args;
using ::testing::ElementsAre;
using ::testing::ElementsAreArray;
using ::testing::NotNull;
using ::testing::Gt;
using ::testing::Ge;
using ::testing::InSequence;
using ::testing::MakeMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;
using ::testing::InSequence;


typedef pair<string, string>        Command_Response;
typedef vector<Command_Response>    Command_Response_Pairs;

class BaseTest : public ::testing::Test {
private:
    string                      name;
    string                      objective;




    Command_Response_Pairs  cr_pairs;

protected:
    TerminalConfigs         terminalConfig;
    StrictMockHalFunctions      halApi;

protected:
    BaseTest() {
        init();
    };
    BaseTest(string name)  { 
        setName(name); 
        init();
    };

    void init();
    virtual ~BaseTest()     {};

    virtual void SetUp()    { 
        ON_CALL(halApi, readConfig(isConfig("A000101_22"), _)).WillByDefault(Return(SUCCESS));
        ON_CALL(halApi, readConfig(isConfig("A000101_23"), _)).WillByDefault(Return(SUCCESS));

        //initializeEmvKernel();
        //int kernelVersion = getVersion();
        //cout << "Kernel version: " << kernelVersion << endl;
        clearCommandResponse();   
    }
    virtual void TearDown() {}

    void initializeEmvKernel() {
        initialize(".");
    }


    void useTerminalConfig(TerminalConfigs::Configurations configType);
    void addCommandResponse(string cmd, string resp);
    void clearCommandResponse();

public:
    void    setName(string& name)               { this->name = name;            };
    string  getName()                           { return this->name;            };
    void    setObjective(string& objective)     { this->objective = objective;  };
    string  getObjective()                      { return this->objective;       };

    void executeTest();

};

#endif// _BASE_TEST_H_
