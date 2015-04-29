#include <string.h> // memcpy
#include "configFactory.h"

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithStatusCheck(unsigned char v) 
{
    fProperties.config.statusCheck = v;
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

TerminalConfigs TerminalConfigs::generateTerminalConfig01()
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck(YES)
                            .WithZeroAmountAllowed(YES)
                            .WithClessTrnxLimit(120)
                            .WithClessFloorLimit(12)
                            //.WithTermFloorLimit(0)
                            .WithCvmRequiredLimit(15)
                            .WithTtq("B6208000")
                            .WithExtendedSelectionSupport(YES)
                            .Build();
}
/*

TerminalConfigs TerminalConfigs::generateTerminalConfig02(string kernelId, string aid)
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck()
                            .WithZeroAmountAllowed()
                            .WithClessTrnxLimit()
                            .WithClessFloorLimit()
                            .WithTermFloorLimit()
                            .WithCvmRequiredLimit()
                            .WithTtq()
                            .WithExtendedSelectionSupport();
                            .Build();
}

TerminalConfigs TerminalConfigs::generateTerminalConfig03()
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck()
                            .WithZeroAmountAllowed()
                            .WithClessTrnxLimit()
                            .WithClessFloorLimit()
                            .WithTermFloorLimit()
                            .WithCvmRequiredLimit()
                            .WithTtq()
                            .WithExtendedSelectionSupport();
                            .Build();
}
TerminalConfigs TerminalConfigs::generateTerminalConfig04()
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck()
                            .WithZeroAmountAllowed()
                            .WithClessTrnxLimit()
                            .WithClessFloorLimit()
                            .WithTermFloorLimit()
                            .WithCvmRequiredLimit()
                            .WithTtq()
                            .WithExtendedSelectionSupport();
                            .Build();
}
TerminalConfigs TerminalConfigs::generateTerminalConfig05()
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck()
                            .WithZeroAmountAllowed()
                            .WithClessTrnxLimit()
                            .WithClessFloorLimit()
                            .WithTermFloorLimit()
                            .WithCvmRequiredLimit()
                            .WithTtq()
                            .WithExtendedSelectionSupport();
                            .Build();
}
TerminalConfigs TerminalConfigs::generateTerminalConfig06()
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck()
                            .WithZeroAmountAllowed()
                            .WithClessTrnxLimit()
                            .WithClessFloorLimit()
                            .WithTermFloorLimit()
                            .WithCvmRequiredLimit()
                            .WithTtq()
                            .WithExtendedSelectionSupport();
                            .Build();
}
TerminalConfigs TerminalConfigs::generateTerminalConfig07()
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck()
                            .WithZeroAmountAllowed()
                            .WithClessTrnxLimit()
                            .WithClessFloorLimit()
                            .WithTermFloorLimit()
                            .WithCvmRequiredLimit()
                            .WithTtq()
                            .WithExtendedSelectionSupport();
                            .Build();
}
TerminalConfigs TerminalConfigs::generateTerminalConfig08()
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck()
                            .WithZeroAmountAllowed()
                            .WithClessTrnxLimit()
                            .WithClessFloorLimit()
                            .WithTermFloorLimit()
                            .WithCvmRequiredLimit()
                            .WithTtq()
                            .WithExtendedSelectionSupport();
                            .Build();
}
TerminalConfigs TerminalConfigs::generateTerminalConfig09()
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck()
                            .WithZeroAmountAllowed()
                            .WithClessTrnxLimit()
                            .WithClessFloorLimit()
                            .WithTermFloorLimit()
                            .WithCvmRequiredLimit()
                            .WithTtq()
                            .WithExtendedSelectionSupport();
                            .Build();
}
TerminalConfigs TerminalConfigs::generateTerminalConfig10()
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck()
                            .WithZeroAmountAllowed()
                            .WithClessTrnxLimit()
                            .WithClessFloorLimit()
                            .WithTermFloorLimit()
                            .WithCvmRequiredLimit()
                            .WithTtq()
                            .WithExtendedSelectionSupport();
                            .Build();
}
TerminalConfigs TerminalConfigs::generateTerminalConfig11()
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck()
                            .WithZeroAmountAllowed()
                            .WithClessTrnxLimit()
                            .WithClessFloorLimit()
                            .WithTermFloorLimit()
                            .WithCvmRequiredLimit()
                            .WithTtq()
                            .WithExtendedSelectionSupport();
                            .Build();
}
TerminalConfigs TerminalConfigs::generateTerminalConfig12()
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck()
                            .WithZeroAmountAllowed()
                            .WithClessTrnxLimit()
                            .WithClessFloorLimit()
                            .WithTermFloorLimit()
                            .WithCvmRequiredLimit()
                            .WithTtq()
                            .WithExtendedSelectionSupport();
                            .Build();
}
TerminalConfigs TerminalConfigs::generateTerminalConfig13()
{
    return TerminalConfigs::TerminalConfigBuilder()
                            .WithStatusCheck()
                            .WithZeroAmountAllowed()
                            .WithClessTrnxLimit()
                            .WithClessFloorLimit()
                            .WithTermFloorLimit()
                            .WithCvmRequiredLimit()
                            .WithTtq()
                            .WithExtendedSelectionSupport();
                            .Build();
}
*/