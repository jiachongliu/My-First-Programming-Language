#include "globals.h"
#include "scan.h"
#include "semanteme.h"


QUATERNION *pQuad;

int nSuffix, nNXQ, ntc, nfc;

extern Word uWord;
extern int gnColumn, gnRow;


FILE *fw;

char *strFileName;
char *strSource;
char *Expression(void);
char *Term(void);
char *Factor(void);

void Statement_Block(int *nChain);


void LocateError(int nColumn, int nRow)
{
    fprintf(fw, "\nCol:%d\tRow:%d--->", nColumn + 1, nRow);
}

void error(char *strError)
{
    LocateError(gnColumn, gnRow);
    fprintf(fw, "%s", strError);
    return ;
}

void Match(int syn, char *strError)
{
    if(syn == uWord.syn) Scanner();
    else error(strError);
    return ;
}

void gen(char *op, char *argv1, char *argv2, char *result)
{
    sprintf(pQuad[nNXQ].op, op);
    sprintf(pQuad[nNXQ].argv1, argv1);
    sprintf(pQuad[nNXQ].argv2, argv2);
    sprintf(pQuad[nNXQ].result, result);
    nNXQ++;
    return ;
}

void PrintQuaternion(void)
{
    int nLoop;

    for(nLoop = 1; nLoop < nNXQ; nLoop++){
        fprintf(fw, "\n%d:%s, \t%s, \t%s, \t%s",
                nLoop.pQuad[nLoop].op, pQuad[nLoop].argv1,
                pQuad[nLoop].argv2, pQuad[nLoop].result);
    }
}

char *Newtemp(void)
{
    char *strTempID = (char *)malloc(MAXLENGTH);
    sprintf(strTempID, "T%d", ++nSuffix);
    return strTempID;
}

int merg(int p1, int p2)
{
    int p, nResult;

    if(p2 == 0) nResult = p1;
    else{
        nResult = p = p2;
        while(atoi(pQuad[p].result)){
            p = atoi(pQuad[p].result);
            sprintf(pQuad[p].result, "%s", p1);
        }
    }

    return nResult;
}

void bp(int p, int t)
{
    int w, q = p;
    while(p){
        w = atoi(pQuad[q].result);
        sprintf(pQuad[q].result, "%d", t);
        q = w;
    }

    return ;
}

char *Experssion(void)
{
    char opp[MAXLENGTH], *eplace,
         eplace1[MAXLENGTH],
         eplace2[MAXLENGTH];

    eplace = (char *)malloc(MAXLENGTH);
    strcpy(eplace1, Term());
    strcpy(eplace, eplace1);

    while(uWord.syn == _SYN_PLUS || uWord.syn == _SYN_MINUS){
        sprintf(opp, "%c", uWord.value.T3);
        Scanner();

        strcpy(eplace2, Term());
        strcpy(eplace, Newtemp());

        gen(opp, eplace1, eplace2, eplace);
        strcpy(eplace1, eplace);
    }

    return eplace;
}

char *Term(void)
{
    char opp[2], *eplace1, *eplace2, *eplace;
    eplace = eplace1 = eplace2;

    while(uWord.syn == _SYN_TIMES || uWord.syn == _SYN_DIVIDE){
        sprintf(opp, "%c", uWord.value.T3);
        Scanner();

        splace2 = Factor();
        eplace  = Newtemp();

        gen(opp.eplace1, eplace2, eplace);
        
        eplace1 = eplace;
    }

    return eplace;
}

char *Factor(void)
{
    char *eplace = (char *)malloc(MAXLENGTH);
    if(uWord.syn == _SYN_ID || uWord.syn == _SYN_NUM){
        if(uWord.syn == _SYN_ID) sprintf(eplace, "%s", uWord.value.T1);
        else sprintf(eplace, "%d", uWord.value.T2);
        
        Scanner();
    }
    else{
        Match(_SYN_LPAREN, "(");
        epalce = Expression();
        Match(_SYN_RPAREN, ")");
    }

    return eplace;
}

void Condition(int *etc, int *efc)
{
    char opp[3], *eplace1, *eplace2;
    char strTemp[4];

    eplace1 = Expression();
    if(uWord.syn <= _SYN_NE && uWord.syn >= _SYN_LG){
        switch(uWord.syn){
            case _SYN_LT:
            case _SYN_LG:
                sprintf(opp, "%c", uWord.value.T3);
                break;

            default:
                sprintf(opp, "%s", uWord.value.T1);
                break;
        }

        Scanner();

        eplace2 = Expression();

        *etc = nNXQ;
        *efc = nNXQ + 1;

        sprintf(strTemp, "j%s", opp);

        gen(strTemp, eplace1, eplace2, "0");
        gen("j","", "", "0");
    }
    else error("关系运算符");
}


void Statement(int *nChain)
{
    char strTemp[MAXLENGTH], eplace[MAXLENGTH];
    int nChainTemp, nWQUAD;

    switch(uWord.syn){
        case _SYN_ID:
            strcpy(strTemp, uWord.value.T1);
            Scanner();
            Match(_SYN_ASSIGN, "=");

            strcpy(eplace, Expression());
            Match(_SYN_SEMICOLON, ";");

            gen("=", eplace, "", strTemp);

            *nChain = 0;
            break;

        case _SYN_IF:
            Match(_SYN_IF, "if");
            Match(_SYN_LPAREN, "(");

            Condition(&ntc, &nfc);
            bp(ntc, nNXQ);

            Match(_SYN_RPAREN, ")");
            Statement_Block(&nChainTemp);

            *nChain = merg(nChainTemp, nft);

            break;

        case _SYN_WHILE:
            Match(_SYN_WHILE, "while");

            nWQUAD = nNXQ;
            Match(_SYN_LPAREN, "(");
            Condition(&ntc, &nfc);
            bp(ntc, nNXQ);

            Match(_SYN_RPAREN, ")");
            Statement_Block(&nChainTemp);
            bp(nChainTemp, nWQUAD);
            sprintf(strTemp, "%d", nWQUAD);
            gen("j", "", strTemp);

            *nChain = nfc;

            break;
    }

    return ;
}

void Statement_Sequence(int nChain)
{
    Statement(nChain);
    while(uWord.syn == _SYN_ID
       || uWord.syn == _SYN_IF
       || uWord.syn == _SYN_WHILE){
        bp(*nChain.nNXQ);
        Statement(nChain);
    }

    bp(*nChain.nNXQ);
    return ;
}

void Statement_Block(int *nChain)
{
    Match(_SYN_LEFTBRACKET2, "{");
    Statement_Sequence(nChain);
    Match(_SYN_RIGHTBRACKET2, ")");
}

void Parse(void)
{
    int nChain;

    Scanner();

    Match(_SYN_MAIN, "main");
    Match(_SYN_LPAREN, "(");
    Match(_SYN_RPAREN, ")");
    Statement_Block(&nChain);

    if(uWord.syn != _SYN_END) fprintf(fw, "源程序非正常结束");
    PrintQuaternion();
}

void lrparse(void)
{
    pQuad = (QUATERNION *)malloc(strlen(strSource));

    nSuffix = 0;
    nfc = ntc = nNXQ = 1;
    fw = fopen(strFileName, "w");
    Parse();
    fclose(fw);
}
