#include <vector>


//The move class has only a cost and a destination.
class possibleMove{
public:
  possibleMove(int d){dest = d;};
  possibleMove(){dest = -1;};


  int dest; //Destination node number
};


class hexSpace{
public:
        hexSpace(){type=0; checked=0;};
        int type;
		int checked;
        hexSpace* right;
        hexSpace* left;
        hexSpace* upright;
        hexSpace* upleft;
        hexSpace* downright;
        hexSpace* downleft;
        std::vector<possibleMove>moveList;
};
