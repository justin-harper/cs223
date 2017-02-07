// Cpt S 223 - Directed Graph Homework
// DirectedGraph.cpp
// (Justin Harper WSUID: 10696738)
#include "DirectedGraph.h"

DirectedGraph::DirectedGraph()
{
	// No initialization needed
}

DirectedGraph::~DirectedGraph()
{
	// Free all nodes and edges
	for (int i = 0; i < m_nodes.size(); i++)
	{
		delete m_nodes[i];
	}
	m_nodes.clear();
	for (int i = 0; i < m_edges.size(); i++)
	{
		delete m_edges[i];
	}
	m_edges.clear();

	// Make sure the node map is cleared too
	m_nodeMap.clear();
}

bool DirectedGraph::AddNode(const string& nodeName, const string& nodeData)
{
	// We don't add the node if one with the same name already exists
	if (NodeExists(nodeName)) { return false; }

	Node* n = new Node(nodeName, nodeData);
	if (!n) { return false; }
	m_nodes.push_back(n);
	m_nodeMap.insert(make_pair(nodeName, m_nodes.size() - 1));
	return true;
}

// Adds an edge to the graph that starts at the source node, 
// and goes to the target node.
// If the graph already contains an edge going from the specified 
// source to target node then false is returned and no modification 
// occurs.
// If either or both of the two nodes don't exist in the graph then 
// false is returned and no modification occurs.
// Otherwise the edge will be added. Note that an edge from N1 (source) 
// to N2 (target) is different than an edge from N2 (source) to N1 (target).
bool DirectedGraph::AddEdge(const string& sourceNodeName,
	const string& targetNodeName)
{
	// First make sure both nodes exist
	if (!NodeExists(sourceNodeName) || !NodeExists(targetNodeName))
	{
		return false;
	}

	// Allocate the edge and add it to the edge list
	int sourceIndex = m_nodeMap[sourceNodeName];
	int targetIndex = m_nodeMap[targetNodeName];
	Edge* e = new Edge(sourceIndex, targetIndex);
	if (!e) { return false; }
	m_edges.push_back(e);

	// Add it as an outgoing edge for the source node and an incoming edge 
	// for the target node.
	m_nodes[sourceIndex]->Out.push_back(e);
	m_nodes[targetIndex]->In.push_back(e);

	return true;
}

// Gets the degree of the node with the specified name. -1 is returned 
// if no such node exists in the graph.
int DirectedGraph::GetDegree(const string& nodeName) const
{
	if (0 == m_nodeMap.count(nodeName)) { return -1; }

	// Get the index of the node from the hash map
	unordered_map<string, int>::const_iterator it = m_nodeMap.find(nodeName);
	if (it == m_nodeMap.end()) { return -1; }
	int index = it->second;

	// Linear-time solution commented out below (because we have a faster one)
	/*
	// Count all edges that have this node
	int count = 0;
	for (int i = 0; i < m_edges.size(); i++)
	{
	if (m_edges[i]->srcI == index || m_edges[i]->targetI == index)
	{
	count++;
	}
	}
	return count;
	*/

	// Constant time solution
	return m_nodes[index]->In.size() + m_nodes[index]->Out.size();
}

int DirectedGraph::GetNodeIndex(const string& nodeName) const
{
	// Get the index of the node from the hash map
	unordered_map<string, int>::const_iterator it = m_nodeMap.find(nodeName);
	if (it == m_nodeMap.end()) { return -1; }
	return it->second;
}

// Gets the shortest path from the specified start to end nodes. If no path exists 
// from the start to end nodes then false is returned and the traversalList object 
// is not modified. Otherwise the traversalList is filled with strings representing 
// the sequence of nodes for the shortest path from start to end. These strings 
// will be the node names if nodeDataInsteadOfName is false, otherwise they will be 
// the node data values (which are strings).
bool DirectedGraph::GetShortestPath(const string& startNode, const string& endNode, bool nodeDataInsteadOfName, vector<string>& traversalList) const
{

	// You must implement this function




	//make "table" for VisitedNodes and Distance
	std::vector<bool> VisitedNodes;
	std::vector<double> Distance;


	//initilze the tables
	for (auto n : m_nodes)
	{
		VisitedNodes.push_back(false);
		Distance.push_back(INFINITY);

	}
	//get indices for start and end
	int startIndex = GetNodeIndex(startNode);
	int endIndex = GetNodeIndex(endNode);

	//set startNode distance to 0
	Distance[startIndex] = 0;


	//end of initilzation


	//begin shortest path main loop


	bool keepGoing = true;

	while (keepGoing)
	{
		//get index of node with the least cost/distance
		int CurrentNodeIndex = getIndexOfUnvistitedNodeWithLeastDistance(VisitedNodes, Distance);

		//if currentNodeIndex equals the end node stop
		//we have found the path
		if (CurrentNodeIndex == endIndex)
		{
			keepGoing = false;
			//need to update TraversalList with nodes in shortest path

			updatePath(VisitedNodes, Distance, startIndex, endIndex, traversalList, nodeDataInsteadOfName);

			return true;
		}
		else if (CurrentNodeIndex == -1)
		{
			//current node does not exist
			keepGoing = false;
			return false;
		}
		else if (Distance[CurrentNodeIndex] == INFINITY)
		{
			//Node cannot be traveld to
			//graph is discrete
			//no valid path exits
			keepGoing = false;
			return false;
		}
		else
		{
			//we have not found the end of the path and need to keep going


			//check all outgoing edges of currentNode
			//and compare cost with table
			//if the cost to go to the next node is less than what is in the table 
			//update the table
			Node* current = m_nodes[CurrentNodeIndex];

			for (int i = 0; i < current->Out.size(); i++)
			{
				double currentCost = Distance[CurrentNodeIndex];
				double costToI = currentCost + current->Out[i]->getCost();
				int indexOfI = current->Out[i]->targetI;


				if (costToI < Distance[indexOfI])
				{
					Distance[indexOfI] = costToI;
				}
				//else leave current value in the table and move on
			}

			//we have checked every outgoing edge and updated the
			//distance/cost table accordingly

			//now mark current node as "visited"

			VisitedNodes[CurrentNodeIndex] = true;


			//go to next node and go again

		}

	}



	return false;
}





//determines if an edge exists between src and dest
//src and dest are indexes in graph vector
bool DirectedGraph::hasEdge(int src, int dest) const
{
	for (int i = 0; i < m_edges.size(); i++)
	{
		if (m_edges[i]->srcI == src && m_edges[i]->targetI == dest)
		{
			return true;
		}
	}

	return false;
}





int DirectedGraph::minDistance(std::vector<int>& dist, std::vector<bool>& sptSet, int V) const
{
	int min = INT_MAX;
	int min_index;


	for (int i = 0; i < V; i++)
	{
		if (sptSet[i] == false && dist[i] < min)
		{
			min = dist[i], min_index = i;
		}
	}

	return min_index;

}


bool DirectedGraph::NodeExists(const string& nodeName) const
{
	return (m_nodeMap.count(nodeName) > 0);
}


int DirectedGraph::getIndexOfUnvistitedNodeWithLeastDistance(std::vector<bool>& VisitedTable, std::vector<double>& DistanceTable) const
{
	int indexToReturn = -1;
	double minDistance = INFINITY;

	for (int i = 0; i < VisitedTable.size(); i++)
	{
		if (VisitedTable[i] == false && DistanceTable[i] < minDistance)
		{
			indexToReturn = i;
			minDistance = DistanceTable[i];
		}
	}

	return indexToReturn;
}

//this function will trace back along the shortest path and update the traversalList vector
void DirectedGraph::updatePath(std::vector<bool>& VisitedNodes, std::vector<double>& Distance, int startIndex, int endIndex, vector<string>& traversalList, bool data) const
{
	//if data is false use Name field
	if (!data)
	{

		int index = endIndex;
		double currentCost = Distance[endIndex];

		//end node will be in the path
		//traversalList.push_back(m_nodes[index]->Name);

		if (Distance[endIndex] == INFINITY)
		{
			traversalList.push_back("nope2");
			return;
		}


		while (m_nodes[index] != m_nodes[startIndex])
		{

			for (int i = 0; i < m_nodes[index]->In.size(); i++)
			{
				if (currentCost - m_nodes[index]->In[i]->getCost() == Distance[m_nodes[index]->In[i]->srcI])
				{
					currentCost = currentCost - m_nodes[index]->In[i]->getCost();
					traversalList.push_back(m_nodes[index]->Name);
					index = m_nodes[index]->In[i]->srcI;
					i = 0;
					break;
				}
			}
		}



		//add start node to list
		traversalList.push_back(m_nodes[index]->Name);


	}
	//use data field
	else
	{
		int index = endIndex;
		double currentCost = Distance[endIndex];

		//end node will be in the path
		//traversalList.push_back(m_nodes[index]->Name);

		if (Distance[endIndex] == INFINITY)
		{
			traversalList.push_back("Nope");
			return;
		}


		while (m_nodes[index] != m_nodes[startIndex])
		{

			for (int i = 0; i < m_nodes[index]->In.size(); i++)
			{
				if (currentCost - m_nodes[index]->In[i]->getCost() == Distance[m_nodes[index]->In[i]->srcI])
				{
					currentCost = currentCost - m_nodes[index]->In[i]->getCost();
					traversalList.push_back(m_nodes[index]->Data);
					index = m_nodes[index]->In[i]->srcI;
					i = 0;
					break;
				}
			}
		}



		//add start node to list
		traversalList.push_back(m_nodes[index]->Data);



	}

	reverseList(traversalList);

	return;
}


void DirectedGraph::reverseList(std::vector<string> &list) const
{

	std::stack<string> temp;

	for (int i = 0; i < list.size(); i++)
	{
		temp.push(list[i]);
	}
	list.clear();
	while (!temp.empty())
	{
		list.push_back(temp.top());
		temp.pop();
	}


	return;
}



//takes a stack of indexs in the path and fills the traversalList with
//the names of the nodes along the path
void DirectedGraph::putPathIntoTraversialList(std::stack<int> &path, std::vector<string> &traversalList) const
{
	while (!path.empty())
	{
		int index = path.top();
		path.pop();

		traversalList.push_back(m_nodes[index]->Name);

	}

	return;

}

