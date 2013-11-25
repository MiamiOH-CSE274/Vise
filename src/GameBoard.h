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
	bool GameBoard::inVise(int x, int y);
	bool GameBoard::isContigious();
	bool GameBoard::isAdjacent(int x,int y);
	bool GameBoard::isPlayerOneConnected(int x, int y);
	bool GameBoard::isPlayerTwoConnected(int x, int y);
	int GameBoard::dijkstraRecursive(GameNode* cur, int* visited, int arrSize);

private:
	void assignPointers();
	bool playerOneTurn;
	int GameBoard::dijkstraTotal(int x, int y);
	

	

	





};


