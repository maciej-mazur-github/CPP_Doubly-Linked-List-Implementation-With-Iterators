#include <iostream>
#include "Doubly_linked_list_iterators.h"
#include "Person.h"


int main()
{
	list<int> list1;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4, e = 5;
	list1.add_element(a);
	list1.add_element(b);
	list1.add_element(c);
	cout << list1;


	Iterator_Dll<int> iter(list1);
	list1.add_element(c, iter);
	cout << list1;
	iter++;
	list1.add_element(e, iter);
	cout << list1;

	iter.move_to_position(2);
	list1.add_element(e, iter);
	cout << list1;

	iter.set_chosen_after_last();
	list1.add_element(e, iter);
	cout << list1;

	list1.remove_element(iter);
	cout << list1;

	iter.set_chosen_as_last();
	list1.remove_element(iter);
	cout << list1;

	list1.remove_element(iter);
	cout << list1;

	iter.set_chosen_as_first();
	list1.remove_element(iter);
	cout << list1;

	iter.move_to_position(10);
	list1.remove_element(iter);
	cout << list1;

	iter.set_chosen_as_first();
	list1.remove_element(iter);
	cout << list1;

	cout << *iter;
	cout << *(++iter);

	iter++;
	cout << *iter;

	iter++;
	cout << *iter;

	list<string> list2;
	string s1 = "Dupa1",
		s2 = "Dupa2",
		s3 = "Dupa3";

	list2.add_element(s1);
	list2.add_element(s2);
	list2.add_element(s3);

	Iterator_Dll<string> iter2(list2);

	cout << "\n\n" << *iter2 << endl;

	//cout << "\n\n" << list1;


	list<person> list3;
	person person1("Caroline"), person2("Meggy"), person3("Jenny");
	Iterator_Dll<person> iter3(list3);

	list3.add_element(person1);
	list3.add_element(person2);
	list3.add_element(person3);

	cout << "\n\n" << list3;

	iter3.set_chosen_as_first();
	*iter3 = "Judith";
	cout << "\n\n" << *iter3;


}