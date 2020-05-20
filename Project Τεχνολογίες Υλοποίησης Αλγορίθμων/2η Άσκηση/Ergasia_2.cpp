#include <iostream>
#include <time.h>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <LEDA/graph/graph.h>

//export LEDAROOT=/home/jim/Project/Leda/LEDA-6.3-free-fedora-core-8-64-g++-4.1.2; export LD_LIBRARY_PATH=$LEDAROOT
//g++ Ergasia_2.cpp -o testcode -I$LEDAROOT/incl -L$LEDAROOT -lleda -lX11 -lm

using namespace std;
using namespace boost;
using namespace leda;

// Define the boost edge weight property
typedef property<edge_weight_t, int> EdgeWeightProperty;

// Define the boost directed graph: std::vector, std::vector, directed, no vertex property, int edge property, no graph property, std::list
typedef adjacency_list<vecS, vecS, directedS, no_property, EdgeWeightProperty, no_property, listS> DirectedGraph;

// Define the vertex class as vertex_desciptor
typedef graph_traits<DirectedGraph>::vertex_descriptor Vertex;

// Define the edge class as edge_desciptor
typedef graph_traits<DirectedGraph>::edge_descriptor Edge;

// Define the edge iterator as edge_iterator
typedef graph_traits<DirectedGraph>::edge_iterator EdgeIterator;

// Define the edge iterator as edge_iterator
typedef graph_traits<DirectedGraph>::vertex_iterator VertexIterator;

// Define the edge iterator as edge_iterator
typedef graph_traits<DirectedGraph>::out_edge_iterator OutEdgeIterator;

// Define the edge weight map as a property map
typedef property_map<DirectedGraph, edge_weight_t>::type EdgeWeightMap;

/**
 * Copies @param LedaGraph to @param BoostDirectedGraph, using the @param LedaEdgeWeightMap
 * @param BoostDirectedGraph The boost directed graph
 * @param LedaGraph The leda directed graph
 * @param LedaEdgeWeightMap The edge array that contain the leda directed graph edges weights
*/
void CopyLedaGraphToBoostGraph(DirectedGraph& BoostDirectedGraph, leda::graph& LedaGraph, edge_array<int>& LedaEdgeWeightMap)
{
	// Create a new boost directed graph containing the smae number of nodes as the leda directed graph
	DirectedGraph boostGraph(LedaGraph.number_of_nodes());

	// Leda edge that will be used for iteration
	leda::edge tempEdge;

	// For all edges in the leda directed graph
	forall_edges(tempEdge, LedaGraph)
	{
		// Get the source node of the edge
		node source = LedaGraph.source(tempEdge);

		// Get the target node of the edge
		node target = LedaGraph.target(tempEdge);

		// Get the weight of the edge
		int edgeWeight = LedaEdgeWeightMap[tempEdge];

		// Add the edge in the boost directed graph
		add_edge(LedaGraph.index(source), LedaGraph.index(target), edgeWeight, boostGraph);
	}

	// Update the boost directed graph
	BoostDirectedGraph = boostGraph;
}

/**
 * Applies the Bellman Ford algorithm to the @param directedGraph, using @param startingnode
 * @param directedGraph The inserted boost directed graph
 * @param startingNode The node that will be used as the minimum path's starting node
 * @return False if the graph contains a negative weight circle or true otherwise
 */
bool BellmanFord(DirectedGraph& directedGraph, Vertex startingVertex)
{
	// Initialize a node map containg the node minimum path cost
	std::map<Vertex, int> nodeCostMap;

	// Initialize the property map that contain the edges's weights
	EdgeWeightMap edgeWeightMap = get(edge_weight, directedGraph);

	// Initialise the boost vertex iterators
	VertexIterator vertexIteratorBegin, vertexIteratorEnd;

	// For every vertex in the boost directed graph...
	for(tie(vertexIteratorBegin, vertexIteratorEnd) = vertices(directedGraph); vertexIteratorBegin != vertexIteratorEnd; vertexIteratorBegin++)
	{
		// Set the vertex initial cost to INT_MAX
		nodeCostMap.insert(pair<Vertex,int>(*vertexIteratorBegin, INT_MAX));
	}

	// Set the starting node cost to 0
	nodeCostMap[startingVertex] = 0;

	// Initialise the boost edge iterators
	EdgeIterator edgeIteratorBegin, edgeIteratorEnd;

	// For every vertex in the boost directed graph...
	for(tie(vertexIteratorBegin, vertexIteratorEnd) = vertices(directedGraph); vertexIteratorBegin != vertexIteratorEnd; vertexIteratorBegin++)
	{
		// Get the current vertex
		Vertex currentNode = vertex(*vertexIteratorBegin, directedGraph);
		
		// TODO####################################
		// For every out edge of the current vertex... 
		for(tie(edgeIteratorBegin, edgeIteratorEnd) = edges(directedGraph); edgeIteratorBegin != edgeIteratorEnd; edgeIteratorBegin++)
		{
			// Get the current edge's source node
			int sourceNodeCost = nodeCostMap[source(*edgeIteratorBegin, directedGraph)];

			// Get the current edge's target node
			int targetNodeCost = nodeCostMap[target(*edgeIteratorBegin, directedGraph)];

			// Get the current edge's weight
			int edgeWeight = edgeWeightMap[*edgeIteratorBegin];
			
			// If the current edge verifies the triangular inequality and has been accessed already...
			if(sourceNodeCost != INT_MAX && (sourceNodeCost + edgeWeight < targetNodeCost))
			{
				nodeCostMap[target(*edgeIteratorBegin, directedGraph)] = sourceNodeCost + edgeWeight;
			}
	 	}
	}

	// For all edges in the boost directed graph...
	for(tie(edgeIteratorBegin, edgeIteratorEnd) = edges(directedGraph); edgeIteratorBegin != edgeIteratorEnd; edgeIteratorBegin++)
	{
		// Get the current edge's source node
		int sourceNodeCost = nodeCostMap[source(*edgeIteratorBegin, directedGraph)];

		// Get the current edge's target node
		int targetNodeCost = nodeCostMap[target(*edgeIteratorBegin, directedGraph)];

		// Get the current edge's weight
		int edgeWeight = edgeWeightMap[*edgeIteratorBegin];

		//cout << "{" << source(*edgeIteratorBegin, directedGraph) << " -> " << target(*edgeIteratorBegin,directedGraph) <<"}" << " Edge Cost:" << edgeWeight << endl;

		// If negative cycle is detected...
		if(sourceNodeCost != INT_MAX && (sourceNodeCost + edgeWeight < targetNodeCost))
		{
			cout << "Graph contains negative weight cycle" << endl; 
			
			// Return false if a negative weight cycle is present in the directed graph
			return false;
		}
	}

	// Return true since the directed graph doesn't contain a negative weight cycle
	return true;
}

// Main function
int main()
{
	#pragma region Initialization

	// Create an empty boost directed graph
	DirectedGraph boostDirectedGraph;
	
	// Create an empty leda directed graph
	leda::graph ledaDirectedGraph;
	
	// User graph option
	std::string graphOption;

	// Number of nodes
	int numberOfNodes;

	cout << "Choose the testing graph between grid or random." << endl; 

	// Read the graph type
	cin >> graphOption;

	// If the grid graph is selected...
	if(graphOption == "grid")
	{
		cout << "Enter the number of nodes." << endl;

		// Read the number of nodes
		cin >> numberOfNodes;

		// Create a grid graph
		
		
		// Initialize a random seed
		srand(time(NULL));

		// For every edge in the undirected graph...
		// forall_edges(tempEdge, directedGraph)
		// {
		// 	// Assign random integer values as costs between 10 and 10000
		// 	directedGraph.assign(tempEdge, (rand() % 10000) - 100);
		// }
	}
	else
	{
		// If the random graph is selected...
		if(graphOption == "random")
		{
			cout << "Enter the number of nodes." << endl;

			// Read the number of nodes
			cin >> numberOfNodes;

			// Calculate the number of edges
			int numberOfEdges = ceil(1 * numberOfNodes * log2(numberOfNodes));

			// Generate a random directed graph
			random_graph(ledaDirectedGraph, numberOfNodes, numberOfEdges, false, true, true);

			// Make the graph cohesive
			Make_Connected(ledaDirectedGraph);

			// Intialise an edge array that will contain the leda graph edges weights
			edge_array<int> edgeWeightArray(ledaDirectedGraph);

			// Initialise a random seed
			srand(time(NULL));

			// Edge that will be used for the iteration
			leda::edge tempEdge;

			// For every edge in the undirected graph...
			forall_edges(tempEdge, ledaDirectedGraph)
			{
				// Assign random integer values as costs between 10 and 10000
				edgeWeightArray[tempEdge] = (rand() % 10100) - 100;
			}

			// Copy the leda directed graph to the boost directed graph
			CopyLedaGraphToBoostGraph(boostDirectedGraph, ledaDirectedGraph, edgeWeightArray);

			// Initialise a property map that contain the boost graph edges weights
			EdgeWeightMap edgeWeightMap = get(edge_weight, boostDirectedGraph);
		}
		else
		{
			cout << "Choose between grid or random." << endl;

			// Exit if another option is selected
			exit(0);
		}
	}

	#pragma endregion Initialization

	#pragma region Simulation

	// Number of nodes
	int numberOfExecutions;

	cout << "Enter the number of how many times you want the simulation to run." << endl; 

	// Read the graph type
	cin >> numberOfExecutions;

	// Get the index of a random boost directed graph vertex
	int randomBoostVertexIndex = rand() % ledaDirectedGraph.number_of_nodes();
	
	// Initialise the starting CPU time
	float CPUTime = used_time();

	// For 
	for(int index = 0; index < numberOfExecutions; index++)
	{
		// Execute the Bellman Ford algorithm for the boost directed graph using the random node
		bool executionFlag = BellmanFord(boostDirectedGraph, vertex(randomBoostVertexIndex, boostDirectedGraph));
	}
	
	// Print the user defined Kruscal execution time
	cout << "User Defined Boost Bellman Ford funtion execution time: " << (used_time(CPUTime)/numberOfExecutions) << "seconds."<< endl;
	
	#pragma endregion Simulation

	// Return 0
	return 0;
}
