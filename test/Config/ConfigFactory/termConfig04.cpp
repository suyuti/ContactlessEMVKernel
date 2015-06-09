#include "termConfig04.h"

TerminalConfigs TerminalConfig04::generateSet1() {
    return TerminalConfigs::TerminalConfigBuilder()
        //.WithStatusCheck(YES)
        .WithZeroAmountAllowed(YES)
        //.WithClessTrnxLimit(120)
        .WithClessFloorLimit(20)
        //.WithTermFloorLimit(0)
        //.WithCvmRequiredLimit(15)
        .WithTtq("84008000")
        .WithExtendedSelectionSupport(YES)
        .Build();
}

TerminalConfigs TerminalConfig04::generateSet4() {
    return TerminalConfigs::TerminalConfigBuilder()
        .WithStatusCheck(NO)
        .WithZeroAmountAllowed(NO)
        .WithClessTrnxLimit(120)
        //.WithClessFloorLimit(50)
        //.WithTermFloorLimit(0)
        .WithCvmRequiredLimit(20)
        .WithTtq("84C08000")
        .WithExtendedSelectionSupport(YES)
        .Build();
}

TerminalConfigs TerminalConfig04::generateSet5() {
    return TerminalConfigs::TerminalConfigBuilder()
        //.WithStatusCheck(YES)
        .WithZeroAmountAllowed(YES)
        .WithClessTrnxLimit(120)
        .WithClessFloorLimit(20)
        //.WithTermFloorLimit(0)
        //.WithCvmRequiredLimit(15)
        .WithTtq("84008000")
        .WithExtendedSelectionSupport(YES)
        .Build();
}

TerminalConfigs TerminalConfig04::generateSet9() {
    return TerminalConfigs::TerminalConfigBuilder()
        //.WithStatusCheck(NO)
        //.WithZeroAmountAllowed(YES)
        //.WithClessTrnxLimit(120)
        .WithClessFloorLimit(50)
        //.WithTermFloorLimit(0)
        //.WithCvmRequiredLimit(10)
        .WithTtq("B6208000")
        .WithExtendedSelectionSupport(YES)
        .Build();
}
