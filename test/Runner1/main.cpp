/*
    Copyright 2015
*/

#include <iostream>
#include<gtest/gtest.h>
#include<gmock/gmock.h>

/*#include "Hal_Test/halTests.h"

#include "EntryPoint_Test/entryPointTest.h"
#include "EntryPoint_Test/epIndicatorsTests.h"
#include "EntryPoint_Test/epTrnxParametersTests.h"

#include "Base_Test/selectTests.h"
#include "Base_Test/utilsTests.h"
#include "Base_Test/tlvTests.h"
#include "Base_Test/vectorTests.h"

#include "Mockups/mockup_tests.h"
*/
using namespace std;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
