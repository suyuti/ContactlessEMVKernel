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

void BaseTest::init() {
    setCardOpen(&mockCardOpen);
    setCardReset(&mockCardReset);
    setCardClose(&mockCardClose);
    setCardTransmit(&mockCardTransmit);
    //setReadConfig(&mockReadConfig);
    setFileOpen(&defaultFileOpen);
    setFileClose(&defaultFileClose);
    setFileRead(&defaultFileRead);
    setGetFileSize(&defaultGetFileSize);
    setAllocate(&defaultAllocate);
    setRelease(&defaultRelease);
    setGenUnPredNum(&defaultGenUnPredNum);

    hal.card_open       = &defaultCard_open;
    hal.card_close      = &defaultCard_close;
    hal.card_reset      = &defaultCard_reset;
    hal.card_transmit   = &defaultCard_transmit;
    hal.fileOpen        = &defaultFileOpen;
    hal.fileClose       = &defaultFileClose;
    hal.fileRead        = &defaultFileRead;
    hal.getFileSize     = &defaultGetFileSize;
    hal.allocate        = &defaultAllocate;
    hal.release         = &defaultRelease;
    hal._genUnPredNum   = &defaultGenUnPredNum;
}
