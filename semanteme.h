#ifndef _SEMANTEME_H
#define _SEMANTEME_H


#define MAXLENGTH 100


typedef struct QUAD{
    char op[MAXLENGTH];
    char argv1[MAXLENGTH];
    char argv2[MAXLENGTH];
    char result[MAXLENGTH];
}QUATERNION;

void lrparse(void);


#endif
