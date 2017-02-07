#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "PQ_Heap.h"
#include "PQ_LinkedList.h"

using namespace std;


int main(void)
{
	PQ_LinkedList<int> ll;

	for (int i = 0; i < 50; i++)
	{
		ll.Add(i);
		//cout << ll.GetMax() << " -> ";
	}

	cout << endl << endl;
	while (!ll.IsEmpty())
	{
		int out;

		ll.RemoveMax(out);

		cout << out << " -> ";
	}

	cout << endl;








	return 1;
}