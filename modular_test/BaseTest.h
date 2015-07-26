/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_TEST_BASETEST_H_
#define MODULAR_TEST_BASETEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <utility>

#include "Mockups/mockHal.h"
#include "./testUtils.h"

extern "C" {
    #include "../modular_src/Common/err.h"
    #include "../modular_src/Common/common.h"
    #include "../modular_src/Common/hal.h"
    #include "./defaultHalImpl.h"
}

#include "./matchers.h"
#include "./testUtils.h"

using namespace EmvTest;
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

 protected:
    HalInterfaces               hal;
    // EntryPointConfigs         terminalConfig;
    StrictMockHalFunctions      halApi;

 protected:
    BaseTest() {
        init();
    }

    BaseTest(string name)  {
        setName(name);
        init();
    }

    void init();
    virtual ~BaseTest()     {}

    virtual void SetUp()    {
        ON_CALL(halApi, readConfig(isConfig("A000101_22"), _)).WillByDefault(Return(SUCCESS));
        ON_CALL(halApi, readConfig(isConfig("A000101_23"), _)).WillByDefault(Return(SUCCESS));
    }
    virtual void TearDown() {}

    void initializeEmvKernel() {
        // initialize(".");
    }


    // void useTerminalConfig(EntryPointConfigs::Configurations configType);
    // void addCommandResponse(string cmd, string resp);
    // void clearCommandResponse();

 public:
    void    setName(const string& name)               { this->name = name;            }
    string  getName()                           { return this->name;            }
    void    setObjective(const string& objective)     { this->objective = objective;  }
    string  getObjective()                      { return this->objective;       }

    void executeTest();
};

#endif  // MODULAR_TEST_BASETEST_H_
