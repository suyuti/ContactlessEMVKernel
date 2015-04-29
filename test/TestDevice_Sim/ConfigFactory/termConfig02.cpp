#include "termConfig02.h"

TerminalConfigs TerminalConfig02::generate(string kid, string aid)
{
    if ((aid == "A0000000651010" && kid == "TK1") || 
        (aid == "A0000000030003" && kid == "21" ))
        return generateSet1();
    else if ((aid == "A0000000041010" && kid == "TK2") ||
             (aid == "A0000000020002" && kid == "22" ) ||
             (aid == "A0000000041010" && kid == "2B" ) ||
             (aid == "A0000000020002" && kid == "2B" ))
        return generateSet2();
    else if ((aid == "A0000000031010" && kid == "TK3") ||
             (aid == "A0000000010001" && kid == "23" ) ||
             (aid == "A0000000031010" && kid == "2B" ) ||
             (aid == "A0000000010001" && kid == "2B" ))
        return generateSet3();
    else if ((aid == "A0000000251010" && kid == "TK4") ||
             (aid == "A0000000651010" && kid == "TK5") ||
             (aid == "A0000000040004" && kid == "24" ) ||
             (aid == "A0000000030003" && kid == "25" ))
        return generateSet4();
    else if ((aid == "A0000000041010" && kid == "TK4") ||
             (aid == "A0000000020002" && kid == "24" ))
        return generateSet5();
    else if ((aid == "A0000000031010" && kid == "TK1") ||
             (aid == "A0000000010001" && kid == "21" ))
        return generateSet6();
    else if ((aid == "A0000000651010" && kid == "TK2") ||
             (aid == "A0000000251010" && kid == "TK5") ||
             (aid == "A0000000030003" && kid == "22" ) ||
             (aid == "A0000000040004" && kid == "25" ))
        return generateSet7();
    else if ((aid == "A0000000251010" && kid == "TK3") ||
             (aid == "A0000000040004" && kid == "23" ))
        return generateSet8();
    else if ((aid == "A0000000251010" && kid == "2B" ) || 
             (aid == "A0000000040004" && kid == "2B" ) ||
             (aid == "A0000001523010" && kid == "TK6") ||
             (aid == "A0000003330101" && kid == "TK7") ||
             (aid == "A0000003241010" && kid == "TK6"))
        return generateSet9();
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
