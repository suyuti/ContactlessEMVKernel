/*
    Copyright 2015
*/

#include <iostream>
#include<gtest/gtest.h>
#include<gmock/gmock.h>

#include "EntryPoint_Test/entryPointTest.h"
#include "Base_Test/selectTests.h"

using namespace std;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
