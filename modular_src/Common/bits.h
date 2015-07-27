/*
    Copyright 2015
*/

#ifndef MODULAR_SRC_COMMON_BITS_H_
#define MODULAR_SRC_COMMON_BITS_H_

#define BIT_1  1  // 00000001
#define BIT_2  2  // 00000010
#define BIT_3  3  // 00000100
#define BIT_4  4  // 00001000
#define BIT_5  5  // 00010000
#define BIT_6  6  // 00100000
#define BIT_7  7  // 01000000
#define BIT_8  8  // 10000000


#define SET_BIT(var, bit)           ((var) |= (1 << (unsigned char)(bit - 1)));
#define RESET_BIT(var, bit)         ((var) &= ~(1 << ((unsigned char)bit - 1)))
#define TOGGLE_BIT(var, bit)        ((var) ^= 1 << (bit))
#define CHECK_BIT(var, bit)         (((var) >> ((unsigned char)bit-1)) & 1)
#define CHANGE_NBIT(var, n, x)      ((var) ^= (-(x) ^ (var)) & (1 << (n)))

#endif  // MODULAR_SRC_COMMON_BITS_H_
