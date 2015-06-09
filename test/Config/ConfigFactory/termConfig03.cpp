#include "termConfig03.h"


TerminalConfigs TerminalConfig03::generateSet9() {
    return TerminalConfigs::TerminalConfigBuilder()
        .WithStatusCheck(NO)
        //.WithZeroAmountAllowed(YES)
        .WithClessTrnxLimit(100)
        //.WithClessFloorLimit(12)
        //.WithTermFloorLimit(0)
        .WithCvmRequiredLimit(10)
        //.WithTtq("B6208000")
        .WithExtendedSelectionSupport(NO)
        .Build();
}
