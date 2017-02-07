#pragma once

// Justin Harper
// 10696738
// CptS 223 - Advanced Data Structures
// Homework assignment #1

class Node
{
private:

	int data;
	Node* next;

public:
	Node()
	{
		next = nullptr;
		data = 0x8000000;
	}

	Node(int newData, Node* currentHeadOfList)
	{
		next = currentHeadOfList;
		data = newData;
	}
	
	int getData(void) const
	{
		return data;
	}

	Node* getNext(void) const
	{
		return next;
	}

};