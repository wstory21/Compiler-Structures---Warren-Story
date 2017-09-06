#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <bitset>
#include <stack>

using namespace std;

struct Node
{
	bitset<8> letter;
	Node *next;
};


int main()
{
	Node *inn = new Node;
	ifstream inf;

	inf.open("input.txt");

	stack<bitset<8>> letters;

	int size = 0;

	while (!(inf.eof()))
	{
		bitset<8> l (inf.get());
		letters.push(l);
		size++;
	}

	ofstream otf;
	otf.open("outputDec.txt");
	for (int i = size; i > 0; i--)
	{
		otf << letters.top() << " ";
		letters.pop();
	}

	/*
	ifstream inf;
	inf.open("input.txt");
	bitset<8> first (inf.get());
	bitset<8> second(inf.get());
	bitset<8> third(inf.get());
	bitset<8> fourth(inf.get());


	ofstream otf;
	otf.open("outputDec.txt");
	otf << first << endl << second << endl << third << endl << fourth;
	*/








	/*
	char uni[100];
	char buffer[100];

	ifstream inf;
	inf.open("input.txt");

	ofstream otf;
	otf.open("output.bin", ios::out | ios::binary);

	int size = 0;
	while (!(inf.eof()))
	{
		inf >> uni[size];
		size++;
	}

	otf.write(uni, size);
	otf.close();
	otf.open("outputDec.txt");
	*/
}