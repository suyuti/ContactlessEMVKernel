#ifndef _TERM_CONFIG_05_H_
#define _TERM_CONFIG_05_H_

#include "termConfigDefault.h"

class TerminalConfig05 : public TerminalConfigDefault {
public:
    virtual TerminalConfigs generate(string kid = "", string aid = "", TrnxTypes trnx = None);
};

#endif// _TERM_CONFIG_05_H_
