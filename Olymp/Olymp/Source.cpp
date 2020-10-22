#include <queue>
#include <iostream>
#include <list>
#include <map>
#include <math.h>

using namespace std;


int main()
{

	string in;
	cin >> in;

	vector<int> num;
	
	for(auto temp : in)
	{
		int n = temp - '0';
		if (n == 0) num.back() *= 10;
		else num.push_back(n);
	}

	int a, b, n = 0;
	int counter = 0;
	while(true)
	{
		a = 0;
		b = 0;
		for (int i = 0; i < n; ++i)
		{
			b *= std::pow(10, static_cast<int>(std::log10(num[i]) + 1));
			a += num[i];
		}
		for (int i = n; i < num.size(); ++i)
		{
			b *= std::pow(10,static_cast<int>(std::log10(num[i]) + 1));
			b += num[i];
		}
		if (a > b) counter++;
		if (n == num.size()) break;
		n++;
	}
	cout << counter << endl;
}