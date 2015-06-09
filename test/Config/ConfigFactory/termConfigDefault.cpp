#include "termConfigDefault.h"

TerminalConfigs TerminalConfigDefault::generateSet1() {
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

TerminalConfigs TerminalConfigDefault::generateSet2() {
    return TerminalConfigs::TerminalConfigBuilder()
        .WithStatusCheck(NO)
        //.WithZeroAmountAllowed(YES)
        //.WithClessTrnxLimit(120)
        //.WithClessFloorLimit(12)
        //.WithTermFloorLimit(0)
        .WithCvmRequiredLimit(10)
        //.WithTtq("B6208000")
        //.WithExtendedSelectionSupport(YES)
        .Build();
}

TerminalConfigs TerminalConfigDefault::generateSet3() {
    return TerminalConfigs::TerminalConfigBuilder()
        .WithStatusCheck(YES)
        .WithZeroAmountAllowed(NO)
        .WithClessTrnxLimit(200)
        //.WithClessFloorLimit(12)
        .WithTermFloorLimit(25)
        //.WithCvmRequiredLimit(15)
        .WithTtq("28000000")
        .WithExtendedSelectionSupport(NO)
        .Build();
}

TerminalConfigs TerminalConfigDefault::generateSet4() {
    return TerminalConfigs::TerminalConfigBuilder()
        //.WithStatusCheck(YES)
        .WithZeroAmountAllowed(NO)
        //.WithClessTrnxLimit(120)
        .WithClessFloorLimit(50)
        //.WithTermFloorLimit(0)
        .WithCvmRequiredLimit(20)
        .WithTtq("84C08000")
        .WithExtendedSelectionSupport(YES)
        .Build();
}

TerminalConfigs TerminalConfigDefault::generateSet5() {
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

TerminalConfigs TerminalConfigDefault::generateSet6() {
    return TerminalConfigs::TerminalConfigBuilder()
        .WithStatusCheck(NO)
        //.WithZeroAmountAllowed(YES)
        //.WithClessTrnxLimit(120)
        //.WithClessFloorLimit(12)
        //.WithTermFloorLimit(0)
        .WithCvmRequiredLimit(10)
        //.WithTtq("B6208000")
        .WithExtendedSelectionSupport(NO)
        .Build();
}

TerminalConfigs TerminalConfigDefault::generateSet7() {
    return TerminalConfigs::TerminalConfigBuilder()
        .WithStatusCheck(YES)
        .WithZeroAmountAllowed(YES)
        .WithClessTrnxLimit(200)
        //.WithClessFloorLimit(12)
        .WithTermFloorLimit(25)
        //.WithCvmRequiredLimit(15)
        .WithTtq("28000000")
        //.WithExtendedSelectionSupport(YES)
        .Build();
}

TerminalConfigs TerminalConfigDefault::generateSet8() {
    return TerminalConfigs::TerminalConfigBuilder()
        .WithStatusCheck(YES)
        .WithZeroAmountAllowed(YES)
        //.WithClessTrnxLimit(120)
        .WithClessFloorLimit(50)
        //.WithTermFloorLimit(0)
        .WithCvmRequiredLimit(20)
        //.WithTtq("B6208000")
        .WithExtendedSelectionSupport(YES)
        .Build();
}

TerminalConfigs TerminalConfigDefault::generateSet9() {
    return TerminalConfigs::TerminalConfigBuilder()
        .WithStatusCheck(NO)
        //.WithZeroAmountAllowed(YES)
        .WithClessTrnxLimit(120)
        //.WithClessFloorLimit(12)
        //.WithTermFloorLimit(0)
        .WithCvmRequiredLimit(10)
        //.WithTtq("B6208000")
        .WithExtendedSelectionSupport(NO)
        .Build();
}
