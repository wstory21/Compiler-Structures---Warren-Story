%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "firstCode.tab.h"
 
#define TABSIZE 1000
 
char* var_names[TABSIZE];         
int n_of_names = 0;          

int install(char *txt)
{
    int j; char *s;
     
    if(n_of_names == 0) {
        s = strdup(txt);
        var_names[0] = s;
        ++n_of_names;
        return 0;
    }
     
    for(j = 0; j < n_of_names; ++j) {
        if(strcmp(txt, var_names[j]) == 0) {
            return j;
        }
    }
     
    s = strdup(txt);
    var_names[j] = s;
    ++n_of_names;
    return j;
}
 
%}
 
ALPHA   [a-z]|[a-z][a-z]
NUM     [0-9]|[0-9][0-9]
LET	[l][e][t][ ]

%%
 
[ \n\t]                 { }
 
[0-9][0-9]*(\.[0-9]+)?  {
    yylval.num = atof(yytext);
    return NUMBER;
}
 
{ALPHA}+{NUM}*    {
    yylval.index = install(yytext);
    return VARIABLE;
}
{LET}			{
    yylval.index = install(yytext);
    return lBinding;
}
.                       {
    return yytext[0];
}
 
%%
 
int yywrap(void)
{
    return 1;
}