/*****
 * Author   : brinkmwj
 * Date     : 2009-11-06
 * Sources  : All code is original
 * 
 * This class uses the adjacency list representation of boards, but 
 * using vector for both the main array and for the actual adjacency "lists"
 */

<<<<<<< HEAD
#include <vector>

=======

#include <vector>


>>>>>>> 06038faed0461eb65471033a31040843ed01f523
//The move class has only a cost and a destination.
class possibleMove{
public:
  possibleMove(int d){dest = d;};
  possibleMove(){dest = -1;};

<<<<<<< HEAD
  int dest; //Destination node number
};

class hexSpace{
public:
	hexSpace(){type=0;};
	int type;
	hexSpace* right;
	hexSpace* left;
	hexSpace* upright;
	hexSpace* upleft;
	hexSpace* downright;
	hexSpace* downleft;
	std::vector<possibleMove>moveList;
};
=======

  int dest; //Destination node number
};


class hexSpace{
public:
        hexSpace(){type=0;};
        int type;
        hexSpace* right;
        hexSpace* left;
        hexSpace* upright;
        hexSpace* upleft;
        hexSpace* downright;
        hexSpace* downleft;
        std::vector<possibleMove>moveList;
};



>>>>>>> 06038faed0461eb65471033a31040843ed01f523
