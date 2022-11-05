#include <iostream>
#include "DLL_with_iterators.h"
#include "person.h"


int main()
{
	List<int> list1("list1");
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


	try
	{
		cout << *iter;
	}
	catch (const char* message)
	{
		cerr << message << endl;
	}

	try
	{
		cout << *iter;
	}
	catch (const char* message)
	{
		cerr << message << endl;
	}

	try
	{
		cout << *(++iter) << endl;
	}
	catch (const char* message)
	{
		cerr << message << endl;
	}
	
	

	iter.setChosenAfterLast();

	try
	{
		cout << *iter;
	}
	catch (const char* message)
	{
		cerr << message << endl;
	}
	

	iter++;

	try
	{
		cout << *iter;
	}
	catch (const char* message)
	{
		cerr << message << endl;
	}
	

	List<string> list2("list2");
	string s1 = "word1",
		s2 = "word2",
		s3 = "word3";

	list2.addElement(s1);
	list2.addElement(s2);
	list2.addElement(s3);

	IteratorDll<string> iter2(list2);

	cout << "\n\n" << *iter2 << endl;
	iter2.setChosenAfterLast();

	try
	{
		cout << *iter2;
	}
	catch(const char* message)
	{
		cerr << message << endl;
	}
	

	iter2.setChosenAsFirst();
	list2.removeElement(iter2);
	cout << list2;


	List<Person> list3("list3");
	Person person1("Caroline"), person2("Meggy"), person3("Jenny");
	IteratorDll<Person> iter3(list3);

	list3.addElement(person1);
	list3.addElement(person2);
	list3.addElement(person3);

	cout << "\n\n" << list3;
	

	try
	{
		iter3.setChosenAsFirst();
		*iter3 = "Judith";
		cout << "\n\n" << *iter3;
	}
	catch (const char* message)
	{
		cerr << message << endl;
	}
}