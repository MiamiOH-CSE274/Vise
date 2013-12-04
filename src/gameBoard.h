#include <vector>

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
};
