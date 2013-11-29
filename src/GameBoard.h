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
	bool isContigious();
	bool isAdjacent(int x,int y);
	bool isPlayerOneConnected(int x, int y);
	bool isPlayerTwoConnected(int x, int y);
	int dijkstraRecursive(GameNode* cur, int* visited, int arrSize);
    bool canMoveOld(int row, int column);
	void setPieceToMove(int x, int y);
	bool GameBoard::moveOld(int x, int y);
	bool GameBoard::isAdjTo(int x1, int y1, int x2, int y2);
	int GameBoard::wouldBeCont(int x, int y);


private:
	void assignPointers();
	bool playerOneTurn;
	int dijkstraTotal(int x, int y);
	bool dijkstraMove(int x, int y);
	int oldPieceToMoveX;
	int oldPieceToMoveY;
	bool dijkstraMoveRecursive (GameNode* cur, int* visited, int arrSize, int movesLeft);
	GameNode* oldPieceToMove;
	

	





};


