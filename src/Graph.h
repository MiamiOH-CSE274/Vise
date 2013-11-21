/*****
 * Author   : brinkmwj
 * Date     : 2009-11-06
 * Sources  : All code is original
 * 
 * This class uses the adjacency list representation of graphs, but 
 * using vector for both the main array and for the actual adjacency "lists"
 */

#include <vector>

//The edge class has only a cost and a destination.
class Edge{
public:
  Edge(double c, int d){cost = c; dest = d;};
  Edge(){cost = -1; dest = -1;};

  double cost;
  int dest; //Destination node number
};

class Node{
public:
  std::vector<Edge> edgeList;
};

//A Graph is just a list of nodes, where each node is responsible
// for keeping a list of the edges adjacent to itself.
class Graph{
public:
  //You will need to resize the adjList before you can use it
  Graph(unsigned int numVertices);
  
  //Return the cost of the edge from node1 to node2. If there
  // is no edge, return -1.
  int getCost(int node1, int node2);

  //Add an edge from node1 to node2, and from node2 to node1, with
  // the given cost. If the cost is < 0, throw a string exception.
  // If the edge already exists, just update the cost
  void addEdge(int node1, int node2, double cost);

  //Remove the edge from node1 to node2, and also from node2 to node1.
  // If there are no such edges, then don't do anything.
  void removeEdge(int node1, int node2);

private:
  std::vector<Node> adjList;	
};
