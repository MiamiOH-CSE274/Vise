/*****
 * Author   : brinkmwj
 * Date     : 2009-11-06
 * Sources  : All code is original
 */
#include "Graph.h"

Graph::Graph(unsigned int numNodes){
	adjList.resize(numNodes);
}


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
		if(i-20>0){
			if(((i%40)>=20) && (i+1<20))
				addEdge(i,i-19);
			addEdge(i,i-20);
			if(((i%40)<20) && (i-1>0))
				addEdge(i,i-21);
		}
		if(i%20>0)
			addEdge(i,i-1);
		if(i%20<20) 
			if(i!=399)
				addEdge(i,i+1);			
		if(i+20<400){
			if(((i%40)<20) && ((i-1)%20>0))
				
					addEdge(i,i+19);
			addEdge(i,i+20);
			if(((i%40)>=20) && ((i+1)%20<20))
				if(i!=379)
				addEdge(i,i+21);
		}
		adjList.at(i).piece=0;
		if(i==210)
			adjList.at(i).piece=1;
		if(i==211)
			adjList.at(i).piece=2;
	}
}
int Graph::getPiece(int x, int y){
	return adjList.at((y*20)+x).piece;
}
int* Graph::getNeighbors(int x, int y){
	int* neighborList = new int[adjList.at((y*20)+x).edgeList.size()];
	for (int edgeCount = 0; edgeCount < adjList.at((y*20)+x).edgeList.size(); edgeCount++)
		neighborList[edgeCount] = adjList.at((y*20)+x).edgeList.at(edgeCount).dest;
	return neighborList;
}
int Graph::getNeighborListSize(int x, int y){
	return adjList.at(y*20+x).edgeList.size();
}
void Graph::placePiece(int x, int y, int given){
	adjList.at((y*20)+x).piece=given;
}

int Graph::getClose(int x, int y, int hex){
	//if(adjList.at(y*20+x).piece==0);
	if(hex < adjList.at(y*20+x).edgeList.size())//adjList.at(y*20+x) //adjList.at( adjList.at((y*20)+x).edgeList.size()))
		return adjList.at( adjList.at((y*20)+x).edgeList.at(hex).dest).piece;
	else
		return 0;
}
int Graph::getPiece(int i){
	return adjList.at(i).piece;
}
int Graph::getConnected(int i){
	if(adjList.at(i).piece==0)
		return 0;
	std::vector<int> list;
	list.push_back(i);
	for(int j=0;j<6;j++)
		getConnected(adjList.at(i).edgeList.at(j).dest);//   .at(j).edgeList());

	return list.size();
}
//int Graph::getClose(int x, int y, int hex){
bool Graph::isClose(int x1, int y1, int x2, int y2){
	for (int edgeCount = 0; edgeCount < adjList.at((y2*20)+x2).edgeList.size(); edgeCount++){
		if (adjList.at((y2*20)+x2).edgeList.at(edgeCount).dest == (y1*20)+x1)
			return true;
	}
	return false;
}
void Graph::checkNbrs(int x, int y, int& okayNbrs, int& badNbrs, int whoseTurn){
	int j=adjList.at(20*y+x).edgeList.size();
	for(int i=0;i<j;i++){
		int t=getClose(x,y, i);
		if(t!=0)
			if(t==whoseTurn)
				okayNbrs++;
			else 
				badNbrs++;
	}
}
bool Graph::inVise(int x, int y){
	//std::vector<int> list;//= new std::vector<int>();
	//int player=getPiece(x,y);
	//for(int i=0;i<adjList.at(20*y+x).edgeList.size();i++){
	//	if(adjList.at(adjList.at((20*y)+x).edgeList.at(i).dest).piece!=player&& adjList.at(adjList.at((20*y)+x).edgeList.at(i).dest).piece!=0)
	//		list.push_back(adjList.at(20*y+x).edgeList.at(i).dest);//adjList.at(adjList.at((20*y)+x).edgeList.at(i).dest));

//	}
	//for(int i=0;i<list.size();i++){
	if(getPiece(x,y)==0)
	return false;
	if((y*20+x-19)>0&&(y*20+x+20)<400)
		if((adjList.at(y*20+x-19).piece==adjList.at(y*20+x+20).piece)&&adjList.at(y*20+x-19).piece!=0)
			if(adjList.at(y*20+x-19).piece!=adjList.at(y*20+x).piece)
			return true;
	if((y*20+x-20)>0&&(y*20+x+21)<400)
		if((adjList.at(y*20+x-20).piece==adjList.at(y*20+x+21).piece)&&adjList.at(y*20+x-20).piece!=0)
			if(adjList.at(y*20+x-20).piece!=adjList.at(y*20+x).piece)
			return true;
	if((y*20+x-1)>0&&(y*20+x+1)<400)
		if((adjList.at(y*20+x-1).piece==adjList.at(y*20+x+1).piece)&&adjList.at(y*20+x-1).piece!=0)
			if(adjList.at(y*20+x-1).piece!=adjList.at(y*20+x).piece)
			return true;
	//}

	return false;
}