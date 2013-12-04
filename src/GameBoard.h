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
		bool checked;
		GameNode() {pieceOn = -1; checked = false; inVise=false;};
		int getPieceOn(int row, int column);
        
	};
    
public:
    int numPieces;
	std::vector<std::vector<GameNode> > board;
    
	int getPiece(int row, int column);
	int dijkstraRecursive(GameNode* cur, int* visited, int& arrSize);
	int getP1Spares();
    int getP2Spares();
	int countPieces (int playerCheckingFor);
    
	bool canMove(int row, int column);
	bool inVise(int x, int y);
	bool isContigious();
	bool isAdjacent(int x,int y);
	bool isPlayerOneConnected(int x, int y);
	bool isPlayerTwoConnected(int x, int y);
	bool canMoveOld(int row, int column);
	bool jump(int x, int y);
	bool isAdjTo(int x1, int y1, int x2, int y2);
	bool wouldBeCont(int x, int y);
	bool isMove (int playerCheckingFor);
    bool playerStillInGame(int player);
	bool getPlayerOneTurn();
    
	void addPiece(int row, int column, int player);
	void removePiece();
	void makeGameBoard();
	void resetVise();
	void setPieceToMove(int x, int y);
	void removePiece(int x, int y);
	void removeVises();
    void returnDisconnectedPieces();
    void setP1Spares(int num);
    void setP2Spares(int num);
	void setPlayerOneTurn(bool turn);
    
private:
	int oldPieceToMoveX;
	int oldPieceToMoveY;
    
	GameNode* oldPieceToMove;
    
    int p1Spares;
	int p2Spares;
    
	bool playerOneTurn;
    
	bool p1InGroup (GameNode* cur, int* visited, int& arrSize);
    bool p2InGroup (GameNode* cur, int* visited, int& arrSize);
	bool dijkstraMove(int x, int y);
    
	int dijkstraTotal(int x, int y);
	int pieceCount(GameNode* cur, int* visited, int& arrSize, int player);
    
	void assignPointers();
	void dijkstraRecursiveReturn (GameNode* cur, int* visited, int& arrSize);
    
    
    
	
    
    
    
    
    
};
