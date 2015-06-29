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

#include "EntryPoint/entryPointTest.h"
#include "EntryPoint/epConfigTests.h"
#include "EntryPoint/epPreProcessingTests.h"
#include "EntryPoint/epCombinationSelectionTests.h"

#include "Base/candidateListTests.h"
#include "Base/selectTests.h"
#include "Base/utilsTests.h"
#include "Base/kernelTests.h"

using namespace std;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
