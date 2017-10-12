CXXFLAGS=-std=gnu++11
all : firstCode

lex.yy.cpp : firstCode.l
	flex -o lex.yy.cpp firstCode.l
	sed -i- -e 's/register //g' lex.yy.cpp


	bison lex.yy.cpp
