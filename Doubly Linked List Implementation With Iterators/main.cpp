#include <iostream>
#include "DLL_with_iterators.h"
#include "person.h"


int main()
{
	List<int> list1;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4, e = 5;
	list1.addElement(a);
	list1.addElement(b);
	list1.addElement(c);
	cout << list1;


	IteratorDll<int> iter(list1);
	list1.addElement(c, iter);
	cout << list1;
	iter++;
	list1.addElement(e, iter);
	cout << list1;

	iter.moveToPosition(2);
	list1.addElement(e, iter);
	cout << list1;

	iter.setChosenAfterLast();
	list1.addElement(e, iter);
	cout << list1;

	list1.removeElement(iter);
	cout << list1;

	iter.setChosenAsLast();
	list1.removeElement(iter);
	cout << list1;

	list1.removeElement(iter);
	cout << list1;

	iter.setChosenAsFirst();
	list1.removeElement(iter);
	cout << list1;

	iter.moveToPosition(10);
	list1.removeElement(iter);
	cout << list1;

	iter.setChosenAsFirst();
	list1.removeElement(iter);
	cout << list1;

	cout << *iter;
	cout << *(++iter);

	iter++;
	cout << *iter;

	iter++;
	cout << *iter;

	List<string> list2;
	string s1 = "Dupa1",
		s2 = "Dupa2",
		s3 = "Dupa3";

	list2.addElement(s1);
	list2.addElement(s2);
	list2.addElement(s3);

	IteratorDll<string> iter2(list2);

	cout << "\n\n" << *iter2 << endl;

	//cout << "\n\n" << list1;


	List<Person> list3;
	Person person1("Caroline"), person2("Meggy"), person3("Jenny");
	IteratorDll<Person> iter3(list3);

	list3.addElement(person1);
	list3.addElement(person2);
	list3.addElement(person3);

	cout << "\n\n" << list3;

	iter3.setChosenAsFirst();
	*iter3 = "Judith";
	cout << "\n\n" << *iter3;


}