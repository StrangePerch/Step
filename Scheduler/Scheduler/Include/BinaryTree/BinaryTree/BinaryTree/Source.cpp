
#include <ctime>
#include <iostream>


#include "../../AVLTree.h"


void main()
{
	srand(time(nullptr));
	av::AVLTree<int,int> a;
	for (size_t i = 1; i <= 30000; i++)
	{
		auto r = 0;
		while(a.push(r) == nullptr) r = rand() % 30000;
	}
	system("pause");
	while (true)
	{
		a.menu();
	}
}