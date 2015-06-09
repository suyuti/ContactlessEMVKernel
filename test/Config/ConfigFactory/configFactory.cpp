#include <string.h> // memcpy
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

//TerminalConfigs TerminalConfigs::generate(string kid, string aid, string trnx)
//{
//    return *this; // TODO
//}
