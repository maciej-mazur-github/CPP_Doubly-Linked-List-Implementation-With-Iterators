#pragma once


#include <iostream>
#include <string.h>
#include <conio.h>
using namespace std;


template <class T>
class List;

template <class T>
class IteratorDll;

template <class T>
ostream& operator<<(ostream& out, List<T>& arg);

template <class T>
class List
{
	string listName;
protected:
	struct Node
	{
		T* objPtr;
		Node* nextNodePtr;
		Node* previousNodePtr;
		Node()
			: nextNodePtr(NULL), previousNodePtr(NULL), objPtr(NULL) {}
	};

	Node* firstNodePtr;
	Node* lastNodePtr;

	int elementCounter;
	typedef IteratorDll<T> IterDll;

public:
	List(string name = "No-name List")
	{
		firstNodePtr = lastNodePtr = NULL;
		elementCounter = 0;
		listName = name;
	}

	friend ostream& operator<< <T>(ostream& out, List<T>& arg);
	friend class IteratorDll<T>;

	void addElement(T& obj);
	void addElement(T& obj, typename IterDll& iter);
	void addElement(T& obj, int position);

	void removeElement();
	void removeElement(typename IterDll& iter);
	void removeElement(int position);



	void printChosenElement(typename IterDll& iter) const
	{
		if (!firstNodePtr)
			return;

		else
			cout << *iter;
	}


	~List();


private:
	void addElementAsFirst(Node* newlyAddedNodePtr, IterDll& iter);
	void addElementAsLast(Node* newlyAddedNodePtr, IterDll& iter);
	void addElementInMiddle(Node* newlyAddedNodePtr, IterDll& iter);

	void removeLastElement(IterDll& iter);
	void removeFirstElement(IterDll& iter);
	void removeMiddleElement(IterDll& iter);
};
//##################################################################################
//##################################################################################



template <class T>
List<T>::~List()
{
	IterDll iter(*this);
	IterDll tempIter(*this);


	if (!iter.chosenNodePtr)
		return;

	for (; iter.chosenNodePtr; )
	{
		tempIter.chosenNodePtr = iter.chosenNodePtr->nextNodePtr;
		delete iter.chosenNodePtr;
		iter = tempIter;
	}
}


template <class T>
void List<T>::addElement(T& obj, int position)
{
	IterDll iter(*this);
	iter.moveToPosition(position);
	addElement(obj, iter);
}


template <class T>
void List<T>::removeElement(int position)
{
	IterDll iter(*this);
	iter.moveToPosition(position);
	removeElement(iter);
}



template <class T>
void List<T>::removeElement()
{
	IterDll iter(*this);
	iter.setChosenAsLast();
	removeElement(iter);
}

template <class T>
void List<T>::removeLastElement(IterDll& iter)
{
	if (firstNodePtr == lastNodePtr)  // if this is 1-element list then after the operation the list becomes empty
	{
		delete iter.chosenNodePtr;    // free the memory

		firstNodePtr = lastNodePtr = iter.chosenNodePtr = NULL;
		return;
	}

	else if (firstNodePtr->nextNodePtr == lastNodePtr)   // if this is a 2-element list
	{
		delete iter.chosenNodePtr;
		lastNodePtr = iter.chosenNodePtr = firstNodePtr;
		firstNodePtr->nextNodePtr = NULL;
		return;
	}

	else
	{
		typename List<T>::Node* penultimate = lastNodePtr->previousNodePtr;
		delete lastNodePtr;
		penultimate->nextNodePtr = NULL;
		lastNodePtr = penultimate;
		iter.chosenNodePtr = lastNodePtr;
	}
}





template <class T>
void List<T>::removeFirstElement(IterDll& iter)
{
	// 1-element list scenario has been covered in removeLastElement()

	if (firstNodePtr->nextNodePtr == lastNodePtr) // 2-element list scenario
	{
		delete firstNodePtr;
		firstNodePtr = lastNodePtr;  // the list becomes a 1-element one
		iter.chosenNodePtr = firstNodePtr;
		firstNodePtr->previousNodePtr = NULL;
	}

	else
	{
		Node* second_Node = firstNodePtr->nextNodePtr;
		delete firstNodePtr;
		firstNodePtr = second_Node;
		iter.chosenNodePtr = firstNodePtr;
		firstNodePtr->previousNodePtr = NULL;
	}
}

template <class T>
void List<T>::removeMiddleElement(IterDll& iter)
{
	typename List<T>::Node* previous_Node = iter.chosenNodePtr->previousNodePtr;
	typename List<T>::Node* next_Node = iter.chosenNodePtr->nextNodePtr;

	delete iter.chosenNodePtr;
	previous_Node->nextNodePtr = next_Node;
	next_Node->previousNodePtr = previous_Node;
	iter.chosenNodePtr = previous_Node;
}


template <class T>
void List<T>::removeElement(typename IterDll& iter)
{
	if (!firstNodePtr || !iter.chosenNodePtr)
		return;

	if (iter.chosenNodePtr == lastNodePtr)
		removeLastElement(iter);

	else if (iter.chosenNodePtr == firstNodePtr)
	{
		removeFirstElement(iter);
	}

	else
		removeMiddleElement(iter);


	elementCounter--;
}




template <class T>
ostream& operator<<(ostream& out, List<T>& arg)
{
	cout << "********************\n";
	cout << arg.listName << " current status:\n";

	if (arg.elementCounter == 0)
	{
		cout << "\nThe list " << arg.listName << " is empty\n";
		return out;
	}

	IteratorDll<T> bishop(arg);

	for (int i = 1; i <= arg.elementCounter; i++)
	{
		cout << *(bishop++) << "\t";

		/*if (!(i % 3) && i != 0)
			cout << "\n";*/
	}
	cout << "\n********************\n";

	out << endl << endl;
	return out;
}



template <class T>
void List<T>::addElementInMiddle(Node* newlyAddedNodePtr, IterDll& iter)
{
	Node* previous_Node = iter.chosenNodePtr->previousNodePtr;
	previous_Node->nextNodePtr = newlyAddedNodePtr;
	newlyAddedNodePtr->previousNodePtr = previous_Node;
	newlyAddedNodePtr->nextNodePtr = iter.chosenNodePtr;
	iter.chosenNodePtr->previousNodePtr = newlyAddedNodePtr;
	iter.chosenNodePtr = newlyAddedNodePtr;
}


template <class T>
void List<T>::addElementAsLast(Node* newlyAddedNodePtr, IterDll& iter)
{
	lastNodePtr->nextNodePtr = newlyAddedNodePtr;
	newlyAddedNodePtr->previousNodePtr = lastNodePtr;
	lastNodePtr = newlyAddedNodePtr;
}



template <class T>
void List<T>::addElementAsFirst(Node* newlyAddedNodePtr, IterDll& iter)
{
	if (!firstNodePtr)   // in case the list is empty yet
	{
		firstNodePtr = newlyAddedNodePtr;
		lastNodePtr = newlyAddedNodePtr;
	}
	else
	{
		newlyAddedNodePtr->nextNodePtr = firstNodePtr;
		firstNodePtr->previousNodePtr = newlyAddedNodePtr;
		firstNodePtr = newlyAddedNodePtr;
		iter.chosenNodePtr = firstNodePtr;
	}
}


template <class T>
void List<T>::addElement(T& obj, typename IterDll& iter)
{
	Node* newNodePtr = new Node;
	newNodePtr->objPtr = &obj;

	if (!firstNodePtr || iter.chosenNodePtr == firstNodePtr)
		addElementAsFirst(newNodePtr, iter);
	else
	{
		if (!iter.chosenNodePtr)
		{
			addElementAsLast(newNodePtr, iter);
		}
		else
		{
			addElementInMiddle(newNodePtr, iter);
		}
	}

	elementCounter++;
}



template <class T>
void List<T>::addElement(T& obj)
{
	Node* newNodePtr = new Node;
	newNodePtr->objPtr = &obj;

	IterDll iter(*this);
	iter.setChosenAfterLast();
	addElement(obj, iter);
}



//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************


template <class T>
class IteratorDll;

template <class T>
class List;

template <class T>
class IteratorDll
{
	friend class List<T>;
	List<T>& dll;
	typename List<T>::Node* chosenNodePtr;
public:
	IteratorDll(typename List<T>& worklist)
		: dll(worklist)
	{
		chosenNodePtr = worklist.firstNodePtr;
	}


	T& operator*();


	IteratorDll& setChosenAsFirst()
	{
		if (dll.firstNodePtr)
			chosenNodePtr = dll.firstNodePtr;

		return *this;
	}

	IteratorDll& setChosenAsLast()
	{
		if (dll.lastNodePtr)
			chosenNodePtr = dll.lastNodePtr;

		return *this;
	}

	IteratorDll& setChosenAfterLast()
	{
		chosenNodePtr = NULL;
		return *this;
	}

	IteratorDll& operator++()
	{
		if (!chosenNodePtr)
			return *this;

		chosenNodePtr = chosenNodePtr->nextNodePtr;
		return *this;
	}

	IteratorDll operator++(int)
	{
		if (!chosenNodePtr)
			return *this;

		IteratorDll temp = *this;
		chosenNodePtr = chosenNodePtr->nextNodePtr;
		return temp;
	}

	IteratorDll& operator--()
	{
		if (!chosenNodePtr)
			return *this;

		chosenNodePtr = chosenNodePtr->previousNodePtr;
		return *this;
	}

	IteratorDll& operator=(const IteratorDll& rhs)
	{
		dll = rhs.dll;
		chosenNodePtr = rhs.chosenNodePtr;
		return *this;
	}


	IteratorDll operator--(int)
	{
		if (!chosenNodePtr)
			return *this;

		IteratorDll temp = *this;
		chosenNodePtr = chosenNodePtr->previousNodePtr;
		return temp;
	}

	int operator==(const IteratorDll& rhs)
	{
		if (chosenNodePtr == rhs.chosenNodePtr)
			return 1;
		else
			return 0;
	}

	int operator!=(const IteratorDll& rhs)
	{
		if (chosenNodePtr == rhs.chosenNodePtr)
			return 0;
		else
			return 1;
	}

	operator int()
	{
		if (chosenNodePtr != NULL)
			return 1;
		else
			return 0;
	}

	IteratorDll& moveToPosition(int position)
	{
		if (!dll.firstNodePtr)
			return *this;

		if (position >= dll.elementCounter)
			setChosenAfterLast();
		else
		{
			setChosenAsFirst();

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
T& IteratorDll<T>::operator*()
{
	if (chosenNodePtr)
		return *(chosenNodePtr->objPtr);

	else
	{
		throw "Iterator pointing at nothing";
	}

}


