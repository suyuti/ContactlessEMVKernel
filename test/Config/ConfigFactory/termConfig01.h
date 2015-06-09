#ifndef _TERM_CONFIG_01_H_
#define _TERM_CONFIG_01_H_

#include "termConfigDefault.h"

class TerminalConfig01 : public TerminalConfigDefault {
public:
    // Same as Default parameter
    virtual TerminalConfigs generate(string kid = "", string aid = "", TrnxTypes trnx = None);
};

#endif// _TERM_CONFIG_01_H_
