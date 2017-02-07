#pragma once

// Justin Harper
// 10696738
// CptS 223 - Advanced Data Structures
// Homework assignment #1


#include "Node.h"
 

using namespace std;


class LinkedList
{
private:
	Node* root;
	bool isEmpty = true;

	
public:
	LinkedList()
	{
		root = nullptr;
	}
	void addToTop(int value)
	{

		Node* temp = new Node{value, root};
		root = temp;
		isEmpty = false;

	}

	int removeFromTop(void)
	{
		int x = 0x80000000;

		if (root != nullptr)
		{
			x = root->getData();
			root = root->getNext();
		}
		if (root == nullptr)
		{
			isEmpty = true;
		}
		return x;

	}

	bool isListEmpty(void) const
	{
		return isEmpty;
	}



};

