#pragma once

// Justin Harper
// 10696738
// CptS 223 - Advanced Data Structures
// Homework assignment #1

#include <iostream>
#include "LinkedList.h"

using namespace std;

class ReversibleStack
{
private:
	LinkedList* stack;



public:
	ReversibleStack()
	{
		stack = new LinkedList{};

	}
	string header(void)
	{
		return "Justin Harper - WSU ID: 10696738";
	}

	void push(int newData)
	{
		stack->addToTop(newData);
	}

	int pop(void)
	{
		return stack->removeFromTop();

	}

	void reverse(void)
	{
		LinkedList* newLL = new LinkedList{};
		while (stack->isListEmpty() == false)
		{
			int x = stack->removeFromTop();
			newLL->addToTop(x);
		}

		stack = newLL;

	}

	bool isEmpty()
	{
		return stack->isListEmpty();
	}


};