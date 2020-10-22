
#include <iostream>
#include <vector>

using namespace std;

void print_array(vector<int>& vec)
{
	for (int temp : vec)
	{
		cout << temp << " ";
	}
	cout << endl;
}

void del(vector<int>& vec, int ind)
{
	if (ind == 0) vec.erase(vec.begin());
	else if (ind == vec.size() - 1) vec.pop_back();
	else
	{
		vec[ind] = vec[ind - 1] + vec[ind + 1];
		vec.erase(vec.begin() + ind - 1);
		vec.erase(vec.begin() + ind);
	}
}

void main()
{
	vector<int> result;
	vector<int> input;

	int n;
	cin >> n;


	for (int i = 0; i < n; ++i)
	{
		int temp;
		cin >> temp;
		input.push_back(temp);
	}

	while(true)
	{
		print_array(input);
		int ind;
		cin >> ind;
		result.push_back(ind);
		ind--;
		del(input, ind);
		if (input.size() == 1) break;
	}
	result.insert(result.begin(), result.size());
	result.insert(result.begin(), input[0]);
	print_array(result);
	system("pause");
}
