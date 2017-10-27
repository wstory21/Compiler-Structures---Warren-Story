#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <bitset>
#include <queue>

using namespace std;

string binToHex(string s)
{
	int sum = 0;
	int four = 0;
	string num;

	for (int i = s.length()/4; i > 0; i--)
	{
		if (s[four] == '1')
			sum += 8;
		if (s[four + 1] == '1')
			sum += 4;
		if (s[four + 2] == '1')
			sum += 2;
		if (s[four + 3] == '1')
			sum += 1;
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
		four = four + 4;
		sum = 0;
	}
	return num;
}

void getHex(queue<bitset<8>> fLetters, queue<int> bNum, int size, queue<char> &hex)
{
	string num = "";
	int four = 1;
	int sum = 0;
	int count;
	for (int i = 0; i < size; i++)
	{
		count = 1;
		string yo = fLetters.front().to_string();

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
		num = "";
		fLetters.pop();
	}
}

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
	getHex(fLetters, bNum, size, hex);

	cout << "Unicode Character UTF_8 in hexadecimal" << endl;
	for (int i = 1; i < size * 2; i = i + 2)
	{
		if (bNum.front() == 0)
		{
			cout << ": ";
			bNum.pop();
		}
		cout << hex.front();
		hex.pop();
		cout << hex.front() << " ";
		hex.pop();
		bNum.front()--;
	}
	cout << endl << endl;
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
			num.push(count + 0);
			count = 1;
		}
		else
		{
			count++;
		}
		letters.pop();
	}
	num.push(count + 0);
}

void getCodePoint(queue<bitset<8>> fLetters, queue<int> bNum, int size)
{
	string first;
	string second;
	string third;
	string fourth;
	string ans;
	queue<char> hex;
	int count = 1;
	int rSize = bNum.size() + 0;
	getHex(fLetters, bNum, size, hex);
	for (int i = 0; i < rSize; i++)
	{
		if (bNum.front() == 1)
		{
			cout << "Code Point for Character #" << count << ": U+00" << hex.front();
			hex.pop();
			cout << hex.front() << endl;
			hex.pop();
			fLetters.pop();
			bNum.pop();
			count++;
		}
		else if (bNum.front() == 2)
		{
			hex.pop();
			hex.pop();
			cout << "Code Point for Character #" << count << ": U+00" << hex.front();
			hex.pop();
			cout << hex.front() << endl;
			fLetters.pop();
			fLetters.pop();
			hex.pop();
			bNum.pop();
			count++;
		}
		else if (bNum.front() == 3)
		{
			first = fLetters.front().to_string();
			fLetters.pop();
			second = fLetters.front().to_string();
			fLetters.pop();
			third = fLetters.front().to_string();
			fLetters.pop();
			first = first.substr(4, 8);
			second = second.substr(2, 8);
			third = third.substr(2, 8);

			string binFull = first + second + third;
			ans = binToHex(binFull);
			cout << "Code Point for Character #" << count << ": " << "U+" << ans << endl;
			count++;
			bNum.pop();
		}
		else if (bNum.front() == 4)
		{
			first = fLetters.front().to_string();
			fLetters.pop();
			second = fLetters.front().to_string();
			fLetters.pop();
			third = fLetters.front().to_string();
			fLetters.pop();
			fourth = fLetters.front().to_string();
			fLetters.pop();
			first = first.substr(6, 8);
			second = second.substr(2, 8);
			third = third.substr(2, 8);
			fourth = fourth.substr(2, 8);

			string binFull = first + second + third + fourth;
			ans = binToHex(binFull);
			cout << "Code Point for Character #" << count << ": " << "U+" << ans << endl;
			count++;
			bNum.pop();
		}
		else
			break;
	}
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

	getCodePoint(fLetters, bNum, size);

	system("pause");
}



