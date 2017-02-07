#pragma once

// Cpt S 223 - Homework 2
// You can modify the class declaration by adding add additional helper functions, but 
// do not rename or remove anything that's already declared.

#include <iostream>
#include <queue>
#include <stack>


class HW2BST
{
private:
	struct Node
	{
		int Data;
		Node* Left;
		Node* Right;

		Node(int dataValue);
	};

	// Pointer to the root node of the binary search tree
	// If this is null it implies that the tree is empty
	Node* m_root;

	void DeleteTree(Node* n);

	void DisplayContents(Node* node, std::ostream& outputStream);

public:
	HW2BST(void);
	~HW2BST(void);

	// Should return false if the value already exists in the tree or if memory 
	// for a new node could not be allocated.
	bool Add(int dataValue);
	bool AddHelper(Node* root, int dataValue);
	Node* makeNewNode(int data);
	

	int CountLevels();

	void DisplayContents(std::ostream& outputStream);

	void DisplayLevels(std::ostream& outputStream);
	void HW2BST::DisplayLevelsHelper(std::ostream& os, HW2BST::Node* node, int indent);

	// Gets the maximum value in the tree. Returns 0 if the tree is empty.
	int GetMax();

	bool IsEmpty();

	// Returns true if the value was found and removed, false if it was not found
	bool Remove(int dataValue);

	int HW2BST::Height(HW2BST::Node*);

	int Max(int a, int b);

	

	bool HW2BST::RemoveHelper(HW2BST::Node*&, int dataValue);

	HW2BST::Node* GetLeftMostChild(HW2BST::Node* root);
};

