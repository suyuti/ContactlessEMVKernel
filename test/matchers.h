#ifndef _MATCHERS_H_
#define _MATCHERS_H_

#include <gtest/gtest.h>
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

MATCHER_P(isSelectAIP, a, "") {
    unsigned char select[] = {  0x00, 0xA4, 0x04, 0x00};
    if (memcmp(select, arg, sizeof(select)) == 0)
        return true;
    return false;
}

MATCHER_P(isGPO, a, "") {
    unsigned char gpo[] = {  0x00, 0xA4, 0x04, 0x00};
    if (memcmp(gpo, arg, sizeof(gpo)) == 0)
        return true;
    return false;
}

#endif// _MATCHERS_H_
