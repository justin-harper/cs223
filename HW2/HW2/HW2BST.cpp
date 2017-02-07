#include "HW2BST.h"

using namespace std;

HW2BST::Node::Node(int dataValue)
{
	Data = dataValue;
	Left = Right = NULL;
}

HW2BST::HW2BST(void)
{
	m_root = NULL;
}

HW2BST::~HW2BST(void)
{
	DeleteTree(m_root);
	m_root = NULL;
}

// Should return false if the value already exists in the tree or if memory 
// for a new node could not be allocated.
bool HW2BST::Add(int dataValue)
{
	// You must implement this function
	
	bool success = false;


	if (m_root == nullptr)
	{
		if (m_root = new Node{ dataValue })
		{
			success = true;
		}
	}

	else
	{
		success = AddHelper(m_root, dataValue);
	}

	return success;

}

bool HW2BST::AddHelper(Node* root, int dataValue)
{
	Node* current = root;
	



	if (current->Data > dataValue)
	{
		if (current->Left != nullptr)
		{
			return AddHelper(current->Left, dataValue);
		}
		else
		{
			return (current->Left = new Node{ dataValue });
			
			
			
		}
	}
	else if (current->Data < dataValue)
	{
		if (current->Right != nullptr)
		{
			return AddHelper(current->Right, dataValue);
		}
		else
		{
			return (current->Right = new Node{ dataValue });
			

		}
	}
	

}

// Returns the number of levels in the tree. A tree with no contents (null root) will have 
// zero levels. A tree with just the root and no children has 1 level. For all other cases 
// the number of levels must be counted. There is a linear-time algorithm for this.
int HW2BST::CountLevels()
{
	//seems to be off by a bit
	int left = 0;
	int right = 0;
	int Level = 0;

	if (m_root == nullptr)
	{
		return Level;
	}

	std::queue<Node*> que;
	que.push(m_root);

	while (!que.empty())
	{
		Node* temp = que.front();
		que.pop();

		if (temp->Left)
		{
			que.push(temp->Left);
			left++;
		}
		if (temp->Right)
		{
			que.push(temp->Right);
			right++;
		}
	}
	return Max(left, right);


}

void HW2BST::DeleteTree(Node* root)
{
	if (root)
	{
		DeleteTree(root->Left);
		DeleteTree(root->Right);
		delete root;
	}
}

void HW2BST::DisplayContents(Node* node, ostream& outputStream)
{
	if (node)
	{
		DisplayContents(node->Left, outputStream);

		// Display the numerical value for this node
		outputStream << node->Data << " ";

		// Display the entire right subtree
		DisplayContents(node->Right, outputStream);
	}
}

void HW2BST::DisplayContents(ostream& outputStream)
{
	outputStream << "BST Contents: ";
	DisplayContents(m_root, outputStream);
	outputStream << endl;
}

//will go through the tree displaying the nodes at each level
void HW2BST::DisplayLevels(std::ostream& outputStream)
{
	// You must implement this function
	int Levels = CountLevels();
	outputStream << "Tree with " << Levels << " levels:" << endl;
	
	int h = Height(m_root);
	for (int i = 0; i < h; i++)
	{
		outputStream << "Level " << i + 1 << ": ";
		DisplayLevelsHelper(outputStream, m_root, i + 1);
		outputStream << endl;

	}

}
//recusrive function to display levels (usually called by DisplayLevels()
void HW2BST::DisplayLevelsHelper(std::ostream& os, HW2BST::Node* node, int indent)
{
	if (node == nullptr)
	{
		return;
	}
	if (indent == 1)
	{
		os << node->Data << " ";
	}

	DisplayLevelsHelper(os, node->Left, indent - 1);
	
	DisplayLevelsHelper(os, node->Right, indent - 1);
	

}

// Gets the maximum value in the tree. Returns 0 if the tree is empty.
int HW2BST::GetMax()
{
	if (m_root)
	{
		Node* n = m_root;
		while (n->Right)
		{
			n = n->Right;
		}
		return n->Data;
	}
	return 0;
}





bool HW2BST::IsEmpty()
{
	return (NULL == m_root);
}

// Returns true if the value was found and removed, false if it was not found
bool HW2BST::Remove(int dataValue)
{
	// You must implement this function

	if (!m_root)
	{//empty tree
		return false;
	}
	else
	{
		return RemoveHelper(m_root, dataValue);
	}
	
}

bool HW2BST::RemoveHelper(HW2BST::Node*& root, int dataValue)
{
	if (root == nullptr)
	{
		return false;
	}
	else if (root->Data == dataValue)
	{
		if (root->Right)
		{
			Node* leftSub = root->Left;
			Node* rightSub = root->Right;
			Node* x = root;
			root = rightSub;
			Node* temp = GetLeftMostChild(rightSub);
			temp->Left = leftSub;

			delete x;
			return true;
			


		}
	}
	else if (root->Data > dataValue)
	{
		return RemoveHelper(root->Left, dataValue);
	}
	else
	{
		return RemoveHelper(root->Right, dataValue);
	}
	

}


HW2BST::Node* HW2BST::GetLeftMostChild(HW2BST::Node* root)
{
	if (root)
	{
		if (root->Left)
		{
			return GetLeftMostChild(root->Left);
		}
		else
		{
			return root;
		}
	}
	else
	{
		return nullptr;
	}
}

int HW2BST::Height(HW2BST::Node* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	if (!root->Left && !root->Right)
	{
		return 1;
	}
	int lheight = Height(root->Left);
	int rheight = Height(root->Right);

	return Max(lheight, rheight) + 1;
}

int HW2BST::Max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}