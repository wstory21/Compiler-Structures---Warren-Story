#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <bitset>
#include <queue>

using namespace std;

queue<bitset<8>> filterOut(queue<bitset<8>> &letters, int &size)
{
	queue<bitset<8>> Fletters;
	int count = 1;
	for (int i = size; i > 0; i--)
	{
		if (count == 1 || count == 2 || count == 3)
		{
			letters.pop();
			count++;
			size--;
		}
		else if (letters.front().to_ulong() == 255)
		{
			letters.pop();
			count = 1;
			size--;
		}
		else
		{
			Fletters.push(letters.front());
			letters.pop();
			count++;
		}
	}
	return Fletters;
}


int main()
{
	ifstream inf;
	inf.open("input.txt");

	queue<bitset<8>> letters;
	queue<bitset<8>> fLetters;

	int size = 0;
	queue<char> hex;

	while (!(inf.eof()))
	{
		bitset<8> l (inf.get());
		letters.push(l);
		size++;
	}
	inf.close();

	fLetters = filterOut(letters, size);

	string num = "";
	int sum = 0;
	int count;
	int four = 1;
	for (int i = 0; i < size; i++)
	{
		count = 1;
		string yo = fLetters.front().to_string();
		cout << "String: " << yo << endl;

		for (int j = 0; j < 8; j++)
		{
			if (yo.at(7-j) == '1')
			{
				sum += count;
			}

			four++;
			if (four > 4)
				four = 1;


			if (count == 8)
			{
				cout << "TSum: " << sum << endl;
				switch (sum)
				{
				case 0:
					num += '0';
					break;
				case 1:
					num += '1';
					break;
				case 2:
					num += '2';
					break;
				case 3:
					num += '3';
					break;
				case 4:
					num += '4';
					break;
				case 5:
					num += '5';
					break;
				case 6:
					num += '6';
					break;
				case 7:
					num += '7';
					break;
				case 8:
					num += '8';
					break;
				case 9:
					num += '9';
					break;
				case 10:
					num += 'A';
					break;
				case 11:
					num += 'B';
					break;
				case 12:
					num += 'C';
					break;
				case 13:
					num += 'D';
					break;
				case 14:
					num += 'E';
					break;
				case 15:
					num += 'F';
					break;
				default:
					cout << "Didn't Work!" << endl;
				}
				sum = 0;
				four = 1;
			}
			count = count * 2;
			if (count > 8)
				count = 1;
		}
		hex.push(num[1]);
		hex.push(num[0]);
		cout << "Num: " << num << endl << endl;
		num = "";
		fLetters.pop();
	}

	cout << "Unicode Point (Hex): ";
	for (int i = 1; i < size * 2; i = i + 2)
	{
		cout << hex.front();
		hex.pop();
		cout << hex.front() << " : ";
		hex.pop();
	}

	system("pause");
}
