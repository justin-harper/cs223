#include "ArraySorter.h"


ArraySorter::ArraySorter(void)
{
}

void ArraySorter::InsertionSort(int* arr, int n)
{
	InsertionSort(arr, n, 0, 1);
}

void ArraySorter::InsertionSort(int* arr, int n, int startIndex, int gap)
{
	// You must implement this function
	for (int i = gap; i < n; i++)
	{
		int tmp = arr[i];
		int j = 0;
		for (j = i - gap; j >= 0 && arr[j]> tmp; j -= gap)
		{
			arr[j + gap] = arr[j];
		}
		arr[j + gap] = tmp;
	}
}

// Checks to see if the array is in sorted order
bool ArraySorter::IsSorted(int* arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		// If an item is less than the one before it, then we're not sorted
		if (arr[i] < arr[i - 1])
		{
			return false;
		}
	}

	return true;
}

void ArraySorter::MergeSort(int* arr, int n)
{
	// You must implement this function

	MergeSortRec(0, n, arr);
}

void ArraySorter::MergeSortRec(int left, int right, int* arr)
{
	//handle base case
	if (right - left <= 1)
	{
		return;
	}
	int leftStart = left;
	int leftEnd = (left + right) / 2;
	int rightStart = leftEnd;
	int rightEnd = right;

	//sort left half
	MergeSortRec(leftStart, leftEnd, arr);

	//sort right half
	MergeSortRec(rightStart, rightEnd, arr);

	//merge halves

	Merge(arr, leftStart, leftEnd, rightStart, rightEnd);


}


void ArraySorter::Merge(int* arr, int leftStart, int leftEnd, int rightStart, int rightEnd)
{
	int leftLength = leftEnd - leftStart;
	int rightLength = rightEnd - rightStart;
	
	int *leftHalf = new int[leftLength];
	int *rightHalf = new int[rightLength];

	int rightHalfIndex = 0;
	int leftHalfIndex = 0;
	int mainIndex = 0;

	//copy left half of arr into leftHalf
	for (mainIndex = leftStart; mainIndex < leftEnd; mainIndex++, leftHalfIndex++)
	{
		leftHalf[leftHalfIndex] = arr[mainIndex];
	}

	//copy right half of arr into rightHalf
	for (mainIndex = rightStart; mainIndex < rightEnd; mainIndex++, rightHalfIndex++)
	{
		rightHalf[rightHalfIndex] = arr[mainIndex];
	}

	//merge left and right back into list
	for (mainIndex = leftStart, rightHalfIndex = 0, leftHalfIndex = 0; leftHalfIndex < leftLength && rightHalfIndex < rightLength; mainIndex++)
	{
		if (leftHalf[leftHalfIndex] < rightHalf[rightHalfIndex])
		{
			arr[mainIndex] = leftHalf[leftHalfIndex++];
		}
		else
		{
			arr[mainIndex] = rightHalf[rightHalfIndex++];
		}
	}
	//now get leftovers
	for (; leftHalfIndex < leftLength; mainIndex++, leftHalfIndex++)
	{
		arr[mainIndex] = leftHalf[leftHalfIndex];
	}
	for (; rightHalfIndex < rightLength; mainIndex++, rightHalfIndex++)
	{
		arr[mainIndex] = rightHalf[rightHalfIndex];
	}




}


void ArraySorter::QuickSort(int* arr, int n)
{
	// You must implement this function

	if (n < 2)
	{
		return;
	}

	int p = arr[n / 2];
	int *l = arr;
	int *r = arr + n - 1;

	while (l <= r)
	{
		if (*l < p)
		{
			l++;
			continue;
		}
		if (*r > p)
		{
			r--;
			continue;
		}

		int t = *l;
		*l++ = *r;
		*r-- = t;
	}

	QuickSort(arr, r - arr + 1);

	QuickSort(l, arr + n - l);



}

// This is implemented for you, but you need to implement the InsertionSort 
// function that it calls.
void ArraySorter::ShellSort(int* arr, int n, int* gapVals, int gapValsCount)
{
	// Do an insertion sort pass for each of the gap values
	int i;
	for (i = 0; i < gapValsCount; i++)
	{
		for (int j = 0; j < gapVals[i]; j++)
		{
			InsertionSort(arr, n, j, gapVals[i]);
		}
	}

	// We always need to finish with a pass using gap=1
	if (1 != gapVals[i - 1])
	{
		InsertionSort(arr, n);
	}
}
