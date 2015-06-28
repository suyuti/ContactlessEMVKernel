#ifndef _BITS_H_
#define _BITS_H_

#define BIT_0 0x01  // 00000001
#define BIT_1 0x02  // 00000010
#define BIT_2 0x04  // 00000100
#define BIT_3 0x08  // 00001000
#define BIT_4 0x10  // 00010000
#define BIT_5 0x20  // 00100000
#define BIT_6 0x40  // 01000000
#define BIT_7 0x80  // 10000000

#define SET_BIT(var, bit)           ((var) |= 1 << (bit));
#define RESET_BIT(var, bit)         ((var) &= ~(1 << (bit)))
#define TOGGLE_BIT(var, bit)        ((var) ^= 1 << (bit))
#define CHECK_BIT(var, bit)         (((var) >> (bit)) & 1)
#define CHANGE_NBIT(var, n, x)      ((var) ^= (-(x) ^ (var)) & (1 << (n)))

#endif// _BITS_H_
