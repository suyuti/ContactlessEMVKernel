#ifndef _TERM_CONFIG_02_H_
#define _TERM_CONFIG_02_H_

#include "configFactory.h"

class TerminalConfig02 : public TerminalConfigs {
public:
    TerminalConfigs generate(string kid, string aid);
protected:
    TerminalConfigs generateSet1();
    TerminalConfigs generateSet2();
    TerminalConfigs generateSet3();
    TerminalConfigs generateSet4();
    TerminalConfigs generateSet5();
    TerminalConfigs generateSet6();
    TerminalConfigs generateSet7();
    TerminalConfigs generateSet8();
    TerminalConfigs generateSet9();
};

#endif// _TERM_CONFIG_02_H_
