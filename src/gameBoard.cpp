/*****
 * Author   : brinkmwj
 * Date     : 2009-11-06
 * Sources  : All code is original
 */
#include "gameBoard.h"

gameBoard::gameBoard(unsigned int numNodes){
  hexList.resize(numNodes);
}

//Add an move from node1 to node2, and from node2 to node1, with
// the given cost. If the cost is < 0, throw a string exception.
void gameBoard::addMove(int node1, int node2){
  possibleMove* toAdd = new possibleMove(node2);
  hexList[node1]->moveList.push_back(*toAdd);
}

//Remove the move from node1 to node2, and also from node2 to node1.
// If there are no such moves, then don't do anything.
void gameBoard::removeMove(int node1, int node2){
	for(int i = 0; i < hexList[node1]->moveList.size(); i++)
		if(hexList[node1]->moveList[i].dest==node2){
			hexList[node1]->moveList.erase(hexList[node1]->moveList.begin()+i);
		  break;
	  }
}
