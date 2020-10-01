#include <iostream>

#include "../../Vect.h"

using namespace std;

void fill_array(av::Vect <int> &vector, const int size = 10)
{
	for (size_t i = 0; i < size; i++)
	{
		vector.push_back(rand() % 100);
	}
}

int main()
{
	av::Vect <int> vector;
	vector.push_back(15);
	cout << vector << endl;
	vector.insert(0, 10);
	cout << vector << endl;
	vector.pop_back(2);
	cout << vector << endl;
	fill_array(vector);
	cout << vector << endl;
	vector.erase(2, 5);
	cout << vector << endl;
	vector.insert(3, 99);
	cout << vector << endl;
	cout << vector[4] << endl;
	av::Vect <int> a,b;
	a = b = vector;
	cout << a << endl;
	cout << b << endl;
	av::Vect <int> c = vector;
	cout << c << endl;
	c += 100;
	cout << c << endl;
	c -= 5;
	cout << c << endl;
	system("pause");
}