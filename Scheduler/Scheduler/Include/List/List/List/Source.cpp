#include <iostream>
#include <list>


#include "../../List.h"

using namespace std;

int main()
{
	av::List<int> a;
	a.push_back(5);
	a.push_back(10);
	a.push_back(15);
	a.push_back(23);
	a.echo();
	a.push_front(555);
	a.push_back(555);
	a.echo();
	a.pop_front();
	a.echo();
	a.pop_back();
	a.echo();
	av::List<int>::iterator iterator_ = a.begin();
	++iterator_;
	iterator_ = 9;
	cout << iterator_ << endl;
	iterator_ = a.begin();
	cout << iterator_ << endl;
	++iterator_;
	cout << iterator_ << endl;
	iterator_ = a.end();
	--iterator_;
	--iterator_;
	cout << iterator_ << endl;
	a.echo();
	a.pop_pointer(a.min());
	a.echo();
	a.pop_pointer(a.max());
	a.echo();
	system("pause");
}