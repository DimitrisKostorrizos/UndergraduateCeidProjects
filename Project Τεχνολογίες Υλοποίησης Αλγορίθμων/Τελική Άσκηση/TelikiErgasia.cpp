#include <iostream>
#include <time.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <boost/heap/pairing_heap.hpp>
#include <LEDA/graph/graph.h>

//#include <LEDA/graph/shortest_path.h>

//export LEDAROOT=/home/jim/Project/Leda/LEDA-6.3-free-fedora-core-8-64-g++-4.1.2; export LD_LIBRARY_PATH=$LEDAROOT
//g++ TelikiErgasia.cpp -o testcode -I$LEDAROOT/incl -L$LEDAROOT -lleda -lX11 -lm
//./testcode

using namespace std;
using namespace boost;
using namespace leda;

// Defien the boost priority Heap
typedef heap::pairing_heap<Vertex> Heap;

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

typedef graph_traits<DirectedGraph>::out_edge_iterator OutEdgeIterator;

// Define the edge iterator as edge_iterator
typedef graph_traits<DirectedGraph>::vertex_iterator VertexIterator;

// Define the edge weight map as a property map
typedef property_map<DirectedGraph, edge_weight_t>::type EdgeWeightMap;

inline double Heuristic() 
{
  return 5;
}

void AStarSearch(DirectedGraph& directedGraph, Vertex startingVertex, Vertex targetVertex)
{
	// Initialize the property map that contain the edges's weights
	EdgeWeightMap boostEdgeWeightMap = get(edge_weight, directedGraph);

	std::map<Vertex, double> currentPathCostMap;

	std::map<Vertex, Vertex> pathVertexesMap;

	// Set the initial vertex
	pathVertexesMap[startingVertex] = startingVertex;

	// Initialise the boost vertex iterators
	VertexIterator vertexIteratorBegin, vertexIteratorEnd;
	
	// Initialise the boost edge iterators
	OutEdgeIterator edgeIteratorBegin, edgeIteratorEnd;

	// Set the initial vertex
	Vertex currentVertex = startingVertex;

	double pathCost = 0;

  
	while (currentVertex != NULL) 
	{
		// Clear the cost map
		currentPathCostMap.clear();

		// If the target node was reached...
		if (currentVertex == targetVertex) 
		{
			cout << "Target found." << endl;
			break;
		}
		
		// For every out edge of the current vertex... 
		for(tie(edgeIteratorBegin, edgeIteratorEnd) = out_edges(startingVertex, directedGraph); edgeIteratorBegin != edgeIteratorEnd; edgeIteratorBegin++)
		{
			// Get the current edge's target node
			Vertex currentEdgeTargetVertex = target(*edgeIteratorBegin, directedGraph);

			// Get the current edge's weight
			double edgeWeight = boostEdgeWeightMap[*edgeIteratorBegin];

			// Calculate the new cost
			double newCost = pathCost + edgeWeight + Heuristic();

			// Set the cost to the edge's target
			currentPathCostMap[currentEdgeTargetVertex] = newCost;
		}

		double minimumCost = INT_MAX;

		Vertex minimumCostVertex;

		for (std::map<Vertex, double>::iterator mapIterator=currentPathCostMap.begin(); mapIterator!=currentPathCostMap.end(); ++mapIterator)
		{
			if(mapIterator->second < minimumCost)
			{
				minimumCostVertex = mapIterator->first;

				minimumCost = mapIterator->second;
			}
		}

		currentVertex = minimumCostVertex;

		pathCost += minimumCost;
	}
}

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
 * Applies the Bellman Ford algorithm to the @param directedGraph, using @param startingVertex
 * @param directedGraph The inserted boost directed graph
 * @param startingVertex The node that will be used as the minimum path's starting node
 * @return False if the graph contains a negative weight circle or true otherwise
 */
bool BellmanFord(DirectedGraph& directedGraph, Vertex startingVertex)
{
	// Initialize a node map containg the node minimum path cost
	std::map<Vertex, int> nodeCostMap;

	// Initialize the property map that contain the edges's weights
	EdgeWeightMap boostEdgeWeightMap = get(edge_weight, directedGraph);

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
		// For every out edge of the current vertex... 
		for(tie(edgeIteratorBegin, edgeIteratorEnd) = edges(directedGraph); edgeIteratorBegin != edgeIteratorEnd; edgeIteratorBegin++)
		{
			// Get the current edge's source node
			int sourceNodeCost = nodeCostMap[source(*edgeIteratorBegin, directedGraph)];

			// Get the current edge's target node
			int targetNodeCost = nodeCostMap[target(*edgeIteratorBegin, directedGraph)];

			// Get the current edge's weight
			int edgeWeight = boostEdgeWeightMap[*edgeIteratorBegin];
			
			// If the current edge verifies the triangular inequality and has already been accessed...
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
		int edgeWeight = boostEdgeWeightMap[*edgeIteratorBegin];

		// If negative cycle is detected...
		if(sourceNodeCost != INT_MAX && (sourceNodeCost + edgeWeight < targetNodeCost))
		{
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

	//Create an empty edge array
	edge_array<int> ledaEdgeWeightArray;
	
	// User graph option
	std::string graphOption;

	// Number of nodes
	int numberOfNodes;

	cout << "Choose the testing graph between grid or random." << endl; 

	// Read the graph type
	cin >> graphOption;

	cout << "Enter the number of nodes." << endl;

	// Read the number of nodes
	cin >> numberOfNodes;

	// If the grid graph is selected...
	if(graphOption == "grid")
	{
		// Create a grid graph
		grid_graph(ledaDirectedGraph, numberOfNodes);

		// Intialise an edge array that will contain the leda graph edges weights
		edge_array<int> edgeWeightArray(ledaDirectedGraph);

		// Copy the edge array
		ledaEdgeWeightArray = edgeWeightArray;

		// Initialise a random seed
		srand(time(NULL));

		// Edge that will be used for the iteration
		leda::edge tempEdge;

		// For every edge in the undirected graph...
		forall_edges(tempEdge, ledaDirectedGraph)
		{
			// Get the current edge source node index
			int tempEdgeSourceNodeIndex = ledaDirectedGraph.index(ledaDirectedGraph.source(tempEdge));

			// Get the current edge target node index
			int tempEdgeTargetNodeIndex = ledaDirectedGraph.index(ledaDirectedGraph.target(tempEdge));

			// Get the point representation of the edge's source node index
			div_t tempEdgeSourceNodeIndexDivResult = div(tempEdgeSourceNodeIndex, numberOfNodes);

			// Get the point representation of the edge's target node index
			div_t tempEdgeTargetNodeIndexDivResult = div(tempEdgeTargetNodeIndex, numberOfNodes);

			// Check if the edge is a vertical edge that belong in the third quarter
			bool verticalEdgeThirdQuarterPresence = (tempEdgeSourceNodeIndexDivResult.quot >= (numberOfNodes/2)) && (tempEdgeSourceNodeIndexDivResult.rem <= (numberOfNodes/2)) && (tempEdgeTargetNodeIndexDivResult.quot > (numberOfNodes/2)) && (tempEdgeTargetNodeIndexDivResult.rem < (numberOfNodes/2));

			// Check if the edge is a horizontal edge that belong in the third quarter
			bool horizontalEdgeThirdQuarterPresence = (tempEdgeSourceNodeIndexDivResult.quot > (numberOfNodes/2)) && (tempEdgeSourceNodeIndexDivResult.rem < (numberOfNodes/2)) && (tempEdgeTargetNodeIndexDivResult.quot >= (numberOfNodes/2)) && (tempEdgeTargetNodeIndexDivResult.rem <= (numberOfNodes/2));

			// If the edge belongs into the third quarter...
			if(verticalEdgeThirdQuarterPresence || horizontalEdgeThirdQuarterPresence)
			{
				// If the current edge, was randomly chosen to reversed...
				if((rand() % 2) == 0)
				{
					// Reverse the current edge
					ledaDirectedGraph.rev_edge(tempEdge);
				}
				
				// Check if the edge is the special horizontal edge
				bool specialThirdQuarterHorizontalEdge = (tempEdgeSourceNodeIndexDivResult.quot == (numberOfNodes/2 + 1)) && (tempEdgeSourceNodeIndexDivResult.rem == (numberOfNodes/2 - 1)) && (tempEdgeTargetNodeIndexDivResult.quot == (numberOfNodes/2 + 1)) && (tempEdgeTargetNodeIndexDivResult.rem == (numberOfNodes/2));

				// Check if the edge is the special vertical edge
				bool specialThirdQuarterVerticalEdge = (tempEdgeSourceNodeIndexDivResult.quot == (numberOfNodes/2)) && (tempEdgeSourceNodeIndexDivResult.rem == (numberOfNodes/2 - 1)) && (tempEdgeTargetNodeIndexDivResult.quot == (numberOfNodes/2 + 1)) && (tempEdgeTargetNodeIndexDivResult.rem == (numberOfNodes/2 - 1));

				// If the edge is either the special negative weight vertical edge or the special negative weight horizontal edge...
				if(specialThirdQuarterVerticalEdge || specialThirdQuarterHorizontalEdge)
				{
					// Assign -100000 as weight to the current special edge
					ledaEdgeWeightArray[tempEdge] = -100000;
				}
			}
			else
			{
				// Assign random integer values as costs between 0 and 10000
				ledaEdgeWeightArray[tempEdge] = (rand() % 10000);
			}
		}
		// Get the grid graph number of nodes
		numberOfNodes = ledaDirectedGraph.number_of_nodes();

		// Copy the leda directed graph to the boost directed graph
		CopyLedaGraphToBoostGraph(boostDirectedGraph, ledaDirectedGraph, ledaEdgeWeightArray);

		// Initialise a property map that contain the boost graph edges weights
		EdgeWeightMap boostEdgeWeightMap = get(edge_weight, boostDirectedGraph);
	}
	else
	{
		// If the random graph is selected...
		if(graphOption == "random")
		{
			// Calculate the number of edges
			int numberOfEdges = ceil(20 * numberOfNodes * log2(numberOfNodes));

			// Generate a random directed graph
			random_graph(ledaDirectedGraph, numberOfNodes, numberOfEdges, false, true, true);

			// Make the graph cohesive
			Make_Connected(ledaDirectedGraph);

			// Intialise an edge array that will contain the leda graph edges weights
			edge_array<int> edgeWeightArray(ledaDirectedGraph);

			// Copy the edge array
			ledaEdgeWeightArray = edgeWeightArray;

			// Initialise a random seed
			srand(time(NULL));

			// Edge that will be used for the iteration
			leda::edge tempEdge;

			// For every edge in the undirected graph...
			forall_edges(tempEdge, ledaDirectedGraph)
			{
				// Assign random integer values as costs between 10 and 10000
				ledaEdgeWeightArray[tempEdge] = (rand() % 10100) - 100;
			}

			// Copy the leda directed graph to the boost directed graph
			CopyLedaGraphToBoostGraph(boostDirectedGraph, ledaDirectedGraph, ledaEdgeWeightArray);

			// Initialise a property map that contain the boost graph edges weights
			EdgeWeightMap boostEdgeWeightMap = get(edge_weight, boostDirectedGraph);
		}
		else
		{
			cout << "Choose between grid or random." << endl;

			// Exit if another option is selected
			exit(0);
		}
	}

	// Choose a random node from the Leda directed graph
	node randomLedaNode = ledaDirectedGraph.choose_node();

	// Get the index of the Boost directed graph vertex that correspond to the appropriate Leda random chosen node
	Vertex randomBoostVertex = vertex(ledaDirectedGraph.index(randomLedaNode), boostDirectedGraph);
	
	// Initialise a node array the will contain the last edge on a shortest path from the starting node to a node
	node_array<leda::edge> ledaPredecessorNodeArray(ledaDirectedGraph);

	// Initialise a node array the will contain the shortest path langth from the starting node to a node
	node_array<int> ledaDistanceNodeArray(ledaDirectedGraph);

	// Initialize a property map that contain the edges's weights
	EdgeWeightMap boostEdgeWeightMap = get(edge_weight, boostDirectedGraph);

	// Initialize a vector that will contain the distance to each node and set the initial distance to INT_MAX
	std::vector<int> boostDistanceVector(numberOfNodes,INT_MAX);

	// Set the distance of the chosen vertex to 0
	boostDistanceVector[randomBoostVertex] = 0;

	// Initialize a vector that will contain the predeccesor of each node
	std::vector<std::size_t> boostPredeccesorVector(numberOfNodes);

	// For every vertex in the boost directed graph...
	for(int index = 0; index < numberOfNodes; index++)
	{
		// Set the current vertex predeccesor to itself
		boostPredeccesorVector[index] = index;
	}
	
	#pragma endregion Initialization

	#pragma region Simulation

	// Initialise the starting CPU time
	float CPUTime = used_time();

	// Print the user defined Bellman Ford function execution time
	cout << "User defined Bellman Ford function execution time: " << used_time(CPUTime) << " seconds."<< endl;

	#pragma endregion Simulation

	// Return 0
	return 0;
}
