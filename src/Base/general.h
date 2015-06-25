#ifndef _GENERAL_H_
#define _GENERAL_H_

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
    
#endif// _GENERAL_H_
