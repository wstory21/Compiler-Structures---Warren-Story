%{
/*  Written by: Yancy Vance M. Paredes. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "firstCode.tab.h"
 
#define TABSIZE 1000
#define true 1
#define false 0
 
/* the following were defined in lexana.l */
extern char* var_names[TABSIZE];
extern int var_def[TABSIZE];
extern int n_of_names;
extern int install(char *txt);
extern void reset();
 
/* variables for the grammar file */
int invalid = false;            // just added for error checking
double var_values[TABSIZE];     // array where all the values are stored
 
int yyerror(const char *p) 
{
    fprintf(stderr, "%s\n", p); // print the error message
    invalid = true;
}
 
%}
 
%union {
    /* this will be used for the yylval. */
    /* it is a union since two data types will be used */
    double num;     // the number provided by the user
    int index;      // index of the variable name inside the array
};
 
%start manycmds
%token <index> VARIABLE
%token <num> NUMBER
%type <num> onecmd
%type <num> expression
%type <num> assignment
%type <num> term
%type <num> factor
%type <num> primary
 
%%
 
manycmds : onecmd                           { }
|   manycmds onecmd                         { }
;
 
onecmd : expression ';'                     { if(!invalid) fprintf(stderr, "%lf\n", $1); invalid = 0; }
|   assignment ';'                          { if(!invalid) fprintf(stderr, "%lf\n", $1); invalid = 0; }
 
expression : term                           { $$ = $1; }
|   '-' term                                { $$ = -$2; }
|   expression '+' term                     { $$ = $1 + $3; }
|   expression '-' term                     { $$ = $1 - $3; }
;
 
term : factor                               { $$ = $1; }
|   term '*' factor                         { $$ = $1 * $3; }
|   term '/' factor                         { if($3 == 0) yyerror("undefined"); else $$ = $1 / $3;  }
;
 
factor : primary                            { $$ = $1; }
|   primary '^' factor                      { $$ = pow($1, $3); }
;
 
primary : NUMBER                            { $$ = $1; }
|   VARIABLE                                { if(!var_def[$1]) yyerror("undefined"); else $$ = var_values[$1]; }
|   '(' expression ')'                      { $$ = $2; }
;
 
assignment : '@' VARIABLE '=' expression    { $$ = var_values[$2] = $4; var_def[$2] = 1; }
;
 
%%
 
int main(void)
{
    /* reset all the definition flags first */
    reset();
     
    yyparse();
     
    return 0;
}
