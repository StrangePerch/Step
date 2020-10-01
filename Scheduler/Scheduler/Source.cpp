#include <iostream>
#include "Scheduler.h"
#include <list>

using namespace std;

void main()
{
	

	Scheduler* main = Scheduler::getInstance();

	/*main->add(
		new Task("EXAM", "Finish exam for step\nThema: patters\nLanguage: c++", "Step",
			new Date(1,10,2020,18,0)));
	main->add(
		new Task("Title1", "blablablabla", "School",
			new	Date(5,2,1987,12,0), new Date(6,10,2012,12,0)));
	main->add(
		new Task("Title2", "blablablabla", "School",
			new Date(28, 9, 2020, 20, 0)));
	main->add(
		new Task("Title3", "blablablabla", "Other",
			new Date(28, 9, 2020, 19, 0)));*/

	main->main_menu();
	main->save();
	
}