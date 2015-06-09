#ifndef _TERM_CONFIG_DEFAULT_H_
#define _TERM_CONFIG_DEFAULT_H_

/*
Ref:
    EMVCo Type Approval Book A Book B Test Cases
    Annex A
    Terminal Settings Definitions 
*/
#include "configFactory.h"
extern "C" {
    #include "../../../src/Base/base.h"
}
class TerminalConfigDefault {
public:
    virtual TerminalConfigs generate(string kid = "", string aid = "", TrnxTypes trnx = None) = 0;
protected:
    virtual TerminalConfigs generateSet1();
    virtual TerminalConfigs generateSet2();
    virtual TerminalConfigs generateSet3();
    virtual TerminalConfigs generateSet4();
    virtual TerminalConfigs generateSet5();
    virtual TerminalConfigs generateSet6();
    virtual TerminalConfigs generateSet7();
    virtual TerminalConfigs generateSet8();
    virtual TerminalConfigs generateSet9();
};

#endif// _TERM_CONFIG_DEFAULT_H_
