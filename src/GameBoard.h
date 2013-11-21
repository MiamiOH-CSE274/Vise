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
		int pieceOn;
		bool canMove;
		GameNode() {pieceOn = -1; canMove = false;};
		int getPieceOn(int row, int column);

	};

public:   
	std::vector<std::vector<GameNode>> board;
	void addPiece(int row, int column, int player);
	void removePiece();
	int getPiece(int row, int column);
	void makeGameBoard();
	bool GameBoard::canMove(int row, int column);
	void checkNbrs(int x, int y,int& okayNbrs,int& badNbrs);

private:
	void assignPointers();
	bool playerOneTurn;

	

	





};


