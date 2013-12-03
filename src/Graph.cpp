/*****
 * Author   : brinkmwj
 * Date     : 2009-11-06
 * Sources  : All code is original
 */
#include "Graph.h"

Graph::Graph(unsigned int numNodes){
	adjList.resize(numNodes);
}

/*int Graph::getCost(int node1, int node2){
	if(node1>adjList.size()||node2>adjList.size())
		return -1;
	std::vector<Edge> x =adjList.at(node1).edgeList;
	std::vector<Edge> y =adjList.at(node2).edgeList;

	for(unsigned int i=0;i<x.size();i++)
			if(x.at(i).dest==node2)
				return x.at(i).cost;
	for(unsigned int j=0;j<y.size();j++)
		if(y.at(j).dest==node2)
				return y.at(j).cost;
  return -1;
}*/

//Add an edge from node1 to node2, and from node2 to node1, with
// the given cost. If the cost is < 0, throw a string exception.
void Graph::addEdge(int node1, int node2){

	if(node1>adjList.size()||node2>adjList.size())
		return;
	Edge* x = new Edge(node2);
	adjList.at(node1).edgeList.push_back(*x);

}
void Graph::Setup(){
	for( int i=0;i<400;i++){
		//adjList.at(i).edgeList.
		if(i-20>0){
			if(((i%40)>=20) && (i+1<20))
				addEdge(i,i-21);
			addEdge(i,i-20);
			if(((i%40)<20) && (i-1>0))
				addEdge(i,i-19);
		}
		if(i-1>0)
			addEdge(i,i-1);
		if(i+1<20)             //This one wont work correctly, it will just loop around. Going to need something like i%20 maybe
			addEdge(i,i+1);
		if(i+20<400){
			if(((i%40)<20) && (i-1>0))
				addEdge(i,i+19);
			addEdge(i,i+20);
			if(((i%40)>=20) && (i+1<20))
				addEdge(i,i+21);
		}
		/*if(i-21>0)
			addEdge(i,i-21);
		if(i+21<400)
			addEdge(i,i+21);*/
	}
}
int Graph::getPiece(int x, int y){
	return adjList.at((y*20)+x).piece;
}
int* Graph::getNeighbors(int x, int y){
	int* neighborList = new int[adjList.at((y*20)+x).edgeList.size()];
	for (int edgeCount = 0; edgeCount < adjList.at((y*20)+x).edgeList.size(); edgeCount++)
		neighborList[edgeCount] = adjList.at((y*20)+x).edgeList.at(edgeCount);
	return neighborList;
}
void Graph::placePiece(int x, int y, int given){
	adjList.at((y*20)+x).piece=given;
}
//int Graph::getClose(int x, int y, int hex){
bool Graph::isClose(int x1, int y1, int x2, int y2){
	//return adjList.at( adjList.at((y*20)+x).edgeList.at(hex).dest).piece;
	for (int edgeCount = 0; edgeCount < adjList.at((y1*20)+x1).edgeList.size(); edgeCount++){
		if (adjList.at((y1*20)+x1).edgeList.at(edgeCount) == adjList.at((y2*20)+x2))
			return true;
	}
	return false;
}