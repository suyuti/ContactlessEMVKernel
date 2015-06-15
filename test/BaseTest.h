#ifndef _BASE_TEST_H_
#define _BASE_TEST_H_

#include <string>
#include <vector>
#include <utility>
#include <gtest/gtest.h>

#include "Config/ConfigFactory/configFactory.h"
extern "C" {
    #include "../src/Base/kernel.h"
}

using namespace std; 

typedef pair<string, string>        Command_Response;
typedef vector<Command_Response>    Command_Response_Pairs;

class BaseTest : public ::testing::Test {
private:
    string                  name;
    string                  objective;





    Command_Response_Pairs  cr_pairs;

protected:
    TerminalConfigs         terminalConfig;

protected:
    BaseTest() {};
    BaseTest(string name)   { setName(name); };
    virtual ~BaseTest()     {};

    virtual void SetUp()    { 
        initializeEmvKernel();
        int kernelVersion = getVersion();
        cout << "Kernel version: " << kernelVersion << endl;
        clearCommandResponse();   
    }
    virtual void TearDown() {}

    void initializeEmvKernel() {
        initialize();
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
