%{
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

%}
 
%%
[ \t\n];
[-|+]?[0-9]+ {
	cout << "Signed Integer: " << yytext << endl;
}
[-|+]?[[0-9]*\.[0-9]+]|[0-9]+ {
	cout << "Signed Double: " << yytext << endl;
}
[a-zA-Z0-9]+ {
	cout << "Found a String: " << yytext << endl;
}
%%
int main(int, char**) {
	yylex();
}
