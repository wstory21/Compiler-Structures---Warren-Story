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

void printBytes(queue<bitset<8>> fLetters, queue<int> bNum, int size)
{
	queue<char> hex;
	string num = "";
	int sum = 0;
	int count;
	int four = 1;
	for (int i = 0; i < size; i++)
	{
		count = 1;
		string yo = fLetters.front().to_string();
		cout << "Binary: " << yo << endl;

		for (int j = 0; j < 8; j++)
		{
			if (yo.at(7 - j) == '1')
			{
				sum += count;
			}

			four++;
			if (four > 4)
				four = 1;


			if (count == 8)
			{
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
		cout << "Hex UTF_8: " << num[1] << num[0] << endl << endl;
		num = "";
		fLetters.pop();
	}

	cout << "Unicode Character UTF_8 in hexadecimal: ";
	for (int i = 1; i < size * 2; i = i + 2)
	{
		if (bNum.front() == 0)
		{
			cout << " : ";
			bNum.pop();
		}
		cout << hex.front();
		hex.pop();
		cout << hex.front() << " ";
		hex.pop();
		bNum.front()--;
	}
	cout << endl;
}

void getbNum(queue <bitset<8>> letters, queue<int> &num, int size)
{
	letters.pop();
	int count = 1;
	string front;

	for (int i = 0; i < size - 1; i++)
	{
		front = letters.front().to_string();
		if ((front[0] == '1' && front[1] == '1' ) || front[0] == '0')
		{
			cout << "worked: " << letters.front()[0] << letters.front()[1] << endl;
			num.push(count + 0);
			count = 1;
		}
		else
		{
			cout << "letters: " << letters.front() << endl;
			count++;
		}
		letters.pop();
	}
	num.push(count + 0);
}

int main()
{
	ifstream inf;
	inf.open("input.txt");

	queue<bitset<8>> letters;
	queue<bitset<8>> fLetters;
	queue<int> bNum;

	int size = 0;

	while (!(inf.eof()))
	{
		bitset<8> l(inf.get());
		letters.push(l);
		size++;
	}
	inf.close();

	fLetters = filterOut(letters, size);

	getbNum(fLetters, bNum, size);

	printBytes(fLetters, bNum, size);

	system("pause");
}

