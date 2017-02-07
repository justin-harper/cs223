#pragma once


//Justin Harper
//WSU ID: 10696738
//HW5

// Implement this class in this header file

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// Notes about template object:
// Whatever object is used as the template type for this class must implement the following:
// - Copy constructor
// - int GetKey() function
// - string ToString() function

template <typename T>
class hw6_234tree
{
private:
	struct Node
	{
		// A, B and C are the actual data values in the node		
		T* A;
		T* B;
		T* C;

		// Child pointers
		Node *L, *M1, *M2, *R;

		// Constructor to initialize the node with one value. The other two value 
		// pointers will be set to null and all child pointers will be set to null. 
		// The pointer given as the parameter is directly copied to A.
		Node(T* valueForA)
		{
			A = valueForA;
			B = C = NULL;
			L = M1 = M2 = R = NULL;
		}

		// Constructor to initialize the node with one value and two child pointers.
		Node(T* valueForA, Node* leftChildOfA, Node* rightChildOfA)
		{
			A = valueForA;
			L = leftChildOfA;
			M1 = rightChildOfA;
			
			// Everything else is NULL
			B = C = NULL;
			M2 = R = NULL;
		}

		Node(const Node& copyme)
		{
			A = copyme.A;
			B = copyme.B;
			C = copyme.C;

			L = M1 = M2 = R = nullptr;

		}

		Node(T* aVal, T* bVal, T* cVal, Node* left, Node* m1, Node* m2, Node* right)
		{
			A = aVal;
			B = bVal;
			C = cVal;
			L = left;
			M1 = m1;
			M2 = m2;
			R = right;
		}

		bool ContainsKey(int key)
		{
			if (C && C->GetKey() == key) { return true; }
			if (B && B->GetKey() == key) { return true; }
			if (A->GetKey() == key) { return true; }
			return false;
		}

		void DeleteData()
		{
			if (A) { delete A; A = NULL; }
			if (B) { delete B; B = NULL; }
			if (C) { delete C; C = NULL; }
		}

		// Returns true if all three data-value pointers, A, B, and C, are non-null, 
		// false otherwise.
		bool IsFull()
		{
			return (A != NULL && B != NULL && C != NULL);
		}

		// Returns true if all 4 child pointers are null, implying that the node is a leaf
		bool IsLeaf()
		{
			return (NULL == L && NULL == M1 && NULL == M2 && NULL == R);
		}

		int ValueCount()
		{
			if (C) { return 3; }
			else if (B) { return 2; }
			else if (A) { return 1; }

			// Should never come here
			return 0;
		}


	
	
	}; //end of Node struct

	Node* m_root;
	

	void DeleteTree(Node* root)
	{
		if (root)
		{
			root->DeleteData();
			DeleteTree(root->L);
			DeleteTree(root->M1);
			DeleteTree(root->M2);
			DeleteTree(root->R);
			delete root;
		}
	}

	void Display(Node* n)
	{
		if (!n) { return; }
		
		// There will always be an A value with a subtree to left and right of it
		Display(n->L);
		string nodeAsString = n->A->ToString();
		cout << nodeAsString << endl;
		Display(n->M1);

		// There may or may not be a B and C value
		if (n->B)
		{
			nodeAsString = n->B->ToString();
			cout << nodeAsString << endl;
			Display(n->M2);

			if (n->C)
			{
				nodeAsString = n->C->ToString();
				cout << nodeAsString << endl;
				Display(n->R);
			}
		}
	}

	// Finds and returns the node containing the minimum value in the subtree.
	Node* FindMin(Node* root)
	{
		if (root->IsLeaf())
		{
			return root;
		}

		Node* n = root->L;
		while (n->L) { n = n->L; }
		return n;
	}

	#if defined(DEBUG) || defined(_DEBUG)
	bool IsTreeValid(Node* n)
	{
		if (!n) { return true; }

		// First make sure that A is non-null. This should always be true for any 
		// node in the tree.
		if (!n->A)
		{
			cout << "DEBUG: Tree error: Value A in node is null!" << endl;
			return false;
		}

		// Now make sure A < B < C within the node. If C is null then we just 
		// need to verify that A < B and if B and C are NULL then it's ok.
		if (n->C)
		{
			// B must not be NULL in this case
			if (NULL == n->B)
			{
				cout << "DEBUG: Tree error: Value C in node is non-null but B is null!" << endl;
				return false;
			}

			if (n->C->GetKey() <= n->B->GetKey())
			{
				cout << "DEBUG: Tree error: Value C in node is <= B!" << endl;
				return false;
			}
		}
		else if (n->B)
		{
			if (n->B->GetKey() <= n->A->GetKey())
			{
				cout << "DEBUG: Tree error: Value B in node is <= A!" << endl;
				return false;
			}
		}

		// Next we make sure we have non-null child pointers where appropriate.
		if (!n->IsLeaf())
		{
			if (n->C)
			{
				if (NULL == n->R)
				{
					cout << "DEBUG: Tree error: R pointer in node is NULL but value C is not!" << endl;
					return false;
				}
			}
			if (n->B)
			{
				if (NULL == n->M2)
				{
					cout << "DEBUG: Tree error: M2 pointer in node is NULL but value B is not!" << endl;
					return false;
				}
			}
			if (NULL == n->M1)
			{
				cout << "DEBUG: Tree error: M1 pointer in node (key=";
				cout << n->A->GetKey() << ") is NULL!" << endl;
				return false;
			}
			if (NULL == n->L)
			{
				cout << "DEBUG: Tree error: L pointer in node is NULL!" << endl;
				return false;
			}
		}

		// For each value in the node, the left subtree should be all less and the right 
		// subtree all greater.
		T* vals[] = {n->A, n->B, n->C};
		Node* children[] = {n->L, n->M1, n->M1, n->M2, n->M2, n->R};
		for (int i = 0; i < 3; i++)
		{
			if (NULL == vals[i]) { break; }
			int key = vals[i]->GetKey();

			// Make sure all keys in left subtree are less
			stack<Node*> nodes;
			nodes.push(children[i/2]);
			while (!nodes.empty())
			{
				Node* temp = nodes.top();
				nodes.pop();
				if (!temp) { continue; }

				if (temp->A->GetKey() >= key)
				{
					cout << "DEBUG ERROR: Node in left subtree of key=" << key;
					cout << " has a key of " << temp->A->GetKey() << ", which is";
					cout << "greater and thus improperly structured." << endl;
					return false;
				}
				if (temp->B && temp->B->GetKey() >= key)
				{
					cout << "DEBUG ERROR: Node in left subtree of key=" << key;
					cout << " has a key of " << temp->A->GetKey() << ", which is";
					cout << "greater and thus improperly structured." << endl;
					return false;
				}
				if (temp->C && temp->C->GetKey() >= key)
				{
					cout << "DEBUG ERROR: Node in left subtree of key=" << key;
					cout << " has a key of " << temp->A->GetKey() << ", which is";
					cout << "greater and thus improperly structured." << endl;
					return false;
				}

				// Push children
				nodes.push(temp->L);
				nodes.push(temp->M1);
				nodes.push(temp->M2);
				nodes.push(temp->R);
			}

			// TODO: Right subtree - implement it on your own if you need the 
			// extra error checking
		}

		// Recurse for all children
		return (IsTreeValid(n->L) && IsTreeValid(n->M1) && 
			IsTreeValid(n->M2) && IsTreeValid(n->R));
	}
#endif

public:
	hw6_234tree(void)
	{
		m_root = NULL;
	}

	

	virtual ~hw6_234tree(void)
	{
		DeleteTree(m_root);
		m_root = NULL;
	}

	bool Add(T& toCopyAndAdd)
	{
		// You must implement this function
		// Do not allow duplicates in the tree
		// Return false if value already exists in tree or allocation of needed memory fails
		// Return true if addition succeeds
		// Don't forget the rules for splitting nodes

		T* copy = new T(toCopyAndAdd);
		int val = toCopyAndAdd.GetKey();
		return AddHelp(copy, m_root, nullptr, val);
			
	}
	bool AddHelp(T* copy, Node* n, Node* parent, int keyToAdd)
	{
		//simple case:
		//root is null=> n == m_root == nullptr
		if (n == m_root && m_root == nullptr)
		{
			//tree is empty
			//only time we can make a new node
			m_root = new Node(copy);
			//if the add was succesfull A will != nullptr
			return m_root->A;
		}
		//can only add new values to existing nodes
		//must split nodes on the way down
		if (isNodeFull(n))
		{
			n = split(n, parent);
		}
		if (keyToAdd == n->A->GetKey())
		{
			//duplicates are not allowed
			return false;
		}
		//B might exist
		if (n->B)
		{
			if (keyToAdd == n->B->GetKey())
			{
				//duplicates are not allowed
				return false;
			}
		}



		//current node has room now check value and place in tree
		//case 1: keyToAdd < A
		if (keyToAdd < n->A->GetKey())
		{
			if (n->L != nullptr)
			{
				//key to add is less than n->A and a node exits below A
				return AddHelp(copy, n->L, n, keyToAdd);

			}
			else
			{
				//key to add is less than A but a node does not exist below A
				//due to split earlier we know n has room
				
				//2 cases
				//either B is empty
				//or C is empty

				if (nullptr == n->B)
				{
					n->B = n->A;
					n->M1 = n->L; //B was null so M1 is also null
					n->L = nullptr;
					n->A = copy; //copy is the new value to add
					return n->A;
				}
				else
				{
					//C must be nullptr because Node would have been spit if it wasn't
					
					//move B to C
					n->C = n->B;
					//and fix subtree
					n->R = n->M2;
					
					//move A to B
					n->B = n->A;
					//and fix subtree
					n->M2 = n->M1;
					n->M1 = n->L; //n->L should be null
					
					n->L = nullptr; //just in case it isn't but that would imply broken add function
					//finaly add new value to A 
					n->A = copy;
					return n->A;

				}



			}

		}
		//case 2: keyToAdd > A
		else if (keyToAdd > n->A->GetKey())
		{
			if (n->M1 != nullptr)
			{
				//subtree exits...go to M1 and go again
				return AddHelp(copy, n->M1, n, keyToAdd);
			}
			else
			{
				//key to add is greater than A but less than B but a node does not exist below beteen A & B
				//due to split earlier we know n has room

				//2 cases
				//either B is empty
				//or C is empty
				if (nullptr == n->B)
				{
					//B is empty and keyToAdd is greater than A
					n->B = copy;
					return n->B;
				}
				else
				{
					//B has a value
					//check if keyToAdd is less than B

					if (keyToAdd < n->B->GetKey())
					{
						//keyToAdd is less than B but greater than A
						n->C = n->B;

						//fix up subtree
						n->R = n->M2;
						n->M2 = nullptr;
						//we know M1 is null due to check earlier
						n->B = copy;
						return n->B;

					}

					else
					{
						//keyToAdd is greater than B which is greater than A
						n->C = copy;
						return n->C;

					}

				}

			}

		}
		

		//case 3: keyToAdd > B
		else if (keyToAdd > n->B->GetKey())
		{
			if (n->M2 != nullptr)
			{ //subtree exits go to M2 and continue
				return AddHelp(copy, n->M2, n, keyToAdd);
			}
			else
			{
				//subtree does not exist (M2)
				//and keyToAdd is greater than B

				n->C = copy;
				return n->C;

			}


		}
		

	}

	bool isNodeFull(Node* check)
	{
		if (check->C)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Node*  split(Node* n, Node* parent)
	{
		//one node becomes 3
		Node* oldn = n;
		n = new Node(oldn->B);
		oldn->B = nullptr;
		n->L = oldn;
		
		n->M1 = new Node(oldn->C);
		oldn->C = nullptr;

		n->M1->L = oldn->M2;
		oldn->M2 = nullptr;

		n->M1->M1 = oldn->R;
		oldn->R = nullptr;
		//now fix up parents pointer to new n

		//five cases...

		//case 1: parent is null..ie oldn is old root
		if (nullptr == parent)
		{
			m_root = n;
		}
		//case 2: parents L == oldn
		else if (parent->L == oldn)
		{	
			parent->L = n;
		}
		//case 3 parents M1 == oldn
		else if (parent->M1 == oldn)
		{
			parent->M1 = n;
		}
		//case 4 parents M2 == oldn
		else if (parent->M2 == oldn)
		{
			parent->M2 = n;
		}
		//case 5 parents R == oldn
		else if (parent->R == oldn)
		{
			parent->R = n;
		}
		else
		{
			//should never get here
			//if we are here then
			//tree is broken

			std::cout << "Tree is broken after split()" << endl;
			system("Pause");

		}

		return n;
	}



	void Display(ostream& outstream)
	{
		if (!m_root)
		{
			outstream << "(tree is empty)";
		}
		Display(m_root);
	}

	void DisplayLevelKeys(ostream& outstream)
	{
		if (!m_root)
		{
			outstream << "(tree is empty, no levels to display)";
			return;
		}

		struct NodeLevel
		{
			Node* node;
			int level;
			NodeLevel(Node* n, int l) { node = n; level = l; }
		};
		
		queue<NodeLevel> nodes;
		nodes.push(NodeLevel(m_root, 0));
		int maxLevel = 0;
		while (!nodes.empty())
		{
			NodeLevel nl = nodes.front();
			nodes.pop();
			Node* n = nl.node;
			if (nl.level > maxLevel)
			{
				outstream << endl;
				maxLevel = nl.level;
			}

			outstream << "< " << n->A->GetKey() << " ";
			if (n->B) { outstream << n->B->GetKey() << " "; }
			if (n->C) { outstream << n->C->GetKey() << " "; }
			outstream << ">";

			// Enqueue children
			if (n->L) { nodes.push(NodeLevel(n->L, nl.level + 1)); }
			if (n->M1) { nodes.push(NodeLevel(n->M1, nl.level + 1)); }
			if (n->M2) { nodes.push(NodeLevel(n->M2, nl.level + 1)); }
			if (n->R) { nodes.push(NodeLevel(n->R, nl.level + 1)); }
		}
		outstream << endl;
	}

	T* Find(int key)
	{
		// You must implement this function to return the value for the object 
		// with the associated key. Return NULL if no such object exists in 
		// the tree.

		if (nullptr == m_root)
		{
			//if the tree is empty then key doesn't exist
			return nullptr;
		}
		else
		{
			return FindHelp(key, m_root);
		}

	}

	T* FindHelp(int key, Node* n)
	{
		//case 1: check if value is less than A
		if (key < n->A->GetKey())
		{
			//if key is less than A then
			//check if left subtree exists
			if (n->L != nullptr)
			{
				return FindHelp(key, n->L);
			}
			else
			{
				//value is less than A but no subtree exits
				//so value doesn't exist in tree
				return nullptr;
			}

		}
		//case 2: check if the value == A
		if (key == n->A->GetKey())
		{
			//found it!
			return n->A;
		}
		
		//case 3: the value is greater than A ...check if B exists
		if (n->B != nullptr)
		{
			//B exists now check if key is less than B
			if (key < n->B->GetKey())
			{
				//key is less than B 
				//check if a subtree exists
				if (n->M1 != nullptr)
				{
					//subtree exists move to M1 and check again
					return FindHelp(key, n->M1);
				}
				else
				{
					//key is less than B but no subtree exits
					//key is not in the tree

					return nullptr;

				}

			}
			//key is not less than B...
			//check if B is the target
			else if (key == n->B->GetKey())
			{
				//found it! ;)
				return n->B;
			}
			//B is not the target
			//check if C exits

			//this can be done inside the
			//nested if because if B == nullptr
			//than C can't exist
			else if (n->C != nullptr)
			{
				//C exists
				//check if key is less than C

				if (key < n->C->GetKey())
				{
					//key is less than C
					//check if a subtree exists
					if (n->M2 != nullptr)
					{
						//subtree exists
						//go there and check again
						return FindHelp(key, n->M2);

					}
					else
					{
						//key is less than C
						//but no subtree exits
						return nullptr;
					}
				}
				//key is not less than C
				//check if C is the target
				else if (key == n->C->GetKey())
				{
					//found it ;)
					return n->C;
				}
				//key must be greater than C
				else
				{
					//check if R subtree exits
					if (n->R != nullptr)
					{
						//R exists
						//go to R and check again

						return FindHelp(key, n->R);
					}
				}

			}

		}
		//B doesn't exist
		//check if M1 exists
		else if (n->M1 != nullptr)
		{
			//M1 exists...
			//go to M1 and check again

			return FindHelp(key, n->M1);
		}
		//key does not exist sorry

		return nullptr;

	}
		
	T* GetMin()
	{
		if (!m_root) { return NULL; }
		Node* n = FindMin(m_root);
		return n->A;
	}

#if defined(DEBUG) || defined(_DEBUG)
	bool IsTreeValid()
	{
		return IsTreeValid(m_root);
	}
#endif

	bool Remove(int key)
	{
		if (!m_root) { return false; }

		// Implement the rest of this function for HW6.
		// Don't worry about it and leave it as is for HW5.
		// Return false if the value is not present in the tree
		// Don't forget the rules for fusing nodes

		return RemoveHelp(key, m_root, nullptr);


	}

	bool RemoveHelp(int key, Node* current, Node* parrent)
	{




	//if a node with only one value is encounterd
	//fuse before moving on

		if (!NodeHas2OrMoreChildren(current))
		{
			//current only has one value and needs to be fused
			Fuse(current, parrent);

		}

		


	//Main two cases:

	//case 1: value to delete is in a leaf

		if (current->L == nullptr)
		{
			//all leaf nodes are on the same level...
			//if left subtree is empty then all subtrees are empty
			//therefore we are in a leaf node;
	
			if (current->B != nullptr)
			{

				//subcase 1: node has 2 or 3 entries
				//trivial case
				//just remove value and possible shift values to maintain filled left to right
				if (current->A->GetKey() == key)
				{
					//replace A with B and B with C
					//then done
					T* temp = current->A;
					current->A = current->B;
					current->B = current->C;
					current->C = nullptr;

					//delete dynamicly created objects
					delete temp;

					return true;

				}
				else if (current->B->GetKey() == key)
				{
					T* temp = current->B;
					current->B = current->C;
					current->C = nullptr;

					delete temp;

					return true;
				}
				else if (current->C != nullptr && current->C->GetKey() == key)
				{
					delete current->C;
					current->C = nullptr;

					return true;
				}
			
			}



		}
		else
		{

			//case 2: value to delete is not in a leaf
			//need to rotate until value is in a leaf
			//then procced

			//3 possiblites
			

			if (current->A->GetKey() == key)
			{
				//A is the value to rotate
				//current node has been fused if it needed to be earlier
				//A is greater than everything to the left and less then everything to the right

				Node* tempChild = current->L;
				if (tempChild->C == nullptr)
				{
					//current's left child has at least one free spot
					//rotate current-A to the left
					tempChild->C = current->A;
					current->A = nullptr;

					//now move to current->L and continue

					return RemoveHelp(key, current->L, current);

				}
				else
				{
					tempChild = current->M1;
					if (tempChild->C == nullptr)
					{
						//current's M1 child has at least one free spot
						//need to move M1's values to make room for A
						//as A is less than everything in M1
						tempChild->C = tempChild->B;
						tempChild->B = tempChild->A;
						tempChild->A = current->A;



						//need to replace current-A with max value of current->L subtree

						Node* temp = current->L;
						Node* tempPar = current;
						while (temp != nullptr)
						{
							tempPar = temp;
							temp = temp->R;
						}
						//max value will be at tempPar -> C
						//or if C is nullptr then B
						//or if B is nullptr then A
						//if it is A then a fuse needs to occure


					}
					else
					{
						//current's 2 left children are full and a split needs to occur
						split(current->L, current);
						tempChild = current->L;

						tempChild->C = current->A;
						current->A = nullptr;

						//move to L and continue

						return RemoveHelp(key, current->L, current);

						

					}
				}



			}
			else if (current->B->GetKey() == key)
			{
				//B is the value to rotate
				//B is greater than everything in M1 and less than everything in M2

				Node* tempChild = nullptr;

				if (NodeHasAtLeastOneFreeValue(current->M1))
				{
					tempChild = current->M1;
					
				}
				else if (NodeHasAtLeastOneFreeValue(current->M2))
				{
					tempChild = current->M2;
				}
				else
				{
					//both children are full and a split needs to occure
					split(current->M1, current);
					tempChild = current->M1;

				}



			}
			else if (current->C->GetKey() == key)
			{
				//C is the value to rotate
			}





		}







	//if value wasn't found return false
	return false;
	}


	bool NodeHas2OrMoreChildren(Node* node)
	{
		if (node->B != nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	bool NodeHasAtLeastOneFreeValue(Node* n)
	{
		if (n->C == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}




	void Fuse(Node* current, Node* parrent)
	{
		//cases: 1: left sibling and right sibling have 2 or more values each that can be "borrowed"
			//	 2: siblings do not have values that can be "borrowed"





		//subcase 2: node has only 1 value
		//need to fuse
		//subcase 2a: can "borrow": from left and right
		//subcase 2b: can't "borrow" from left and right
		//need to merge with parrent




	}


};

