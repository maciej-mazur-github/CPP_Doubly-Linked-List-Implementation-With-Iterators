#pragma once
#pragma once

#include <iostream>
#include <string.h>
#include <conio.h>
using namespace std;


template <class T>
class list;

template <class T>
class Iterator_Dll;

template <class T>
ostream& operator<<(ostream& out, list<T>& arg);

template <class T>
class list
{
protected:
	struct node
	{
		T* obj_ptr;
		node* next_node_ptr;
		node* previous_node_ptr;
		node()
			: next_node_ptr(NULL), previous_node_ptr(NULL), obj_ptr(NULL) {}
	};

	node* first_node_ptr;
	node* last_node_ptr;

	int element_counter;
	typedef Iterator_Dll<T> iter_dll;

public:
	list()
	{
		first_node_ptr = last_node_ptr = NULL;
		element_counter = 0;
	}

	friend ostream& operator<< <T>(ostream& out, list<T>& arg);
	friend class Iterator_Dll<T>;

	void add_element(T& obj);
	void add_element(T& obj, typename iter_dll& iter);
	void add_element(T& obj, int position);

	void remove_element();
	void remove_element(typename iter_dll& iter);
	void remove_element(int position);



	void print_chosen_element(typename iter_dll& iter) const
	{
		if (!first_node_ptr)
			return;

		else
			cout << *iter;
	}


	~list();


private:
	void add_element_as_first(node* newly_added_node_ptr, iter_dll& iter);
	void add_element_as_last(node* newly_added_node_ptr, iter_dll& iter);
	void add_element_in_middle(node* newly_added_node_ptr, iter_dll& iter);

	void remove_last_element(iter_dll& iter);
	void remove_first_element(iter_dll& iter);
	void remove_middle_element(iter_dll& iter);
};
//##################################################################################
//##################################################################################



template <class T>
list<T>::~list()
{
	iter_dll iter(*this);
	iter_dll temp_iter(*this);


	if (!iter.chosen_node_ptr)
		return;

	for (; iter.chosen_node_ptr; )
	{
		temp_iter.chosen_node_ptr = iter.chosen_node_ptr->next_node_ptr;
		delete iter.chosen_node_ptr;
		iter = temp_iter;
	}
}


template <class T>
void list<T>::add_element(T& obj, int position)
{
	iter_dll iter(*this);
	iter.move_to_position(position);
	add_element(obj, iter);
}


template <class T>
void list<T>::remove_element(int position)
{
	iter_dll iter(*this);
	iter.move_to_position(position);
	remove_element(iter);
}



template <class T>
void list<T>::remove_element()
{
	iter_dll iter(*this);
	iter.set_chosen_as_last();
	remove_element(iter);
}

template <class T>
void list<T>::remove_last_element(iter_dll& iter)
{
	if (first_node_ptr == last_node_ptr)  // if this is 1-element list then after the operation the list becomes empty
	{
		delete iter.chosen_node_ptr;    // free the memory

		first_node_ptr = last_node_ptr = iter.chosen_node_ptr = NULL;
		return;
	}

	else if (first_node_ptr->next_node_ptr == last_node_ptr)   // if this is a 2-element list
	{
		delete iter.chosen_node_ptr;
		last_node_ptr = iter.chosen_node_ptr = first_node_ptr;
		first_node_ptr->next_node_ptr = NULL;
		return;
	}

	else
	{
		typename list<T>::node* penultimate = last_node_ptr->previous_node_ptr;
		delete last_node_ptr;
		penultimate->next_node_ptr = NULL;
		last_node_ptr = penultimate;
		iter.chosen_node_ptr = last_node_ptr;
	}
}





template <class T>
void list<T>::remove_first_element(iter_dll& iter)
{
	// 1-element list scenario has been covered in remove_last_element()

	if (first_node_ptr->next_node_ptr == last_node_ptr) // 2-element list scenario
	{
		delete first_node_ptr;
		first_node_ptr = last_node_ptr;  // the list becomes a 1-element one
		iter.chosen_node_ptr = first_node_ptr;
		first_node_ptr->previous_node_ptr = NULL;
	}

	else
	{
		node* second_node = first_node_ptr->next_node_ptr;
		delete first_node_ptr;
		first_node_ptr = second_node;
		iter.chosen_node_ptr = first_node_ptr;
		first_node_ptr->previous_node_ptr = NULL;
	}
}

template <class T>
void list<T>::remove_middle_element(iter_dll& iter)
{
	typename list<T>::node* previous_node = iter.chosen_node_ptr->previous_node_ptr;
	typename list<T>::node* next_node = iter.chosen_node_ptr->next_node_ptr;

	delete iter.chosen_node_ptr;
	previous_node->next_node_ptr = next_node;
	next_node->previous_node_ptr = previous_node;
	iter.chosen_node_ptr = previous_node;
}


template <class T>
void list<T>::remove_element(typename iter_dll& iter)
{
	if (!first_node_ptr || !iter.chosen_node_ptr)
		return;

	if (iter.chosen_node_ptr == last_node_ptr)
		remove_last_element(iter);

	else if (iter.chosen_node_ptr == first_node_ptr)
	{
		remove_first_element(iter);
		//return;
	}

	else
		remove_middle_element(iter);


	element_counter--;
}




template <class T>
ostream& operator<<(ostream& out, list<T>& arg)
{
	if (arg.element_counter == 0)
	{
		cout << "\nThe list is empty\n";
		return out;
	}

	Iterator_Dll<T> bishop(arg);

	for (int i = 1; i <= arg.element_counter; i++)
	{
		cout << *(bishop++) << "\t";

		if (!(i % 3) && i != 0)
			cout << "\n";
	}

	out << endl << endl;
	return out;
}



template <class T>
void list<T>::add_element_in_middle(node* newly_added_node_ptr, iter_dll& iter)
{
	node* previous_node = iter.chosen_node_ptr->previous_node_ptr;
	previous_node->next_node_ptr = newly_added_node_ptr;
	newly_added_node_ptr->previous_node_ptr = previous_node;
	newly_added_node_ptr->next_node_ptr = iter.chosen_node_ptr;
	iter.chosen_node_ptr->previous_node_ptr = newly_added_node_ptr;
	iter.chosen_node_ptr = newly_added_node_ptr;
}


template <class T>
void list<T>::add_element_as_last(node* newly_added_node_ptr, iter_dll& iter)
{
	last_node_ptr->next_node_ptr = newly_added_node_ptr;
	newly_added_node_ptr->previous_node_ptr = last_node_ptr;
	last_node_ptr = newly_added_node_ptr;
}



template <class T>
void list<T>::add_element_as_first(node* newly_added_node_ptr, iter_dll& iter)
{
	if (!first_node_ptr)   // in case the list is empty yet
	{
		first_node_ptr = newly_added_node_ptr;
		last_node_ptr = newly_added_node_ptr;
	}
	else
	{
		newly_added_node_ptr->next_node_ptr = first_node_ptr;
		first_node_ptr->previous_node_ptr = newly_added_node_ptr;
		first_node_ptr = newly_added_node_ptr;
		iter.chosen_node_ptr = first_node_ptr;
	}
}


template <class T>
void list<T>::add_element(T& obj, typename iter_dll& iter)
{
	node* new_node_ptr = new node;
	new_node_ptr->obj_ptr = &obj;

	if (!first_node_ptr || iter.chosen_node_ptr == first_node_ptr)
		add_element_as_first(new_node_ptr, iter);
	else
	{
		if (!iter.chosen_node_ptr)
		{
			add_element_as_last(new_node_ptr, iter);
		}
		else
		{
			add_element_in_middle(new_node_ptr, iter);
		}
	}

	element_counter++;
}



template <class T>
void list<T>::add_element(T& obj)
{
	node* new_node_ptr = new node;
	new_node_ptr->obj_ptr = &obj;

	iter_dll iter(*this);
	iter.set_chosen_after_last();
	add_element(obj, iter);
}



//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************


template <class T>
class Iterator_Dll;

template <class T>
class list;

template <class T>
class Iterator_Dll
{
	friend class list<T>;
	list<T>& dll;
	typename list<T>::node* chosen_node_ptr;
public:
	Iterator_Dll(typename list<T>& worklist)
		: dll(worklist)
	{
		chosen_node_ptr = worklist.first_node_ptr;
	}


	T& operator*();


	Iterator_Dll& set_chosen_as_first()
	{
		if (dll.first_node_ptr)
			chosen_node_ptr = dll.first_node_ptr;

		return *this;
	}

	Iterator_Dll& set_chosen_as_last()
	{
		if (dll.last_node_ptr)
			chosen_node_ptr = dll.last_node_ptr;

		return *this;
	}

	Iterator_Dll& set_chosen_after_last()
	{
		chosen_node_ptr = NULL;
		return *this;
	}

	Iterator_Dll& operator++()
	{
		if (!chosen_node_ptr)
			return *this;

		chosen_node_ptr = chosen_node_ptr->next_node_ptr;
		return *this;
	}

	Iterator_Dll operator++(int)
	{
		if (!chosen_node_ptr)
			return *this;

		Iterator_Dll temp = *this;
		chosen_node_ptr = chosen_node_ptr->next_node_ptr;
		return temp;
	}

	Iterator_Dll& operator--()
	{
		if (!chosen_node_ptr)
			return *this;

		chosen_node_ptr = chosen_node_ptr->previous_node_ptr;
		return *this;
	}

	Iterator_Dll& operator=(const Iterator_Dll& rhs)
	{
		dll = rhs.dll;
		chosen_node_ptr = rhs.chosen_node_ptr;
		return *this;
	}


	Iterator_Dll operator--(int)
	{
		if (!chosen_node_ptr)
			return *this;

		Iterator_Dll temp = *this;
		chosen_node_ptr = chosen_node_ptr->previous_node_ptr;
		return temp;
	}

	int operator==(const Iterator_Dll& rhs)
	{
		if (chosen_node_ptr == rhs.chosen_node_ptr)
			return 1;
		else
			return 0;
	}

	int operator!=(const Iterator_Dll& rhs)
	{
		if (chosen_node_ptr == rhs.chosen_node_ptr)
			return 0;
		else
			return 1;
	}

	operator int()
	{
		if (chosen_node_ptr != NULL)
			return 1;
		else
			return 0;
	}

	Iterator_Dll& move_to_position(int position)
	{
		if (!dll.first_node_ptr)
			return *this;

		if (position >= dll.element_counter)
			set_chosen_after_last();
		else
		{
			set_chosen_as_first();

			for (int i = 0; i < position; i++)
			{
				++(*this);
			}
		}

		return *this;
	}


};
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

template <class T>
T& Iterator_Dll<T>::operator*()
{
	if (chosen_node_ptr)
		return *(chosen_node_ptr->obj_ptr);

	else
	{
		T temp = NULL;
		return temp;
	}

}



template <>
string& Iterator_Dll<string>::operator*()
{
	if (chosen_node_ptr)
		return *(chosen_node_ptr->obj_ptr);

	else
	{
		string temp;
		return temp;
	}

}