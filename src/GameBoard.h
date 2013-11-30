#include <vector>

class GameBoard {
public:
	GameBoard ();

	class GameNode {
	public:
		GameNode* east;
		GameNode* west;
		GameNode* northEast;
		GameNode* northWest;
		GameNode* southEast;
		GameNode* southWest;
		int numIdentifier;
		bool inVise;
		bool curLookAt;
		int pieceOn;
		bool canMove;
		GameNode() {pieceOn = -1; canMove = false;};
		int getPieceOn(int row, int column);

	};

public:   
	std::vector<std::vector<GameNode> > board;
	void addPiece(int row, int column, int player);
	void removePiece();
	int getPiece(int row, int column);
	void makeGameBoard();
	bool canMove(int row, int column);
	void checkNbrs(int x, int y,int& okayNbrs,int& badNbrs);
	bool inVise(int x, int y);
	void resetVise();
	bool isContigious();
	bool isAdjacent(int x,int y);
	bool isPlayerOneConnected(int x, int y);
	bool isPlayerTwoConnected(int x, int y);
	int dijkstraRecursive(GameNode* cur, int* visited, int arrSize);
    bool canMoveOld(int row, int column);
	void setPieceToMove(int x, int y);
	bool jump(int x, int y);
	bool isAdjTo(int x1, int y1, int x2, int y2);
	bool wouldBeCont(int x, int y);
	void removePiece(int x, int y);
	void removeVises();
    void returnDisconnectedPieces();
    void setP1Spares(int num);
    void setP2Spares(int num);
    int getP1Spares();
    int getP2Spares();
    bool getPlayerOneTurn();
    void setPlayerOneTurn(bool turn);


private:
	void assignPointers();
	bool playerOneTurn;
	int dijkstraTotal(int x, int y);
	bool dijkstraMove(int x, int y);
	int oldPieceToMoveX;
	int oldPieceToMoveY;
	bool dijkstraMoveRecursive (GameNode* cur, int* visited, int arrSize, int movesLeft);
	GameNode* oldPieceToMove;
    int p1Spares, p2Spares;
	void dijkstraRecursiveReturn (GameNode* cur, int* visited, int arrSize);
    bool p1InGroup (GameNode* cur, int* visited, int arrSize);
    bool p2InGroup (GameNode* cur, int* visited, int arrSize);
    int pieceCount(GameNode* cur, int* visited, int arrSize, int player);
    //int dijkstraRecursiveForWBC(GameNode* cur, int* visited, int arrSize);

	





};


