#include <iostream>

#include "../../SmartPointer.h"
#include "../../../String/Str.h"
using namespace  std;

void main()
{
	int* i = new int(5);
	shared_ptr<int> a(i);
	shared_ptr<int> b(i);
	cout << a.use_count() << endl;
	a.owner_before();
	system("pause");
}