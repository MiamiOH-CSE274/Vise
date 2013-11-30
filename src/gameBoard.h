/*****
 * Author   : brinkmwj
 * Date     : 2009-11-06
 * Sources  : All code is original
 * 
 * This class uses the adjacency list representation of boards, but 
 * using vector for both the main array and for the actual adjacency "lists"
 */


#include <vector>


//The move class has only a cost and a destination.
class possibleMove{
public:
  possibleMove(int d){dest = d;};
  possibleMove(){dest = -1;};


  int dest; //Destination node number
};


//A board is just a list of nodes, where each node is responsible
// for keeping a list of the moves adjacent to itself.
class gameBoard{
public:
  //You will need to resize the hexList before you can use it
  gameBoard(unsigned int numVertices);


  //Add an move from node1 to node2, and from node2 to node1, with
  // the given cost. If the cost is < 0, throw a string exception.
  // If the move already exists, just update the cost
  void addMove(int node1, int node2, double cost);


  //Remove the move from node1 to node2, and also from node2 to node1.
  // If there are no such moves, then don't do anything.
  void removeMove(int node1, int node2);


public:
  std::vector<hexSpace*> hexList;        
};


class hexSpace{
public:
        int type;
        hexSpace* right;
        hexSpace* left;
        hexSpace* upright;
        hexSpace* upleft;
        hexSpace* downright;
        hexSpace* downleft;
        std::vector<possibleMove>moveList;
};

