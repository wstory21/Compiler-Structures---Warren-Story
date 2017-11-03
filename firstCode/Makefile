CXXFLAGS=-std=gnu++11
all : firstCode

lex.yy.c : firstCode.l
	flex firstCode.l
	
firstCode.tab.h firstCode.tab.c : firstCode.y
	bison -d -o firstCode.tab.c firstCode.y
	gcc firstCode.tab.c lex.yy.c -lm -o calculator
