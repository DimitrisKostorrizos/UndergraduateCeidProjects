#include <iostream>
#include <time.h>
#include <algorithm>
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
	// Initialise a random seed
	srand(time(NULL));

	return rand() % 10;
}

/**
 * Executes the ALT algorithm, namely a A* algorithm implementation, using landmarks and the triangle inequality 
 * @param DirectedGraph The boost directed Graph
 * @param Vertex The starting vertex
 * @param Vertex The target vertex
 * @return True if the target vertex is found, or false if the target vertex is not found
 */
bool ALT(DirectedGraph& directedGraph, Vertex startingVertex, Vertex targetVertex)
{
	// Initialize the property map that contain the edges's weights
	EdgeWeightMap boostEdgeWeightMap = get(edge_weight, directedGraph);

	// Declare a map for the the vertexes and the cost to visit them
	std::map<Vertex, double> vertexVisitCostMap;

	// Declare a map for the the vertexes and the next visisted vertexes
	std::map<Vertex, Vertex> vertexSuccessorMap;

	// Declare the boost vertex iterators
	VertexIterator vertexIteratorBegin, vertexIteratorEnd;

	// For every vertex in the boost directed graph...
	for(tie(vertexIteratorBegin, vertexIteratorEnd) = vertices(directedGraph); vertexIteratorBegin != vertexIteratorEnd; vertexIteratorBegin++)
	{
		// Set the vertex initial cost to DBL_MAX
		vertexVisitCostMap.insert(pair<Vertex, double>(*vertexIteratorBegin, DBL_MAX));
	}
	
	// Declare the boost out edge iterators
	OutEdgeIterator edgeIteratorBegin, edgeIteratorEnd;

	// Declare the set for possible vertex successors
	set<Vertex> possibleVertexSuccesorSet;

	// Insert the starting vertex
	possibleVertexSuccesorSet.insert(startingVertex);

	// Declare a map for the the vertexes and the heuristic cost to visit them 
	std::map<Vertex, double> vertexHeuristicCostMap;

	// Set the starting vertex visit cost to 0
	vertexVisitCostMap[startingVertex] = 0;

	// Set the starting vertex heuristic cost
	vertexHeuristicCostMap[startingVertex] = Heuristic();

	// While there is a vertex to search...
	while (!possibleVertexSuccesorSet.empty()) 
	{
		// Get an iterator that point to the vertex with the minimum heuristic value
		auto it = std::min_element(std::begin(vertexHeuristicCostMap), std::end(vertexHeuristicCostMap),[](const auto& l, const auto& r) { return l.second < r.second; });
		
		// Get the vertex from the iterator
		Vertex currentVertex = it->first;

		// If the target node was reached...
		if (currentVertex == targetVertex) 
		{
			// Return true
			return true;
		}

		// Remove the current vertex
		possibleVertexSuccesorSet.erase(currentVertex);
		
		// For every out edge of the current vertex... 
		for(tie(edgeIteratorBegin, edgeIteratorEnd) = out_edges(currentVertex, directedGraph); edgeIteratorBegin != edgeIteratorEnd; edgeIteratorBegin++)
		{
			// Get the current edge's target node
			Vertex currentEdgeTargetVertex = target(*edgeIteratorBegin, directedGraph);

			// Get the current edge's weight
			double currentEdgeWeight = boostEdgeWeightMap[*edgeIteratorBegin];

			// Calculate the target vertex visit cost
			double targetVertexVisitCost = vertexVisitCostMap[currentVertex] + currentEdgeWeight;

			// If the the path to this node is better than the previous one...
			if(targetVertexVisitCost < vertexVisitCostMap[currentEdgeTargetVertex])
			{
				// Add the new vertex into the visisted vertexes
				vertexSuccessorMap.insert(pair<Vertex, Vertex>(currentVertex, currentEdgeTargetVertex));
				
				// Set the visit cost to the edge's target
				vertexVisitCostMap[currentEdgeTargetVertex] = targetVertexVisitCost;

				// Set the heuristic cost to the edge's target
				vertexHeuristicCostMap[currentEdgeTargetVertex] = Heuristic();

				// If the edge's target doesn't exist in the set...
				if(possibleVertexSuccesorSet.find(currentEdgeTargetVertex) == possibleVertexSuccesorSet.end())
				{
					// Add it
					possibleVertexSuccesorSet.insert(currentEdgeTargetVertex);
				}
			}
		}
	}

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
		int currentEdgeWeight = LedaEdgeWeightMap[tempEdge];

		// Add the edge in the boost directed graph
		add_edge(LedaGraph.index(source), LedaGraph.index(target), currentEdgeWeight, boostGraph);
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
