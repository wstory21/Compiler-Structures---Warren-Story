#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <bitset>
#include <queue>

using namespace std;

int main()
{
	ifstream inf;
	inf.open("input.txt");

	queue<bitset<8>> letters;

	int size = 0;

	while (!(inf.eof()))
	{
		bitset<8> l (inf.get());
		letters.push(l);
		size++;
	}
	inf.close();

	ofstream otf;
	otf.open("outputDec.txt");
	//converting to bin
	for (int i = size; i > 0; i--)
	{
		otf << letters.front() << " ";
		letters.pop();
	}

	//Converting to hex
	inf.open("input.txt");
	while (!(inf.eof()))
	{
		bitset<8> l(inf.get());
		letters.push(l);
		size++;
	}


}
