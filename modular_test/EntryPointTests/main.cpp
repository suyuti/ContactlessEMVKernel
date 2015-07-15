/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */
#include <iostream>
#include<gtest/gtest.h>

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>


using namespace std;

void handler(int sig)
{
    void *array[10];
    size_t size;

    size = backtrace(array, 10);

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
