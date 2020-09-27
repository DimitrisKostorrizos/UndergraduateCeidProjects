#include <iostream>
#include <time.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <LEDA/graph/graph.h>


//#include <LEDA/graph/shortest_path.h>

//export LEDAROOT=/home/jim/Project/Leda/LEDA-6.3-free-fedora-core-8-64-g++-4.1.2; export LD_LIBRARY_PATH=$LEDAROOT
//g++ TelikiErgasia.cpp -o testcode -I$LEDAROOT/incl -L$LEDAROOT -lleda -lX11 -lm
//./testcode

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

typedef graph_traits<DirectedGraph>::out_edge_iterator OutEdgeIterator;

// Define the edge iterator as edge_iterator
typedef graph_traits<DirectedGraph>::vertex_iterator VertexIterator;

// Define the edge weight map as a property map
typedef property_map<DirectedGraph, edge_weight_t>::type EdgeWeightMap;

inline double Heuristic() 
{
  return 5;
}

/**
 * 
 * @param
 * @param
 * @param
 */
bool ALT(DirectedGraph& directedGraph, Vertex startingVertex, Vertex targetVertex)
{
	// Initialize the property map that contain the edges's weights
	EdgeWeightMap boostEdgeWeightMap = get(edge_weight, directedGraph);

	// Declare a map for the the vertexes and the cost to traverse them
	std::map<Vertex, double> outgoingPathCostMap;

	// Initialise the boost vertex iterators
	VertexIterator vertexIteratorBegin, vertexIteratorEnd;
	
	// Initialise the boost edge iterators
	OutEdgeIterator edgeIteratorBegin, edgeIteratorEnd;

	// Set the initial vertex
	Vertex lastVisitedVertex = startingVertex;

	// Initialize the path cost
	double totalPathCost = 0;

	// While there is a vertex to search...
	while (lastVisitedVertex != 0) 
	{
		// Clear the cost map
		outgoingPathCostMap.clear();

		// If the target node was reached...
		if (lastVisitedVertex == targetVertex) 
		{
			cout << "Traversed path total cost: " << totalPathCost << endl;

			// Return true
			return true;
		}
		
		// For every out edge of the current vertex... 
		for(tie(edgeIteratorBegin, edgeIteratorEnd) = out_edges(startingVertex, directedGraph); edgeIteratorBegin != edgeIteratorEnd; edgeIteratorBegin++)
		{
			// Get the current edge's target node
			Vertex currentEdgeTargetVertex = target(*edgeIteratorBegin, directedGraph);

			// Get the current edge's weight
			double edgeWeight = boostEdgeWeightMap[*edgeIteratorBegin];

			// Calculate the new cost
			double newCost = totalPathCost + edgeWeight + Heuristic();

			// Set the cost to the edge's target
			outgoingPathCostMap[currentEdgeTargetVertex] = newCost;
		}

		// Set the minimum cost to maximum double
		double minimumCost = DBL_MAX;

		// Declare the vertex with the minimum cost
		Vertex minimumCostVertex = 0;

		// For every selected vertex...
		for (std::map<Vertex, double>::iterator mapIterator = outgoingPathCostMap.begin(); mapIterator!=outgoingPathCostMap.end(); ++mapIterator)
		{
			// If the vertex travel cost is less the the previous minimum cost...
			if(mapIterator->second < minimumCost)
			{
				// Set the vertex as the new vertex
				minimumCostVertex = mapIterator->first;

				// Set the vertex's costs as the minimum cost
				minimumCost = mapIterator->second;
			}
		}

		// Set the last visited vertex
		lastVisitedVertex = minimumCostVertex;

		// Add the traversal cost to the path cost
		totalPathCost += minimumCost;
	}

	cout << "Traversed path total cost: " << totalPathCost << endl;

	// Return false
	return false;
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
			// Assign random integer values as costs between 10 and 10000
			ledaEdgeWeightArray[tempEdge] = rand() % 100;
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
				ledaEdgeWeightArray[tempEdge] = rand() % 100;
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
	node startingRandomLedaNode = ledaDirectedGraph.choose_node();

	// Choose a random node from the Leda directed graph
	node targetRandomLedaNode = ledaDirectedGraph.choose_node();

	// Get the index of the Boost directed graph vertex that correspond to the appropriate Leda random chosen node
	Vertex startingRandomBoostVertex = vertex(ledaDirectedGraph.index(startingRandomLedaNode), boostDirectedGraph);

	// Get the index of the Boost directed graph vertex that correspond to the appropriate Leda random chosen node
	Vertex targetRandomBoostVertex = vertex(ledaDirectedGraph.index(targetRandomLedaNode), boostDirectedGraph);
	
	// Initialise a node array the will contain the last edge on a shortest path from the starting node to a node
	node_array<leda::edge> ledaPredecessorNodeArray(ledaDirectedGraph);

	// Initialise a node array the will contain the shortest path langth from the starting node to a node
	node_array<int> ledaDistanceNodeArray(ledaDirectedGraph);

	// Initialize a property map that contain the edges's weights
	EdgeWeightMap boostEdgeWeightMap = get(edge_weight, boostDirectedGraph);

	// Initialize a vector that will contain the distance to each node and set the initial distance to INT_MAX
	std::vector<int> boostDistanceVector(numberOfNodes,INT_MAX);

	// Initialize a vector that will contain the predeccesor of each node
	std::vector<std::size_t> boostPredeccesorVector(numberOfNodes);
	
	#pragma endregion Initialization

	#pragma region Simulation

	// Initialise the starting CPU time
	float CPUTime = used_time();

	// Execute user defined ALT function
	bool targetVertexFound = ALT(boostDirectedGraph, startingRandomBoostVertex, targetRandomBoostVertex);

	// If the target was found...
	if(targetVertexFound)
		cout << "Target found." << endl;
	else
		cout << "Target not found." << endl;

	// Print the user defined ALT function execution time
	cout << "User defined ALT function execution time: " << used_time(CPUTime) << " seconds."<< endl;

	#pragma endregion Simulation

	// Return 0
	return 0;
}
