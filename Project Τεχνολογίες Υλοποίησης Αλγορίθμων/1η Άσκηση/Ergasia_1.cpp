#include <iostream>
#include <time.h>
#include <LEDA/graph/ugraph.h>
#include <LEDA/graph/graph_misc.h>
#include <LEDA/core/dynamic_trees.h>
#include <LEDA/system/basic.h>
#include <LEDA/graph/graph_alg.h>

using namespace std;
using namespace leda;

// Class that implements a single tree cohasive component
class TreeCohesiveComponent
{
	#pragma region Properties

	public:

		// List that contain the nodes
		list<node> NodeList;

	private:

		// Node list size
		int Size;

		// Pointer to the first node in the node list
		node FirstNodePointer;

		// Pointer to the last node in the node list
		node LastNodePointer;

	#pragma endregion Properties

	#pragma region Public Methods

	public:

		// Default constructor
		TreeCohesiveComponent()
		{
			// Set the properties for an empty instance
			Size = 0;

			FirstNodePointer = NULL;

			LastNodePointer = NULL;
		}

		// Parameter constructor for a single node
		TreeCohesiveComponent(node Node)
		{
			// Set the properties for an instance containing a single node
			Size = 1;

			FirstNodePointer = Node;

			LastNodePointer = Node;

			NodeList.append(Node);
		}

		// List size getter
		int GetSize()
		{
			return Size;
		}

		// First node getter
		node GetFirstNode()
		{
			return FirstNodePointer;
		}

		// Last node getter
		node GetLastNode()
		{
			return LastNodePointer;
		}

		// List size setter
		void SetSize(int ListSize)
		{
			Size = ListSize;
		}

		// First node pointer setter
		void SetFirstNodePointer(node NodePointer)
		{
			FirstNodePointer = NodePointer;
		}

		// Last node pointer setter
		void SetLastNodePointer(node NodePointer)
		{
			LastNodePointer = NodePointer;
		}

		/**
		 * Define the equality comparison operator for the TreeCohesiveComponent class
		 * @param LeftOperand The left operand of the operator
		 * @param RightOperand The right operand of the operator
		 * @return Whether the @param LeftOperand and @param RightOperand were the same
		 */
		friend bool operator == (TreeCohesiveComponent const &LeftOperand, TreeCohesiveComponent const &RightOperand) 
		{
			// Compare the size, the LeftOperand node pointer and the last node pointer
         	return (LeftOperand.FirstNodePointer == RightOperand.FirstNodePointer) && (LeftOperand.LastNodePointer == RightOperand.LastNodePointer) && (LeftOperand.Size == RightOperand.Size); 
    	}
		
	#pragma endregion Public Methods
};

/**
 * Ascending sort, based on the edge cost, for a list of edges
 * @param a The first edge
 * @param b The second edge
 * @return An integer, that the sorting of the edges will be based on
*/
int EdgeCostCompare(const edge &a, const edge &b)
{
	// Create an empty undirected graph in order to call the inf function
	UGRAPH<int, int> testGraph;

	// Ascending cost sorting...
	if(testGraph.inf(a) < testGraph.inf(b))
	{
		// Set a before b
		return -1;
	}	
	else
	{
		// Set b before a
		return 0;
	}
}

/**
 * Search for the tree cohesive component that contains the @param Node, in the @param ComponentList
 * @param ComponentList The tree cohesive component list
 * @param Node The node that will be searched
 * @return The tree cohesive component that contains the @param Node
 */
TreeCohesiveComponent SearchNode(list<TreeCohesiveComponent> &ComponentList, node Node)
{
	// Tree cohesive component that will be used for the iteration
	TreeCohesiveComponent tempTreeCohesiveComponent;

	// Node that will be used for the iteration
	node tempNode;

	// For all the tree cohesive components in the list...
	forall(tempTreeCohesiveComponent, ComponentList)
	{
		// For all the nodes in the tree cohesive component's node list...
		forall(tempNode, tempTreeCohesiveComponent.NodeList)
		{
			// If the node is found...
			if(tempNode == Node)
			{
				// Return the tree cohesive component
				return tempTreeCohesiveComponent;
			}
		}
	}

	return tempTreeCohesiveComponent;
}

/**
 * Merges the @param FirstTreeCohesiveComponent and @param SecondTreeCohesiveComponent
 * @param FirstTreeCohesiveComponent The first tree cohesive component
 * @param SecondTreeCohesiveComponent The second tree cohesive component
 * @return The merged tree cohesive component
 */
TreeCohesiveComponent MergeTreeCohesiveComponents(TreeCohesiveComponent FirstTreeCohesiveComponent, TreeCohesiveComponent SecondTreeCohesiveComponent)
{
	// Node that will be used for the iteration
	node tempNode;

	// Find the bigger node list bewtween the two tree cohesive components
	if(FirstTreeCohesiveComponent.GetSize() >= SecondTreeCohesiveComponent.GetSize())
	{
		// For every node in the smaller tree cohesive component node list...
		forall(tempNode, SecondTreeCohesiveComponent.NodeList)
		{
			// Add the nodes to the new list
			FirstTreeCohesiveComponent.NodeList.append(tempNode);
		}

		// Set the new node list size
		FirstTreeCohesiveComponent.SetSize(FirstTreeCohesiveComponent.NodeList.size());

		// Set the new last node pointer
		FirstTreeCohesiveComponent.SetLastNodePointer(FirstTreeCohesiveComponent.NodeList.tail());

		// Return the merged tree cohesive component
		return FirstTreeCohesiveComponent;
	}
	else
	{
		// For every node in the smaller tree cohesive component node list...
		forall(tempNode, FirstTreeCohesiveComponent.NodeList)
		{
			// Add the nodes to the new list
			SecondTreeCohesiveComponent.NodeList.append(tempNode);
		}

		// Set the new node list size
		SecondTreeCohesiveComponent.SetSize(SecondTreeCohesiveComponent.NodeList.size());

		// Set the new last node pointer
		SecondTreeCohesiveComponent.SetLastNodePointer(SecondTreeCohesiveComponent.NodeList.tail());

		// Return the merged tree cohesive component
		return SecondTreeCohesiveComponent;
	}
}

/**
 * Adds the new edge in the @param TreeCohesiveComponentList if the edge doesn't create a circle
 * @param TreeCohesiveComponentList The list containing the tree cohesive components
 * @param EdgeSourceNode The edge's source node
 * @param EdgeTargetNode The edge's target node
 * @return True if a circle was about to be created in the graph or false if not
*/
bool TreeCohesiveComponentAddEdge(list<TreeCohesiveComponent>& TreeCohesiveComponentList, node EdgeSourceNode, node EdgeTargetNode)
{
	// Get the tree cohesive component that contains the edge's sourse node
	TreeCohesiveComponent sourceNodeTreeCohesiveComponent = SearchNode(TreeCohesiveComponentList, EdgeSourceNode);

	// Get the tree cohesive component that contains the edge's target node
	TreeCohesiveComponent targetNodeTreeCohesiveComponent = SearchNode(TreeCohesiveComponentList, EdgeTargetNode);

	// If the first pointers are the same for both the target and source node...
	if(sourceNodeTreeCohesiveComponent.GetFirstNode() == targetNodeTreeCohesiveComponent.GetFirstNode())
	{
		// Return true because a circle was about to be created
		return true;
	}
	else
	{
		// Merge the tree cohesive components that contain the edge source and target nodes
		TreeCohesiveComponentList.append(MergeTreeCohesiveComponents(sourceNodeTreeCohesiveComponent, targetNodeTreeCohesiveComponent));

		// Remove the old tree cohesive component that contained the edge's source node
		TreeCohesiveComponentList.remove(sourceNodeTreeCohesiveComponent);

		// Remove the old tree cohesive component that contained the edge's target node
		TreeCohesiveComponentList.remove(targetNodeTreeCohesiveComponent);
	}
	
	// Return false because a circle wasn't created
	return false;
}

/**
 * Applies the Kruscal algorithm to the inserted @param UndirectedGraph
 * @param UndirectedGraph The inserted undirected graph
 * @return A graph containing the minimum spanning tree of @param UndirectedGraph
 */
UGRAPH<int, int> Kruscal(UGRAPH<int, int>& UndirectedGraph, list<edge>& CircleEdgeList)
{
	// Create an empty undirected graph for the minimum spanning tree
	UGRAPH<int, int> minimumSpanningTree(UndirectedGraph);

	// Edge array that contains the inserted undirected graph edges
	list<edge> edgeList = minimumSpanningTree.all_edges();

	// Delete all the edges from the minimum spanning tree
	minimumSpanningTree.del_all_edges();

	// Ascending sort the edge list based on the edge cost
	edgeList.sort(EdgeCostCompare);

	// Create a node list for the minimum spanning tree inserted nodes
	list<TreeCohesiveComponent> TreeCohesiveComponentList;

	// Node that will be used for the iteration
	node tempNode;

	// For every node in the minimum spanning tree...
	forall_nodes(tempNode, minimumSpanningTree)
	{
		// Create a tree cohesive component for the node
		TreeCohesiveComponent treeNode(tempNode);

		// Add the tree cohesive component in the list
		TreeCohesiveComponentList.append(treeNode);
	}

	// Edge that will be used for the iteration
	edge tempEdge;

	// List that will contain the edges that will be put in the minimum spanning tree
	list<edge> minimumSpanningTreeEdgesList;

	// For all edges in the edge list...
	forall(tempEdge, edgeList)
	{
		// Get the edge's source node 
		node tempEdgeSourceNode = UndirectedGraph.source(tempEdge);

		// Get the edge's target node 
		node tempEdgeTargetNode = UndirectedGraph.target(tempEdge);

		// Get the edge's cost 
		int tempEdgeCost = UndirectedGraph.inf(tempEdge);

		// Try to add the edge to the tree cohesive component list and get the result
		bool graphCircleFound = TreeCohesiveComponentAddEdge(TreeCohesiveComponentList, tempEdgeSourceNode, tempEdgeTargetNode);

		// Check if a graph circle was about to be created...
		if(!graphCircleFound)
		{
			// Add the edge into the list
			minimumSpanningTreeEdgesList.append(tempEdge);
		}
		else
		{
			// Add the edge that creates a circle into the list
			CircleEdgeList.append(tempEdge);
		}
	}

	// For all edges in the list...
	forall(tempEdge,minimumSpanningTreeEdgesList)
	{
		// Add the edge into the minimum spanning tree
		minimumSpanningTree.new_edge(minimumSpanningTree.source(tempEdge), minimumSpanningTree.target(tempEdge), minimumSpanningTree.inf(tempEdge));
	}

	// Return the minimum spanning tree
	return minimumSpanningTree;
}

/**
 * Validates the minimum spanning tree for the inserted undirected graph
 * @param UndirectedGraph The inserted undirected graph
 * @param MinimumSpanningTree The minimum spanning tree that the Kruscal function returns
 * @param CircleEdgeList The list containing the non tree edges that create a circle
 * @return True if the validation was successful, false if not
*/
bool minimumSpanningTreeValidator(UGRAPH<int, int>& UndirectedGraph, UGRAPH<int, int>& MinimumSpanningTree, list<edge>& CircleEdgeList)
{
	// Get the minimum spanning tree edges
	list<edge> minimumSpanningTreeEdgeList = MinimumSpanningTree.all_edges();

	// Create an empty dynamic tree
	leda_dynamic_trees dynamicTree;

	// Edge that will be used for the iteration
	edge tempEdge;

	// Node that will be used for the iteration
	node tempNode;

	// Initialise a node map, to associate each node to a unique vertex
	node_map<vertex> nodeVertexMap(MinimumSpanningTree, NULL);

	// For all nodes in the minimum spanning tree...
	forall_nodes(tempNode, MinimumSpanningTree)
	{
		// Associate a unique vertex for each node
		nodeVertexMap[tempNode] = dynamicTree.make();
	}

	// For all edges in the minimum spanning tree...
	forall(tempEdge, minimumSpanningTreeEdgeList)
	{
		// Evert the edge source node vertex
		dynamicTree.evert(nodeVertexMap[MinimumSpanningTree.source(tempEdge)]);

		// Evert the edge target node vertex
		dynamicTree.evert(nodeVertexMap[MinimumSpanningTree.target(tempEdge)]);

		// Link the vertexes, that correspond to the nodes of the edges, using the edge cost as the link cost 
		dynamicTree.link(nodeVertexMap[MinimumSpanningTree.source(tempEdge)], nodeVertexMap[MinimumSpanningTree.target(tempEdge)], MinimumSpanningTree.inf(tempEdge));
	}
	
	// For every edge in the circle edge list...
	forall(tempEdge, CircleEdgeList)
	{
		// Get the vertex, that is associated to the edge source node
		vertex edgeSourceNodeVertex = nodeVertexMap[MinimumSpanningTree.source(tempEdge)];

		// Get the vertex, that is associated to the edge target node
		vertex edgeTargetNodeVertex = nodeVertexMap[MinimumSpanningTree.target(tempEdge)];

		// Get the least common ancestor vertex, of the edge source and target node vertexes
		vertex leastCommonAncestorVertex = dynamicTree.lca(edgeSourceNodeVertex,edgeTargetNodeVertex);
		
		// Search the path between the edge source node vertex and the least common ancestor vertex
		while(edgeSourceNodeVertex != leastCommonAncestorVertex)
		{
			// If the non tree edge's cost if greater or equal the current edge...
			if(MinimumSpanningTree.inf(tempEdge) >= dynamicTree.cost(edgeSourceNodeVertex))
			{
				// Get the next edge in the path
				edgeSourceNodeVertex = dynamicTree.parent(edgeSourceNodeVertex);
			}
			else
			{
				// Return false since the tree is invalid
				return false;
			}
		}

		// Search the path between the edge target node vertex and the least common ancestor vertex
		while(edgeTargetNodeVertex != leastCommonAncestorVertex)
		{
			// If the non tree edge's cost if greater or equal the current edge...
			if(MinimumSpanningTree.inf(tempEdge) >= dynamicTree.cost(edgeTargetNodeVertex))
			{
				// Get the next edge in the path
				edgeTargetNodeVertex = dynamicTree.parent(edgeTargetNodeVertex);
			}
			else
			{
				// Return false since the tree is invalid
				return false;
			}
		}
	}
	
	// Return true since the validation was successful
	return true;
}

// Main function
int main()
{
	#pragma region Initialization

	// Create an empty undirected graph
	UGRAPH<int, int> undirectedGraph;

	// Initialise a list that will contain the edges that create a circle in the graph
	list<edge> circleEdgeList;

	// User graph option
	std::string graphOption;

	// Number of nodes
	int numberOfNodes;

	cout << "Choose the testing graph between grid, synthetic or random." << endl; 

	// Read the graph type
	cin >> graphOption;

	cout << "Enter the number of nodes." << endl;

	// Read the number of nodes
	cin >> numberOfNodes;

	// Edge will be used for the iteration
	edge tempEdge;

	// If the grid graph is selected...
	if(graphOption == "grid")
	{
		// Create a grid  
		grid_graph(undirectedGraph, numberOfNodes);
		
		// Initialize a random seed
		srand(time(NULL));

		// For every edge in the undirected graph...
		forall_edges(tempEdge, undirectedGraph)
		{
			// Assign random integer values as costs between 10 and 10000
			undirectedGraph.assign(tempEdge, (rand() % 990) + 10);
		}
	}
	else
	{
		// If the synthetic graph is selected...
		if(graphOption == "synthetic")
		{
			// Create the complete undirected graph 
			complete_ugraph(undirectedGraph, numberOfNodes);

			// For every edge in the undirected graph...
			forall_edges(tempEdge, undirectedGraph)
			{
				// Assign the index of the edge target node as a cost
				undirectedGraph.assign(tempEdge, undirectedGraph.index(undirectedGraph.target(tempEdge)) - 1);
			}
		}
		else
		{
			// If the random graph is selected...
			if(graphOption == "random")
			{
				// Create an empty ugraph
				ugraph initialisedUgraph;

				// Calculate the number of edges
				int numberOfEdges = ceil(2 * numberOfNodes * log2(numberOfNodes));

				// Create a random undirected graph 
				random_simple_undirected_graph(initialisedUgraph, numberOfNodes, numberOfEdges);
				
				// Make the graph cohesive
				Make_Biconnected(initialisedUgraph);

				// Copy the ugraph to the UGRAPH<int, int>
				CopyGraph(undirectedGraph, initialisedUgraph);

				// Initialize a random seed
				srand(time(NULL));

				// For every edge in the undirected graph...
				forall_edges(tempEdge, undirectedGraph)
				{
					// Assign random integer values as costs between 10 and 10000
					undirectedGraph.assign(tempEdge, (rand() % 990) + 10);
				}
			}
			else
			{
				cout << "Choose between grid, synthetic or random." << endl;

				// Exit if another option is selected
				exit(0);
			}
		}
	}
	
	// Initialise an edge array that contains the edges's costs
	edge_array<int> edgeCostArray(undirectedGraph);

	#pragma endregion Initialization

	// Initialise the starting CPU time
	float CPUTime = used_time();

	// Get the minimum spanning tree for the undirected graph
	UGRAPH<int, int> minimumSpanningTree = Kruscal(undirectedGraph, circleEdgeList);

	// Print the user defined Kruscal execution time
	cout << "User defined Kruscal function execution time: " << used_time(CPUTime) << endl;

	// Get the minimum spanning tree
	list<edge> min_tree_edges = MIN_SPANNING_TREE(undirectedGraph,edgeCostArray);

	// Print the user defined Kruscal execution time
	cout << "Leda minimum spanning tree function execution time: " << used_time(CPUTime) << endl;
	
	// Validate the minimum spanning tree based on the undirected graph
	bool minimumSpanningTreeValidation = minimumSpanningTreeValidator(undirectedGraph, minimumSpanningTree, circleEdgeList);

	// If the minimum spanning tree was successfully validated...
	if(minimumSpanningTreeValidation)
	{
		cout << "The minimum spanning tree was successfully validated." << endl; 
	}
	else
	{
		cout << "The minimum spanning tree is invalid." << endl;
	}
	
	// Return 0
	return 0;
}
