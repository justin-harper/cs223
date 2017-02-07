//Justin Harper
//10696738
//HW7_Heaps


#ifndef PQHEAPH
#define PQHEAPH

#include "PQBase.h"
#include <queue>
#include <vector>


using namespace std;

template <typename T>

class PQ_Heap : public PQBase<T>
{

private:
	// Declare the private member variables you need here.
	// Store the heap data in an array or a std::vector.
	vector <T> m_heap;
	int m_k = 0;

public:
	PQ_Heap(int k)
	{
		// Implement this constructor so that it stores k and uses it in 
		// the appropriate member functions to build a k-ary heap for 
		// the priorty queue.

		m_k = k;


	}
	//if vector is is empty then return 1
	bool IsEmpty() const 
	{
		//empty is a vector member function
		if (m_heap.empty() == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	
	void Add(const T& toCopyAndAdd)
	{
		//get heap size
		//size is a vector member funtion
		int heapSize = m_heap.size();
		
		heapSize++;

		//push item to vector
		m_heap.push_back(toCopyAndAdd);

		//because heap size is 0 at first, so we need to do a -1
		SiftUp(heapSize - 1);

	}

	bool RemoveMax(T& outputItem) 
	{
		//cant remove if empty
		if (m_heap.empty() == true)
		{
			return false;
		}
		//if size is 2, then no need to do any sifting
		else if (m_heap.size() <= 2)
		{
			//reassign outputItem
			outputItem = m_heap[0];
			//move last entry in heap to the front
			m_heap[0] = m_heap[m_heap.size() - 1];

			//rezie down by 1...as that is nolonger a valid entry in the heap
			m_heap.resize(m_heap.size() - 1);

			return true;
		}
		//else take the first item and return it to outputitem
		//then resize it smaller by 1
		//and starting shifting down at the top
		else
		{
			//reassign outputItem
			outputItem = m_heap[0];

			//move last item in heap to the front
			m_heap[0] = m_heap[m_heap.size() - 1];

			//rezie heap as last entry is nolonger valid
			m_heap.resize(m_heap.size() - 1);

			//now SiftDown to "heapify"
			ShiftDown(0);
			return true;
		}
		return false;
	}

	void SiftUp(int nodeIndex)
	{
		//see what the parent index are, and then check to see if parent is less
		//if parent is less than do the shifting
		//do shifting until all cases are met
		int parentIndex;
		T temp;
		if (0 != nodeIndex)
		{
			parentIndex = GetParentIndex(nodeIndex);
			//if data at parent is < data at node index
			if (m_heap[parentIndex] < m_heap[nodeIndex])
			{
				//flip Nodes arround				
				temp = m_heap[parentIndex];
				m_heap[parentIndex] = m_heap[nodeIndex];
				m_heap[nodeIndex] = temp;

				//contine sifting
				SiftUp(parentIndex);
			}
			
		}
		//value is =, do nothing
	}

	int GetParentIndex(int nodeIndex)
	{
		//parent index = n-1 / k

		return (nodeIndex - 1) / m_k;

	}
	
	void ShiftDown(int indexNode)
	{
		//FIND the child max
		//once find the child max value
		//return the index of the child
		int  count =0;
		T  temp;

		//first child is located at nk+1
		int childIndex = (indexNode*m_k) + 1;

		//if(nk+1 > m_heap.size()) then indexNode is a leaf node and has no children
		//since it is a leaf node it is in the correct spot
		if (childIndex < m_heap.size())
		{
			//index is not a leaf

			T max_child = m_heap[childIndex];
			int length = m_heap.size();
			int index = childIndex;

			for (int i = index + 1; i < index + m_k && i < length; i++)
			{
				if (m_heap[i] > max_child)
				{
					max_child = m_heap[i];
					childIndex = i;
				}
			}
			//now do recursion until all cases are met
			if (m_heap[indexNode] < m_heap[childIndex])
			{
				temp = m_heap[indexNode];

				m_heap[indexNode] = m_heap[childIndex];
				m_heap[childIndex] = temp;
				
				//go again
				ShiftDown(childIndex);
			}
		}

		return;
	}

	vector<int> GetChildrensIndex(int indexNode)
	{
		if (indexNode != 0)
		{

			int size = m_k;
			vector< int > arr;
			for (int i = 0; i < m_k; i++)
			{
				arr.push_back((indexNode * size) + 1);
			}

			return arr;
		}
		else
		{
			vector< int > arr;
			for (int i = 0; i < m_k; i++)
			{
				arr.push_back(i + 1);
			}
			return arr;
		}

	
	}
};
#endif