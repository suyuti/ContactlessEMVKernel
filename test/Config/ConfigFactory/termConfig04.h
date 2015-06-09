#ifndef _TERM_CONFIG_04_H_
#define _TERM_CONFIG_04_H_

#include "termConfigDefault.h"

class TerminalConfig04 : public TerminalConfigDefault {
protected:
    virtual TerminalConfigs generateSet1();
    virtual TerminalConfigs generateSet4();
    virtual TerminalConfigs generateSet5();
    virtual TerminalConfigs generateSet9();
};

#endif// _TERM_CONFIG_04_H_