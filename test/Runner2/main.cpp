#include <iostream>
#include<gtest/gtest.h>

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>

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

void handler(int sig) 
{
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, 2);
  exit(1);
}

int main(int argc, char** argv)
{
    signal(SIGSEGV, handler);   // install our handler
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
