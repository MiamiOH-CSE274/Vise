/*****
 * Author   : brinkmwj
 * Date     : 2009-11-06
 * Sources  : All code is original
 */
#include "Graph.h"

Graph::Graph(unsigned int numNodes){
  adjList.resize(numNodes);
}

int Graph::getCost(int node1, int node2){
	for(int i = 0; i< adjList[node1].edgeList.size(); i++){
		if(adjList[node1].edgeList[i].dest==node2)
			return adjList[node1].edgeList[i].cost;
	}
	return -1;
}

//Add an edge from node1 to node2, and from node2 to node1, with
// the given cost. If the cost is < 0, throw a string exception.
void Graph::addEdge(int node1, int node2, double cost){
  if(cost<0)
	  throw (std::string) "cost must be >= 0";
  Edge* toAdd = new Edge(cost,node2);
  adjList[node1].edgeList.push_back(*toAdd);
  toAdd = new Edge(cost,node1);
  adjList[node2].edgeList.push_back(*toAdd);
}

//Remove the edge from node1 to node2, and also from node2 to node1.
// If there are no such edges, then don't do anything.
void Graph::removeEdge(int node1, int node2){
  for(int i = 0; i < adjList[node1].edgeList.size(); i++)
	  if(adjList[node1].edgeList[i].dest==node2){
		  adjList[node1].edgeList.erase(adjList[node1].edgeList.begin()+i);
		  break;
	  }

  for(int i = 0; i < adjList[node2].edgeList.size(); i++)
	  if(adjList[node2].edgeList[i].dest==node1){
		  adjList[node2].edgeList.erase(adjList[node2].edgeList.begin()+i);
		  break;
	  }
}
