#ifndef PQLLH
#define PQLLH

#include "PQBase.h"

template <typename T>
class PQ_LinkedList : public PQBase < T >
{
	// Implement this class - maintain a sorted linked-list internally where 
	// the list is always sorted in descending order and therefore the 
	// max is always accessible and removable in constant time.


	//This will use a Linked List so we need to define what a node is
	
private:
	struct Node
	{
		T* value;
		Node* next;

		Node()
		{
			next = nullptr;
		}
		Node(T* data)
		{
			value = data;
			next = nullptr;
		}

		

	};


	Node* m_head;
	

public:

	PQ_LinkedList()
	{
		m_head = nullptr;
		
	}

	~PQ_LinkedList()
	{
		while (m_head != nullptr)
		{
			Node* temp = m_head;
			m_head = m_head->next;
			delete temp;
		}
	}


	T GetMax()
	{
		return *m_head->value;
	}

	void Add(const T& newVal)
	{
		//create new Node
		T* copy = new T(newVal);
		

		Node* newNode = new Node(copy);
		
		
		//put it in the correct sopt in the list

		//case 1: empty list ==> m_head is nullptr
		if (m_head == nullptr)
		{
			m_head = newNode;
			
			return;
		}
		else
		{
			AddHelp(newNode, m_head, nullptr);
		}
		

		

		

	}

	void AddHelp(Node* newNode, Node* current, Node* prev)
	{
		if (current == nullptr)
		{
			prev->next = newNode;
			return;
		}

		else if (newNode->value >= current->value)
		{
			if (prev == nullptr)
			{
				//replace m_head
				newNode->next = m_head;
				m_head = newNode;

			}
			else
			{
				prev->next = newNode;
				newNode->next = current;
			}


		}
		else
		{
			//go to the next node and check again
			AddHelp(newNode, current->next, current);

		}

	}



	bool IsEmpty() const
	{
		if (m_head == nullptr)
		{

			return true;
		}
		else
		{
			return false;
		}
	}


	bool RemoveMax(T& outputItem)
	{
		//two cases

		//case 1: m_head is nullptr
		if (m_head == nullptr)
		{
			return false;
		}
		//case 2: m_head is not nullptr
		else
		{
			outputItem = *m_head->value;
			Node* temp = m_head;
			m_head = m_head->next;

			delete temp;

			return true;

		}


	}





};
#endif