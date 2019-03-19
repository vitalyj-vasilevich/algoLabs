#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt");
	map <long long int, bool> numbers;
	long long int a = 0;
	numbers.insert(pair<long long int, bool>(0, true));
	while (!fin.eof())
	{
		fin >> a;
		numbers.insert(pair<long long int, bool>(a, true));
	}
	fin.close();
	long long int sum = 0;
	for (auto it = numbers.begin(); it != numbers.end(); ++it)
	{
		sum += (*it).first;
	}
	fout.open("output.txt");
	fout << sum;
	fout.close();
	return 0;
}