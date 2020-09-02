#include "iostream.h"
#include "string.h"
#include "fstream.h"

#include "Composite.h"


int main()
{
	Component* comp = new Folder("FileSystem");
	Component* folder1 = new Folder("Folder1");
	Component* folder2 = new Folder("Folder2");
	Component* folder3 = new Folder("Folder3");
	Component* file1 = new File("File1");
	Component* file2 = new File("File2");
	Component* file3 = new File("File3");
	Component* file4 = new File("File4");
	comp->add(folder1);
	folder1->add(folder2);
	folder1->add(folder3);
	comp->add(file1);
	folder2->add(file2);
	folder3->add(file3);
	folder3->add(file4);
	comp->print();

}