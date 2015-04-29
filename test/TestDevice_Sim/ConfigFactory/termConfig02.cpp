#include "termConfig02.h"

TerminalConfigs TerminalConfig02::generate(string kid, string aid)
{
    return generateTerminalConfig01();
}

TerminalConfigs TerminalConfig02::generateSet1() {
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

TerminalConfigs TerminalConfig02::generateSet2() {
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

TerminalConfigs TerminalConfig02::generateSet3() {
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

TerminalConfigs TerminalConfig02::generateSet4() {
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

TerminalConfigs TerminalConfig02::generateSet5() {
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

TerminalConfigs TerminalConfig02::generateSet6() {
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

TerminalConfigs TerminalConfig02::generateSet7() {
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

TerminalConfigs TerminalConfig02::generateSet8() {
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

TerminalConfigs TerminalConfig02::generateSet9() {
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
