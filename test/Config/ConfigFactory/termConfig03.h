#ifndef _TERM_CONFIG_03_H_
#define _TERM_CONFIG_03_H_

#include "termConfigDefault.h"

class TerminalConfig03 : public TerminalConfigDefault {
//public:
//   TerminalConfigs generate(string kid, string aid);
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

#endif// _TERM_CONFIG_03_H_
