/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_TEST_MATCHERS_H_
#define MODULAR_TEST_MATCHERS_H_

#include <gtest/gtest.h>

extern "C" {
    #include "../modular_src/Common/utils.h"
}

using ::testing::MakeMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;

MATCHER_P(isSelectPPSE, a, "") {
    unsigned char selectPPSE[] = {  0x00, 0xA4, 0x04, 0x00,
                                    0x0D,
                                    '2', 'P', 'A', 'Y', '.', 'S', 'Y', 'S', '.', 'D', 'D', 'F', '0', '1',
                                };
    if (memcmp(selectPPSE, arg, sizeof(selectPPSE)) == 0)
        return true;
    return false;
}

MATCHER_P(isSelectAIP, aid, "") {
    unsigned char tmp[120] = {0x00};


    if (arg[0] == 0x00 &&
        arg[1] == 0xA4 &&
        arg[2] == 0x04 &&
        arg[3] == 0x00) {
        int l = arg[4];
        if (l == 0) {
            return false;
        }
        int tmpLen = 0;
        bcd2str(arg+5, l, tmp, &tmpLen);
        if (strncmp(aid, (const char*)tmp, strlen(aid)) == 0) {
            return true;
        }
        return false;
    }
    return false;
}

MATCHER_P(isGPO, a, "") {
    unsigned char gpo[] = {0x80, 0xA8, 0x00, 0x00};
    if (memcmp(gpo, arg, sizeof(gpo)) == 0)
        return true;
    return false;
}

MATCHER_P2(isGPO, amount, amountAuthorized, "") {
    unsigned char gpo[] = {0x80, 0xA8, 0x00, 0x00};
    unsigned char f[] = "80A8000021831F0100000000000000000000750000000000000075769326000000000000000000";
    if (memcmp(gpo, arg, sizeof(gpo)) == 0)
        return true;
    return false;
}

MATCHER_P(isApdu, expected, "") {
    unsigned char tmp[1024] = {0x00};
    int exSize = strlen(expected)/2;
    int size = 0;
    bcd2str(arg,
        exSize,
        tmp,
        &size);
    if (strncmp(reinterpret_cast<char*>expected, reinterpret_cast<char*>tmp, exSize) == 0) {
        return true;
    }
    return false;
}

MATCHER_P(isConfig, name, "") {
    cout << arg << endl;
    return true;
}


#endif// MODULAR_TEST_MATCHERS_H_
