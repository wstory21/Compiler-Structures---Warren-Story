#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void GetToken();
void exp();
void digit();
void number();
void factor();
void term();
void parse();

string word = "3+4";
int index = 0;
char token;

void GetToken()
{
	while (word[index] == ' ')
		index++;
	if (index < word.length())
	{
		token = word[index];
		cout << endl << "<gettoken> " << token << " ";
		index++;
	}
	else
	{
		cout << endl << "The parse has been complete with no problems!" << endl;
		token = '$';
		index = 100;
	}
}

void digit()
{
	cout << "<digit> ";
	if (token == '0' || token == '1' || token == '2' || token == '3' || token == '4' || token == '5' || token == '6' || token == '7' || token == '8' || token == '9')
	{
		GetToken();
	}
	else
		cout << "error" << endl;
}

void number()
{
	cout << "<number> ";
	digit();
	while (token == '0' || token == '1' || token == '2' || token == '3' || token == '4' || token == '5' || token == '6' || token == '7' || token == '8' || token == '9')
	{
		digit();
	}
}

void factor()
{
	cout << "<factor> ";
	if (token == '(')
	{
		GetToken();
		exp();
		if (token == ')')
		{
			GetToken();
		}
		else
			cout << "Error";
	}
	else
		number();
}

void term()
{
	cout << "<term> ";
	factor();
	while (token == '*')
	{
		GetToken();
		factor();
	}
}

void exp()
{
	cout << "<exp> ";
	term();
	while (token == '+')
	{
		GetToken();
		term();
	}
}

void parse()
{
	GetToken();
	exp();
}


int main()
{
	parse();
	system("pause");
}