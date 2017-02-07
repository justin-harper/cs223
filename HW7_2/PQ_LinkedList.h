//Justin Harper
//10696738
//HW7_Heaps


#ifndef PQLLH
#define PQLLH

#include "PQBase.h"

template <typename T>
class PQ_LinkedList : public PQBase < T >
{
	// Implement this class - maintain a sorted linked - list internally where
	// the list is always sorted in descending order and therefore the 
	// max is always accessible and removable in constant time.


	//This will use a Linked List so we need to define what a node is
private:
	struct Node
	{
		T* data;
		 Node* next;


		Node(T* value)
		{
			data = value;
			next = nullptr;
		}
	};
	
	Node* m_head = nullptr;
public:
	// Implement this class - maintain a sorted linked-list internally where 
	// the list is always sorted in descending order and therefore the 
	// max is always accessible and removable in constant time.
	//is empty is root is null
	bool IsEmpty() const 
	{
		if (m_head == nullptr)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	//male a copy of toCopyAndAdd 
	//since we cant modify the const
	//also make a new element which is a new node with that element
	void Add(const T& toCopyAndAdd) 
	{
		//need to create a copy of toCopyAndAdd
		//otherwise it will go out of scope
		//and cause problems

		T* copy = new T(toCopyAndAdd);

		//now put copy into a new node
		Node* newNode = new Node(copy);

		//and add it to the list
		m_head = AddHelper(m_head, copy);
	

	}

	//data is less than value, then insert at the end
	//then do recursion for it.
	Node* AddHelper(Node* head, T* value)
	{
		Node* newNode;
		if (nullptr == head || *head->data <= *value)
		{	//base case
			//inserting at the head of the list
			//note this is a recursive function
			//so "head" maybe a node in the list
			//not necisarrly m_head
			newNode = new Node(value);

			newNode->data = value;
			newNode->next = head;
			
			return newNode;
		}
		else
		{
			//move to the next node and
			//check again
			head->next = AddHelper(head->next, value);
			return head;
		}


	}

	//this is a sorted linked list
	//the max value is always at the front
	//so "pop" it off and reassign m_head
	bool RemoveMax(T& outputItem) 
	{	//base case
		if (nullptr == m_head)
		{
			return 0;
		}
		
			outputItem = *m_head->data;
			Node* temp = m_head;
			m_head = m_head->next;

			//delete dynamicaly created Node
			delete temp;

			return 1;

	}


};
#endif