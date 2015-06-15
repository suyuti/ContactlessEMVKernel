#include <string.h> // memcpy
#include <stdio.h> // sprintf
#include "configFactory.h"

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithStatusCheck(unsigned char v) 
{
    //fProperties.config.statusCheck = v;
    if (v == YES) {
        SET_STATUS_CHECK(fProperties.config);
    }
    else { 
        RESET_STATUS_CHECK(fProperties.config);
    }
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithZeroAmountAllowed(unsigned char v)
{
    fProperties.config.zeroAmountAllowed = v;
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithClessTrnxLimit(int v)
{
    fProperties.config.clessTrnxLimit = v;
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithClessFloorLimit(int v)
{
    fProperties.config.clessFloorLimit = v;
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithTermFloorLimit(int v)
{
    fProperties.config.termFloorLimit = v;
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithCvmRequiredLimit(int v)
{
    fProperties.config.cvmRequiredLimit = v;
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithTtq(string v)
{
    // TODO
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithTtq(unsigned char v[4])
{
    memcpy(fProperties.config.ttq, v, 4);
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithExtendedSelectionSupport(unsigned char v)
{
    fProperties.config.extendedSelectionSupport = v;
    return *this;
}

TerminalConfigs TerminalConfigs::TerminalConfigBuilder::Build() 
{
    return TerminalConfigs(fProperties);
}

string TerminalConfigs::toString()
{
    char tmp[255];
    string str = "";

    sprintf(tmp, "Status Check        : %s\n", IS_STATUS_CHECK(fProperties.config)== YES ? "YES" : "NO");
    str.append(tmp);

    sprintf(tmp, "Zero Amount Allowed : %s\n", fProperties.config.zeroAmountAllowed == YES ? "YES" : "NO");
    str.append(tmp);

    sprintf(tmp, "Cless Trnx Limit    : %d\n", fProperties.config.clessTrnxLimit);
    str.append(tmp);

    sprintf(tmp, "Cless Floor Limit   : %d\n", fProperties.config.clessFloorLimit);
    str.append(tmp);

    sprintf(tmp, "Terminal Floor Limit: %d\n", fProperties.config.termFloorLimit);
    str.append(tmp);

    sprintf(tmp, "CVM Required Limit  : %d\n", fProperties.config.cvmRequiredLimit);
    str.append(tmp);

    sprintf(tmp, "TTQ                 : %02X %02X %02X %02X\n", 
                                                fProperties.config.ttq[0], 
                                                fProperties.config.ttq[1], 
                                                fProperties.config.ttq[2], 
                                                fProperties.config.ttq[3]);

    // TODO Extended selection Support

    str.append(tmp);

    return str;
}
