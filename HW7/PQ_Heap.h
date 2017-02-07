#ifndef PQHEAPH
#define PQHEAPH

#include "PQBase.h"
#include <queue>
#include <vector>

template <typename T>
class PQ_Heap : public PQBase<T>
{
private:
	// Declare the private member variables you need here.
	// Store the heap data in an array or a std::vector.
	int m_k;
	std::vector<T*> m_heap;
	int m_lastUsedIndex;
	bool m_empty;



public:
	
	//Default constructor k = 2
	PQ_Heap()
	{
		m_k = 2;
		m_lastUsedIndex = -1;
		m_empty = true
	}
	
	PQ_Heap(int k)
	{
		// Implement this constructor so that it stores k and uses it in 
		// the appropriate member functions to build a k-ary heap for 
		// the priorty queue.

		m_k = k;
		m_lastUsedIndex = -1;
		m_empty = true;




	}

	~PQ_Heap()
	{
		
	}

	void Add(const T& toCopyAndAdd)
	{
		T* copy = new T (toCopyAndAdd);
		if (m_empty == true)
		{
			//heap is empty

			m_heap.push_back(copy);
			m_lastUsedIndex = 0;
			m_empty = false;
		}
		else
		{
			//when adding to heap always insert at the end and sift up
			m_heap.push_back(copy);
			m_lastUsedIndex++;

			siftUp(m_lastUsedIndex);

		}




		return;
	}

	//ensures valid heap after insertion
	void siftUp(int index)
	{
		//parent Index is located at (n-1)/k note integer division
		//n is the current node, k is the number of children

		//child nodes are located at kn+1 ..kn+2 ..kn+k

		//step 1 see if parent is in bounds of the vector
		//if not index is root

		if ((index - 1) / m_k < 0)
		{
			//parrent does not exist...
			return;
		}

		//step 2...compare value at index with its parrent

		else if (m_heap[index] > m_heap[((index - 1) / m_k)])
		{
			//current is greater and must be sifted up

			//swap values

			T* temp = m_heap[index];
			m_heap[index] = m_heap[((index - 1) / m_k)];
			m_heap[((index - 1) / m_k)] = temp;

			//values have been swapped now check if heap[((index - 1) / m_k)] is greater than its parrent

			siftUp((index - 1) / m_k);

		}
		//current is valid
		return;

	}

	bool IsEmpty() const
	{
		return m_empty;
	}


	bool RemoveMax(T& outputItem)
	{
		//check to see if there is a value to return
		if (m_empty == true)
		{	
			//if not return false
			return false;
		}
		else
		{
			outputItem = *m_heap[0];

			//swap heap[0] with heap[lastIndexUsed]
			//then delete heap[lastIndexUsed] which is a leafNode
			//then sift down until heap is valid

			m_heap[0] = m_heap[m_lastUsedIndex];
			delete m_heap[m_lastUsedIndex];
			m_lastUsedIndex--;

			siftDown(0);
			return true;

		}
	}

	
	void siftDown(int index)
	{
		//get index of maxChild if it exists
		int maxChildIndex = maxChild(index);


		if (maxChildIndex == -1)
		{
			//index is a leaf node and is in the correct spot
			return;
		}
		else
		{
			//compare current index value with children
			//replace current with max of children if child is greater

			if (m_heap[index] < m_heap[maxChildIndex])
			{
				//swap values and sift again
				T* temp = m_heap[index];
				m_heap[index] = m_heap[maxChildIndex];
				m_heap[maxChildIndex] = temp;

				//sift at index of maxChild
				//as that is where the swap occured
				siftDown(maxChildIndex);

			}
			else
			{
				//index is in the correct spot
				return;
			}

		}

	}

	//returns index of child with max value
	int maxChild(int parentIndex)
	{
		int index = -1;
		T max = *m_heap[parentIndex];

		//child nodes are located at kn+1 ..kn+2 ..kn+k
		for (int i = 1; i <= m_k; i++)
		{
			//make sure (m_k*parentIndex) + i is within bounds of m_heap
			
			if ((m_k*parentIndex) + i > m_lastUsedIndex)
			{
				//(m_k*parentIndex) + i > LastIndexUsed is outside the bounds
				//there are no more children ... no need to continue checking
				
				return index;
			}
			

			if (max < *m_heap[(m_k*parentIndex) + i])
			{
				
				max =*m_heap[(m_k*parentIndex) + i];
				index = (m_k*parentIndex) + i;
			}
		}

		//all k children exist return index of greatest
		
		return index;

	}


	// Implement the rest of this class
};
#endif