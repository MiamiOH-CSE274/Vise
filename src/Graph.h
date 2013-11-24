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
  Edge(int d){ dest = d;};
  Edge(){dest = -1;};

  int dest; //Destination node number
};

class Node{
public:
  int piece;
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
  void addEdge(int node1, int node2);
  //sets up the board for the vise, 400 spots
  void Setup();
  //gets the piece number at that position
  int getPiece(int x, int y);
  void placePiece(int x, int y, int given);
  int getClose(int x, int y, int hex);

private:
  std::vector<Node> adjList;	
};
