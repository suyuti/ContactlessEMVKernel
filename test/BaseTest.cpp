#include "BaseTest.h"
#include "Config/ConfigFactory/termConfig01.h"
#include "Config/ConfigFactory/termConfig02.h"

void BaseTest::useTerminalConfig(TerminalConfigs::Configurations configType)
{
    switch(configType) {
        case TerminalConfigs::Config01:
            terminalConfig = TerminalConfig01().generate();
        break;
        case TerminalConfigs::Config02:
            terminalConfig = TerminalConfig02().generate();
        break;
    }
}


void BaseTest::addCommandResponse(string cmd, string resp)
{

}

void BaseTest::clearCommandResponse()
{

}

void BaseTest::executeTest() 
{

}