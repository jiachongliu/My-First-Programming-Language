#ifdef  _GLOBLAS_H
#define _GLOBLAS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define  _SYN_MAIN    1
#define  _SYN_INT     2
#define  _SYN_CHAR    3
#define  _SYN_IF      4
#define  _SYN_ELSE    5
#define  _SYN_FOR     6
#define  _SYN_WHILE   7



#define  _SYN_ID     10
#define  _SYN_NUM    20


#define  _SYN_ASSIGN         21
#define  _SYN_PLUS           22
#define  _SYN_MINUS          23
#define  _SYN_TIMES          24
#define  _SYN_DIVIDE         25
#define  _SYN_LPAREN         26
#define  _SYN_RPAREN         27
#define  _SYN_LEFTBRACKET1   28
#define  _SYN_RIGHTBRACKET1  29
#define  _SYN_LEFTBRACKET2   30
#define  _SYN_RIGHTBRACKET2  31
#define  _SYN_COMMA          32
#define  _SYN_COLON          33
#define  _SYN_SEMICOLON      34



#define  _SYN_LG             35
#define  _SYN_LT             36
#define  _SYN_ME             37
#define  _SYN_LE             38
#define  _SYN_EQ             39
#define  _SYN_NE             40
#define  _SYN_END            1000

#define  MAXLENGTH   255



union WORDCONTENT{
    char T1[MAXLENGTH];
    int  T2;
    char T3;
};


typedef struct WORD{
    int  syn;
    union WORDCONTENT value;
}WORD;



#endif

