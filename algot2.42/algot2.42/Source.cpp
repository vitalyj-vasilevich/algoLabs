#include <iostream>
#include <fstream>
typedef long long int LINT;

using namespace std;

LINT max(LINT a, LINT b)
{
	return a - b > 0 ? a : b;
}

LINT maxFour(LINT a, LINT b, LINT c, LINT d)
{
	return max(max(a, b), max(a, c));
}

LINT min(LINT a, LINT b)
{
	return a - b < 0 ? a : b;
}

int main()
{
	ifstream fin("input.txt");
	short n;
	if (!fin.eof())
	{
		fin >> n;
	}
	//cout << "read n = " << n << endl;
	LINT** counts = new LINT*[n];
	for (short i = 0; i < n; ++i)
	{
		counts[i] = new LINT[n];
	}
	for (short i = 0; i < n; i++)
	{
		fin >> counts[i][0];
	}
	fin.close();
	for (short i = 1; i < n; ++i)
	{
		for (short j = n - i - 1; j > -1; --j)
		{
			if (i == 1)
			{
				counts[j][i] = max(counts[j][0], counts[j + 1][0]);
			}
			else if(i == 2)
			{
				counts[j][i] = max(counts[j][0] + min(counts[j + 2][i - 2], counts[j + 1][i - 2]),
					counts[j + 2][0] + min(counts[j][i - 2], counts[j + 1][i - 2]));
			}
			else
			{
				counts[j][i] = max(counts[j][0] + min(counts[j + 2][i - 2], counts[j + 1][i - 2]),
					counts[i + j][0] + min(counts[j][i - 2], counts[j + 1][i - 2]));
			}
		}
	}
	for (short i = 0; i < n; i++)
	{
		for (short j = 0; j < n; j++)
		{
			cout << counts[i][j] << " ";
		}
		cout << endl;
	}
	ofstream fout("output.txt");
	fout << counts[0][n - 1] << endl;
	fout.close();
	system("pause");
	return 0;
}