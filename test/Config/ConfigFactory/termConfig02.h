#ifndef _TERM_CONFIG_02_H_
#define _TERM_CONFIG_02_H_

#include "termConfigDefault.h"

class TerminalConfig02 : public TerminalConfigDefault {
public:
    virtual TerminalConfigs generate(string kid = "", string aid = "", TrnxTypes trnx = None);
protected:
/*    virtual TerminalConfigs generateSet1();
    virtual TerminalConfigs generateSet2();
    virtual TerminalConfigs generateSet3();
    virtual TerminalConfigs generateSet4();
    virtual TerminalConfigs generateSet5();
    virtual TerminalConfigs generateSet6();
    virtual TerminalConfigs generateSet7();
    virtual TerminalConfigs generateSet8();
    virtual TerminalConfigs generateSet9();
    */
};

#endif// _TERM_CONFIG_02_H_
