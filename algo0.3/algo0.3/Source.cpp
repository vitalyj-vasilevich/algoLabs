#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
typedef long long LINT;

using namespace std;

LINT min(LINT a, LINT b)
{
	return a < b ? a : b;
}

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	LINT amount;
	fin >> amount;
	short* input = new short[amount + 1];
	for (short i = 0; i < amount; ++i)
	{
		fin >> input[i] >> input[i + 1];
	}
	fin.close();
	LINT** work = new LINT*[amount];
	for (LINT i = 0; i < amount; i++)
	{
		work[i] = new LINT[amount];
	}
	for (short i = 0; i < amount; i++)
	{
		work[i][i] = 0;
	}
	for (short n = 2; n < amount + 1; ++n)
	{
		for (short first = 0; first < amount - n + 1; ++first)
		{
			short last = first + n - 1;
			work[first][last] = LONG_MAX;
			for (short k = first; k < last; ++k)
			{
				work[first][last] = min(work[first][last], work[first][k] + work[k + 1][last] + input[first] * input[last + 1] * input[k + 1]);
			}
		}
	}
	/*for (short i = 0; i < amount; i++)
	{
		for (short j = 0; j < amount; j++)
		{
			cout << work[i][j] << " ";
		}
		cout << endl;
	}*/
	fout << work[0][amount - 1];
	fout.close();
	system("pause");
	return 0;
}