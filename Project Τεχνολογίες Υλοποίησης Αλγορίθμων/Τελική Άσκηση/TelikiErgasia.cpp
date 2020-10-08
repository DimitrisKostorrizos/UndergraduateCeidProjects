#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <LEDA/graph/graph.h>
#include <LEDA/graph/shortest_path.h>

using namespace std;
using namespace boost;
using namespace leda;

// Define the boost edge weight property
typedef property<edge_weight_t, double> EdgeWeightProperty;

// Define the boost directed graph: std::vector, std::vector, directed, no vertex property, double edge property, no graph property, std::list
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

/**
 * Calculates the heuristic value for the @param selectedVertex and @param targetVertex
 * @param Vertex The selected vertex
 * @param Vertex The target vertex
 * @return The heuristic value
 */
inline double HeuristicFunction(Vertex selectedVertex, Vertex targetVertex) 
{
	// If the vertexes are the same...
	if(targetVertex == selectedVertex)
		// Return the heuristic
		return 0;

	// Calculate the heuristic
	double heuristicValue = selectedVertex - targetVertex;

	// Return the heuristic
	return abs(heuristicValue);
}

// The struct for the bool operation overloading
struct PairCompare
{
	/**
	 * Compares the pairs
	 * @param right The rightt operand
	 * @param left The left operand
	 * @return Comparison boolean value
	 */
	bool operator()(const pair<Vertex, double>& right, const pair<Vertex, double>& left)
	{
		return right.second < left.second;
	}
};

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

	// Declare a map for the the vertexes and the heuristic cost to visit them 
	std::map<Vertex, double> vertexHeuristicCostMap;

	// Declare the boost vertex iterators
	VertexIterator vertexIteratorBegin, vertexIteratorEnd;

	// For every vertex in the boost directed graph...
	for(tie(vertexIteratorBegin, vertexIteratorEnd) = vertices(directedGraph); vertexIteratorBegin != vertexIteratorEnd; vertexIteratorBegin++)
	{
		// Set the vertex initial cost to DBL_MAX
		vertexVisitCostMap.insert(pair<Vertex, double>(*vertexIteratorBegin, DBL_MAX));

		// Set the vertex initial cost to DBL_MAX
		vertexHeuristicCostMap.insert(pair<Vertex, double>(*vertexIteratorBegin, 0));
	}
	
	// Declare the boost out edge iterators
	OutEdgeIterator edgeIteratorBegin, edgeIteratorEnd;

	// Declare the vector for possible vertex successors
	std::vector<Vertex> possibleVertexSuccesorVector;

	// Insert the starting vertex
	possibleVertexSuccesorVector.push_back(startingVertex);

	// Set the starting vertex visit cost to 0
	vertexVisitCostMap[startingVertex] = 0;

	// Set the starting vertex heuristic cost
	vertexHeuristicCostMap[startingVertex] = HeuristicFunction(startingVertex, startingVertex);

	// While there is a vertex to search...
	while (!possibleVertexSuccesorVector.empty()) 
	{
		// Get an iterator that point to the vertex with the minimum heuristic value
		auto it = *min_element(vertexHeuristicCostMap.begin(), vertexHeuristicCostMap.end(), PairCompare());
		
		// Get the vertex from the iterator
		Vertex currentVertex = it.first;

		// If the target node was reached...
		if (currentVertex == targetVertex) 
		{
			// Return true
			return true;
		}

		// Search the target vertex
		auto iterator = find(possibleVertexSuccesorVector.begin(), possibleVertexSuccesorVector.end(), currentVertex);

		// If the element doesn't exist...
		if(iterator == possibleVertexSuccesorVector.end())
			// Clear the vector
			possibleVertexSuccesorVector.clear();
		else
			// Remove the current vertex
			possibleVertexSuccesorVector.erase(iterator, possibleVertexSuccesorVector.end());
		
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
				// Set the visit cost to the edge's target
				vertexVisitCostMap[currentEdgeTargetVertex] = targetVertexVisitCost;

				// Set the heuristic cost to the edge's target
				vertexHeuristicCostMap[currentEdgeTargetVertex] = targetVertexVisitCost + HeuristicFunction(startingVertex, currentEdgeTargetVertex);

				// Search the target vertex
				auto iterator = find(possibleVertexSuccesorVector.begin(), possibleVertexSuccesorVector.end(), currentEdgeTargetVertex);

				// If the edge's target doesn't exist in the vector...
				if(iterator == possibleVertexSuccesorVector.end())
				{
					// Add it
					possibleVertexSuccesorVector.push_back(currentEdgeTargetVertex);
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
void CopyLedaGraphToBoostGraph(DirectedGraph& BoostDirectedGraph, leda::graph& LedaGraph, edge_array<double>& LedaEdgeWeightMap)
{
	// Create a new boost directed graph containing the smae number of nodes as the leda directed graph
	DirectedGraph boostGraph(LedaGraph.number_of_nodes());

	// Leda edge that will be used for iteration
	leda::edge iterationEdge;

	// For all edges in the leda directed graph
	forall_edges(iterationEdge, LedaGraph)
	{
		// Get the source node of the edge
		node source = LedaGraph.source(iterationEdge);

		// Get the target node of the edge
		node target = LedaGraph.target(iterationEdge);

		// Get the weight of the edge
		double currentEdgeWeight = LedaEdgeWeightMap[iterationEdge];

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
	edge_array<double> ledaEdgeWeightArray;
	
	// User graph option
	std::string graphOption;

	// Number of nodes
	int numberOfNodes;

	cout << "Choose the testing graph between grid, complete or random." << endl; 

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
	}
	else
	{
		// If the random graph is selected...
		if(graphOption == "random")
		{
			// Calculate the number of edges
			int numberOfEdges = ceil(numberOfNodes * (numberOfNodes - 1));

			// Generate a random directed graph
			random_graph(ledaDirectedGraph, numberOfNodes, numberOfEdges, false, true, true);

			// Make the graph cohesive
			Make_Connected(ledaDirectedGraph);
		}
		else
		{
			// If the complete graph is selected...
			if(graphOption == "complete")
			{
				// Create a complete graph
				complete_graph(ledaDirectedGraph, numberOfNodes);
			}
			else
			{
				cout << "Choose between grid, complete or random." << endl;

				// Exit if another option is selected
				exit(0);
			}
		}
	}

	// Intialise an edge array that will contain the leda graph edges weights
	edge_array<double> edgeWeightArray(ledaDirectedGraph);

	// Copy the edge array
	ledaEdgeWeightArray = edgeWeightArray;

	// Initialise a random seed
	srand(time(NULL));

	// Edge that will be used for the iteration
	leda::edge iterationEdge;

	// For every edge in the undirected graph...
	forall_edges(iterationEdge, ledaDirectedGraph)
	{
		// Assign random integer values as costs between 10 and 10000
		ledaEdgeWeightArray[iterationEdge] = (rand() % 100) + 1;
	}

	// Get the grid graph number of nodes
	numberOfNodes = ledaDirectedGraph.number_of_nodes();

	// Copy the leda directed graph to the boost directed graph
	CopyLedaGraphToBoostGraph(boostDirectedGraph, ledaDirectedGraph, ledaEdgeWeightArray);

	// Initialise a property map that contain the boost graph edges weights
	EdgeWeightMap boostEdgeWeightMap = get(edge_weight, boostDirectedGraph);

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
	node_array<double> ledaDistanceNodeArray(ledaDirectedGraph);
	
	#pragma endregion Initialization

	#pragma region Simulation

	// Initialise the starting CPU time
	float CPUTime = used_time();

	// Execute user defined ALT function
	ALT(boostDirectedGraph, startingRandomBoostVertex, targetRandomBoostVertex);

	// Print the user defined ALT function execution time
	cout << "User defined ALT function execution time: " << used_time(CPUTime) << " seconds."<< endl;

	// Execute leda defined shortest path function
	SHORTEST_PATH_T(ledaDirectedGraph, startingRandomLedaNode, ledaEdgeWeightArray, ledaDistanceNodeArray, ledaPredecessorNodeArray);

	// Execute leda defined compute shortest path function
	COMPUTE_SHORTEST_PATH(ledaDirectedGraph, startingRandomLedaNode, targetRandomLedaNode, ledaPredecessorNodeArray);

	// Print the leda defined compute shortest path function execution time
	cout << "Leda defined compute shortest path function execution time: " << used_time(CPUTime) << " seconds."<< endl;

	#pragma endregion Simulation

	// Return 0
	return 0;
}
