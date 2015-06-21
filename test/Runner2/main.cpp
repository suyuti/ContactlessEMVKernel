#include <iostream>
#include<gtest/gtest.h>

#include "EntryPoint/Test_2EA_001_00_01.h"
#include "EntryPoint/Test_2EA_002_00.h"
#include "EntryPoint/Test_2EA_002_01.h"
#include "EntryPoint/Test_2EA_002_02.h"
#include "EntryPoint/Test_2EA_003_00.h"
#include "EntryPoint/Test_2EA_004_00.h"
#include "EntryPoint/Test_2EA_005_00.h"
#include "EntryPoint/Test_2EA_005_01.h"

#include "EntryPoint/epConfigTests.h"

using namespace std;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
