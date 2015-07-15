/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_SRC_COMMON_GENERAL_H_
#define MODULAR_SRC_COMMON_GENERAL_H_

#define OK          1
#define NOK         0
#define SET         1
#define RESET       0
#define TRUE        1
#define FALSE       0
#define YES         1
#define NO          0

typedef unsigned char   BYTE;
typedef unsigned short  WORD;
#define MAKEWORD(a,b)   ((WORD)(((BYTE)(a))|(((WORD)((BYTE)(b)))<<8)))

#define IS_SUCCESS(err) if ((err) != SUCCESS) return err

#endif// MODULAR_SRC_COMMON_GENERAL_H_
