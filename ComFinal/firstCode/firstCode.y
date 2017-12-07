%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "firstCode.tab.h"
 
#define TABSIZE 1000
#define true 1
#define false 0
 
extern char* var_names[TABSIZE];
extern int n_of_names;
extern int install(char *txt);
 
int invalid = false;            
double var_values[TABSIZE];     

int yyerror(const char *p) 
{
    fprintf(stderr, "%s\n", p); 
    invalid = true;
}
 
%}
 
%union {
    double num;     
    int index;      
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
%token <string> lBinding
 
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
|   VARIABLE                                { $$ = var_values[$1]; }
|   '(' expression ')'{ $$ = $2; }
;

assignment : lBinding VARIABLE '=' expression    { $$ = var_values[$2] = $4;}
;
 
%%
 
int main(void)
{
    yyparse();
    return 0;
}
