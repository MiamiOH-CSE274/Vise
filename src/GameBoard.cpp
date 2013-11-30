#include "GameBoard.h"
#include <vector>
#include <iostream>

#define NO_PLAYER_PIECE -1
#define PLAYER_ONE_PIECE  1
#define PLAYER_TWO_PIECE  2

//Okay, you can actually commit this.

GameBoard::GameBoard() {
    
}

void GameBoard::makeGameBoard() {
	playerOneTurn = true;
    board.resize(20);
    for (int i = 0; i < 20; i++) {
        board[i].resize(20);
    }
    assignPointers();
    addPiece(10,10,1);
    addPiece(11,10,2);
    p1Spares = 4;
    p2Spares = 4;
    
    
	
}

void GameBoard::setPlayerOneTurn(bool turn){
    playerOneTurn = turn;
}

bool GameBoard::getPlayerOneTurn(){
    return playerOneTurn;
}

void GameBoard::setP1Spares(int num){
    p1Spares = num;
}

int GameBoard::getP1Spares(){
    return p1Spares;
}

void GameBoard::setP2Spares(int num){
    p2Spares = num;
}

int GameBoard::getP2Spares(){
    return p2Spares;
}

/*Assigns pointers, there are problems on the side base Cases,
 but right now I'm not too woried about it. If you spot any weird things
 with pointers, the problem is in here.
 */
void GameBoard::assignPointers() {
	/*NOTE TO SELF
     Ues X and Y coordinates instead of row and column*/
    
    //TODO:
    //	Fix i == 0 pointers and i== 19 for odd and even rows
    //	Fix k ==0 && k == 19 pointers for opposite reason
    //	Double check all pointers
	int idNum = 0;
	for (int k = 0; k < 20; k++) {
		for (int i = 0; i < 20; i++) {
			if (i != 0 && i != 19 &&  k != 0 && k!= 19) {
				GameNode* edit = &board[i][k];
				
				if (k%2 == 0) {
					edit->numIdentifier = idNum;
					edit->east = &board[i+1][k];
					edit->west = &board[i-1][k];
					edit->northEast = &board[i][k-1];
					edit->northWest = &board[i-1][k-1];
					edit->southEast = &board[i][k+1];
					edit->southWest = &board[i-1][k+1];
					idNum++;
					
				} else {
					edit->numIdentifier = idNum;
					edit->east = &board[i+1][k];
					edit->west = &board[i-1][k];
					edit->northEast = &board[i+1][k-1];
					edit->northWest = &board[i][k-1];
					edit->southEast = &board[i+1][k+1];
					edit->southWest = &board[i][k+1];
					idNum++;
                    
				}
				
			} else if (i == 0 && k == 0) {
                GameNode* edit = &board[i][k];
                edit->numIdentifier = idNum;
                edit->east = &board[1][0];
                edit->west = &board[19][0];
                edit->northEast = &board[1][19];
                edit->northWest = &board[19][19];
                edit->southEast = &board[1][1];
                edit->southWest = &board[1][0];
                idNum++;
                
			} else if (i == 0 && k == 19) {
				GameNode* edit = &board[i][k];
				edit->numIdentifier = idNum;
                edit->east = &board[1][19];
                edit->west = &board[19][19];
                edit->northEast = &board[0][18];
                edit->northWest = &board[19][18];
                edit->southEast = &board[0][1];
                edit->southWest = &board[0][0];
                idNum++;
                
			} else if (i == 19 && k == 0) {
				GameNode* edit = &board[i][k];
				edit->numIdentifier = idNum;
                edit->east = &board[0][0];
                edit->west = &board[18][0];
                edit->northEast = &board[19][0];
                edit->northWest = &board[18][19];
                edit->southEast = &board[0][1];
                edit->southWest = &board[0][19];
                idNum++;
                
			} else if (i == 19 && k == 19) {
				GameNode* edit = &board[i][k];
				edit->numIdentifier = idNum;
                edit->east = &board[19][0];
                edit->west = &board[19][18];
                edit->northEast = &board[18][0];
                edit->northWest = &board[19][19];
                edit->southEast = &board[19][1];
                edit->southWest = &board[18][1];
                idNum++;
                
			} else if (i == 0) {
				GameNode* edit = &board[i][k];
				edit->numIdentifier = idNum;
                edit->east = &board[i][k];
                edit->west = &board[i][k-1];
                edit->northEast = &board[i][19];
                edit->northWest = &board[i][19];
                edit->southEast = &board[i+1][1];
                edit->southWest = &board[i][1];
                idNum++;
                
			} else if (i == 19) {
                GameNode* edit = &board[i][k];
                edit->numIdentifier = idNum;
                edit->east = &board[19][k+1];
                edit->west = &board[19][k-1];
                edit->northEast = &board[18][k+1];
                edit->northWest = &board[18][k];
                edit->southEast = &board[0][k+1];
                edit->southWest = &board[0][k];
                idNum++;
                
			} else if (k == 0) {
				GameNode* edit = &board[i][k];
				edit->numIdentifier = idNum;
				edit->east = &board[i][1];
				edit->west = &board[i][19];
				if (i%2 == 0) {
					edit->northEast = &board[i-1][0];
					edit->northWest = &board[i-1][19];
					edit->southEast = &board[i+1][0];
					edit->southWest = &board[i+1][19];
					idNum++;
				} else {
					edit->northEast = &board[i-1][k+1];
					edit->northWest = &board[i-1][k];
					edit->southEast = &board[i+1][k+1];
					edit->southWest = &board[i+1][k];
					idNum++;
				}
                
			}else if (k == 19) {
				GameNode* edit = &board[i][k];
				edit->numIdentifier = idNum;
				edit->east = &board[i][0];
				edit->west = &board[i][18];
				if (i%2 == 0) {
					edit->northEast = &board[i-1][0];
					edit->northWest = &board[i-1][18];
					edit->southEast = &board[i+1][0];
					edit->southWest = &board[i+1][18];
					idNum++;
				} else {
					edit->northEast = &board[i-1][k];
					edit->northWest = &board[i-1][k-1];
					edit->southEast = &board[i+1][k];
					edit->southWest = &board[i+1][k-1];
					idNum++;
				}
                
			}
		}
	}
}

/*Counts the number of pieces around a specific piece. Is not necessarilly used much,
 this was when I was just going to follow Binkman's idears*/
void GameBoard::checkNbrs(int x, int y,int& okayNbrs,int& badNbrs) {
	GameNode* check = &board[x][y];
	int countGood = 0;
	if (check->east->pieceOn == true) {
		countGood++;
	}
	if (check->northEast->pieceOn == true) {
		countGood++;
	}
	if (check->northWest->pieceOn == true) {
		countGood++;
	}
	if (check->west->pieceOn == true) {
		countGood++;
	}
	if (check->southEast->pieceOn == true) {
		countGood++;
	}
	if (check->southWest->pieceOn == true) {
		countGood++;
	}
	okayNbrs = countGood;
	badNbrs = 6-countGood;
}

/*Fixes a quirk in inVise() where the boolean used to select which pieces are in a vise
 isn't reset to false, this fixes that*/
void GameBoard::resetVise() {
	GameNode* cur;
	for (int x= 0; x < 20; x++) {
		for (int y = 0; y < 20; y++) {
			cur = &board[x][y];
			cur->inVise = false;
            
		}
        
	}
    
}

void GameBoard::returnDisconnectedPieces(){
    int largestGroup = 0;
    int largestBlueGroup =0;
    int largestRedGroup=0;
    int bluesInCombined=0;
    int redsInCombined=0;
    bool foundBlue = false;
    bool foundRed = false;
    //Determine largest group of pieces...
    for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
            if (getPiece(i, j)!=-1){
                int numGroupedPieces =dijkstraTotal(i,j);
                if (numGroupedPieces>0){
                    //Reset the foundPiece booleans
                    foundRed = foundBlue = false;
                    GameNode* check = &board[i][j];
                    if (p1InGroup(check, new int[10], 0))
                        foundBlue = true;
                    if (p2InGroup(check, new int[10], 0))
                        foundRed = true;
                    
                    //Based on results of finding blue and red, store the
                    //size of the group in appropriate category.
                    if(numGroupedPieces>largestGroup && foundBlue && foundRed){
                        largestGroup = numGroupedPieces;
                        bluesInCombined = pieceCount(check, new int[10], 0, PLAYER_ONE_PIECE);
                        redsInCombined = pieceCount(check, new int[10], 0, PLAYER_TWO_PIECE);
                    }
                    
                    else if (foundBlue && !foundRed && numGroupedPieces>largestBlueGroup)
                        largestBlueGroup = numGroupedPieces;
                    else if (foundRed && !foundBlue && numGroupedPieces>largestRedGroup)
                        largestRedGroup = numGroupedPieces;
                }
            }
		}
	}
    //If we want to save a blue-only group
    if (largestGroup == 0 && !playerOneTurn) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (getPiece(i, j)!=-1){
                    int numGroupedPieces =dijkstraTotal(i,j);
                    if(numGroupedPieces!=largestBlueGroup){
                        int* visited = new int[10];
                        GameNode* check = &board[i][j];
                        dijkstraRecursiveReturn(check,visited,0);
                    }
                }
            }
        }

    }
    //Or, a red-only group
    else if (largestGroup == 0 && playerOneTurn) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (getPiece(i, j)!=-1){
                    int numGroupedPieces =dijkstraTotal(i,j);
                    if(numGroupedPieces!=largestRedGroup){
                        int* visited = new int[10];
                        GameNode* check = &board[i][j];
                        dijkstraRecursiveReturn(check,visited,0);
                    }
                }
            }
        }
    }
    
    //The normal case, a group with both red and blue
    else{
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (getPiece(i, j)!=-1){
                    int numGroupedPieces =dijkstraTotal(i,j);
                    if(numGroupedPieces!=largestGroup){
                        int* visited = new int[10];
                        GameNode* check = &board[i][j];
                        dijkstraRecursiveReturn(check,visited,0);
                    }
                    else if (numGroupedPieces==largestGroup &&
                             (bluesInCombined!=pieceCount(&board[i][j], new int[10], 0, PLAYER_ONE_PIECE)||
                              redsInCombined!=pieceCount(&board[i][j], new int[10], 0, PLAYER_TWO_PIECE))){
                                 dijkstraRecursiveReturn(&board[i][j],new int[10],0);
                             }
                        }
            }
        }
    }
    
    //Should only happen if we have two groups of same credentials
    while (!isContigious()) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (getPiece(i, j)!=-1){
                        int* visited = new int[10];
                        GameNode* check = &board[i][j];
                        dijkstraRecursiveReturn(check,visited,0);
                }
            }
        }

    }
}
/*Finds pieces in Vise, and sets a boolean value accordingly */
bool GameBoard::inVise(int x, int y) {
    bool isInVise = false;
	GameNode* check = &board[x][y];
	if (check->pieceOn == -1)
		return;
	if (check->pieceOn == PLAYER_ONE_PIECE) {
        if (check->west->pieceOn == PLAYER_TWO_PIECE && check -> east -> pieceOn == PLAYER_TWO_PIECE){
            check->inVise = true;
            isInVise=true;
        }
        if (check -> northEast -> pieceOn == PLAYER_TWO_PIECE && check->southWest -> pieceOn == PLAYER_TWO_PIECE){
            check->inVise = true;
            isInVise=true;
        }
        if (check -> northWest -> pieceOn == PLAYER_TWO_PIECE && check -> southEast -> pieceOn == PLAYER_TWO_PIECE){
            check->inVise = true;
            isInVise=true;
        }
	}
	if (check->pieceOn == PLAYER_TWO_PIECE) {
        if (check->west->pieceOn == PLAYER_ONE_PIECE && check -> east -> pieceOn == PLAYER_ONE_PIECE){
            check->inVise = true;
            isInVise=true;
        }
        if (check -> northEast -> pieceOn == PLAYER_ONE_PIECE && check->southWest -> pieceOn == PLAYER_ONE_PIECE){
            check->inVise = true;
            isInVise=true;
        }
        if (check -> northWest -> pieceOn == PLAYER_ONE_PIECE && check -> southEast -> pieceOn == PLAYER_ONE_PIECE){
            check->inVise = true;
            isInVise=true;
        }
	}
    
    return isInVise;
}

/*
 Adds piece. Herp derp.
 */
void GameBoard::addPiece(int row, int column,int player) {
	GameNode* toAdd = &board[row][column];
	toAdd->pieceOn = player;
	return;
}

/* Gets piece. Herp derp. */
int GameBoard::getPiece(int row, int column) {
	GameNode get = board[row][column];
	return get.pieceOn;
}

/*True if a piece is connected to some other piece, false if not */
bool GameBoard::isAdjacent(int x,int y) {
	if(isPlayerOneConnected(x,y) || isPlayerTwoConnected(x,y))
		return true;
	else
		return false;
}

/* Counts total pieces, then uses dijkstra's algorythm to count the
 the contigious pieces, if the numbers are different, then the board isn't
 contigious, and so it returns false. */
bool GameBoard::isContigious() {
	int totalPieces = 0;
    for (int x = 0; x < 20; x++) {
		for (int y = 0; y < 20; y++) {
			if (getPiece(x,y) != -1)
				totalPieces++;
		}
	}
	int contiguous = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if  (getPiece(i,j) != -1)  {
                contiguous = dijkstraTotal(i,j);
                if (contiguous == totalPieces)
                    return true;
                else
                    return false;
			}
		}
	}
    return false;
    
}

/*Starts Dijkstra's algorythm, to help organize things*/
int GameBoard::dijkstraTotal(int x, int y) {
	int count = 0;
	int* visited = new int[10];
	GameNode* check = &board[x][y];
	return dijkstraRecursive(check,visited,0);
    
    
}

/*Meat of finding if the board is contiguious.*/
int GameBoard::dijkstraRecursive(GameNode* cur, int* visited, int arrSize) {
	int curCount = 0;
	//If nothing is there, don't add anything
	if (cur->pieceOn == -1)
		return 0;
	
	//If already visited
	for (int i = 0; i < 10; i++) {
		if (cur->numIdentifier == visited[i])
			return 0;
	}
	//Hadn't visited, so add it to visited
	visited[arrSize] = cur->numIdentifier;
	arrSize++;
	curCount++;
	
	//Count in each direction
	curCount = curCount + dijkstraRecursive(cur->west,visited,arrSize);
	curCount = curCount + dijkstraRecursive(cur->east,visited,arrSize);
	curCount = curCount + dijkstraRecursive(cur->northEast,visited,arrSize);
	curCount = curCount + dijkstraRecursive(cur->northWest,visited,arrSize);
	curCount = curCount + dijkstraRecursive(cur->southEast,visited,arrSize);
	curCount = curCount + dijkstraRecursive(cur->southWest,visited,arrSize);
    
	return curCount;
	
	
    
}

int GameBoard::pieceCount(GameNode* cur, int* visited, int arrSize, int player){
    int curCount = 0;
	//If nothing is there, don't add anything
	if (cur->pieceOn == -1)
		return 0;
	
	//If already visited
	for (int i = 0; i < 10; i++) {
		if (cur->numIdentifier == visited[i])
			return 0;
	}
	//Hadn't visited, so add it to visited
	visited[arrSize] = cur->numIdentifier;
	arrSize++;
    if (cur->pieceOn==player) {
        curCount++;
    }
	
	//Count in each direction
	curCount = curCount + pieceCount(cur->west,visited,arrSize,player);
	curCount = curCount + pieceCount(cur->east,visited,arrSize,player);
	curCount = curCount + pieceCount(cur->northEast,visited,arrSize,player);
	curCount = curCount + pieceCount(cur->northWest,visited,arrSize,player);
	curCount = curCount + pieceCount(cur->southEast,visited,arrSize,player);
	curCount = curCount + pieceCount(cur->southWest,visited,arrSize,player);
    
	return curCount;
}

void GameBoard::dijkstraRecursiveReturn(GameNode *cur, int *visited, int arrSize){
	//If nothing is there, don't do anything
	if (cur->pieceOn == NO_PLAYER_PIECE)
		return;
    else{
        if (cur->pieceOn == PLAYER_ONE_PIECE) {
            p1Spares++;
            cur->pieceOn = NO_PLAYER_PIECE;
        }
        else{
            p2Spares++;
            cur->pieceOn = NO_PLAYER_PIECE;
        }
    }
	
	//If already visited
	for (int i = 0; i < 10; i++) {
		if (cur->numIdentifier == visited[i])
			return;
	}
	//Hadn't visited, so add it to visited
	visited[arrSize] = cur->numIdentifier;
	arrSize++;
	
	//Move in each direction
    dijkstraRecursiveReturn(cur->west,visited,arrSize);
    dijkstraRecursiveReturn(cur->east,visited,arrSize);
    dijkstraRecursiveReturn(cur->northEast,visited,arrSize);
    dijkstraRecursiveReturn(cur->northWest,visited,arrSize);
    dijkstraRecursiveReturn(cur->southEast,visited,arrSize);
    dijkstraRecursiveReturn(cur->southWest,visited,arrSize);
}

bool GameBoard::p1InGroup(GameBoard::GameNode *cur, int *visited, int arrSize){
   	//If already visited...so this would be a player2 space
    //bool visitedAlready = false;
	for (int i = 0; i < 10; i++) {
		if (cur->numIdentifier == visited[i])
			//visitedAlready = true;
            return false;
	}
    
    //If nothing is there, then no player1 was found on that route
	if (cur->pieceOn == NO_PLAYER_PIECE)
		return false;
    if (cur->pieceOn == PLAYER_ONE_PIECE)
        return true;
	

	//Hadn't visited, so add it to visited
	visited[arrSize] = cur->numIdentifier;
	arrSize++;
	
	//Move in each direction
    if (p1InGroup(cur->west,visited,arrSize)) return true;
    if (p1InGroup(cur->east,visited,arrSize)) return true;
    if (p1InGroup(cur->northEast,visited,arrSize)) return true;
    if (p1InGroup(cur->northWest,visited,arrSize)) return true;
    if (p1InGroup(cur->southEast,visited,arrSize)) return true;
    if (p1InGroup(cur->southWest,visited,arrSize)) return true;
    
    return false;
}

bool GameBoard::p2InGroup(GameBoard::GameNode *cur, int *visited, int arrSize){
   	//If already visited...so this would be a player2 space
    //bool visitedAlready = false;
	for (int i = 0; i < 10; i++) {
		if (cur->numIdentifier == visited[i])
			//visitedAlready = true;
            return false;
	}
    
    //If nothing is there, then no player1 was found on that route
	if (cur->pieceOn == NO_PLAYER_PIECE)
		return false;
    if (cur->pieceOn == PLAYER_TWO_PIECE)
        return true;
	
    
	//Hadn't visited, so add it to visited
	visited[arrSize] = cur->numIdentifier;
	arrSize++;
	
	//Move in each direction
    if (p2InGroup(cur->west,visited,arrSize)) return true;
    if (p2InGroup(cur->east,visited,arrSize)) return true;
    if (p2InGroup(cur->northEast,visited,arrSize)) return true;
    if (p2InGroup(cur->northWest,visited,arrSize)) return true;
    if (p2InGroup(cur->southEast,visited,arrSize)) return true;
    if (p2InGroup(cur->southWest,visited,arrSize)) return true;
    
    return false;
}

/*Checks if adjacent nodes are connected to any player one places*/
bool GameBoard::isPlayerOneConnected(int x, int y) {
	GameNode* check = &board[x][y];
    if (check->northWest->pieceOn == PLAYER_ONE_PIECE)
        return true;
    if (check->northEast->pieceOn == PLAYER_ONE_PIECE)
        return true;
    if (check->east->pieceOn == PLAYER_ONE_PIECE)
        return true;
    if (check->west->pieceOn == PLAYER_ONE_PIECE)
        return true;
    if (check->southEast->pieceOn == PLAYER_ONE_PIECE)
        return true;
    if (check->southWest->pieceOn == PLAYER_ONE_PIECE)
        return true;
    return false;
}

/*Checks if adjacent nodes are connected to any player two places*/
bool GameBoard::isPlayerTwoConnected(int x, int y) {
	GameNode* check = &board[x][y];
    if (check->northWest->pieceOn == PLAYER_TWO_PIECE)
        return true;
    if (check->northEast->pieceOn == PLAYER_TWO_PIECE)
        return true;
    if (check->east->pieceOn == PLAYER_TWO_PIECE)
        return true;
    if (check->west->pieceOn == PLAYER_TWO_PIECE)
        return true;
    if (check->southEast->pieceOn == PLAYER_TWO_PIECE)
        return true;
    if (check->southWest->pieceOn == PLAYER_TWO_PIECE)
        return true;
    return false;
}

/*Checks to see if a old piece can be moved*/
bool GameBoard::jump(int x, int y) {
	GameNode* checking = &board[x][y];
	checking->curLookAt = true;
    
    if(checking->pieceOn != -1) {
        checking->curLookAt = false;
        return false;
    }
    if(checking->east->pieceOn == PLAYER_ONE_PIECE || checking->east->pieceOn == PLAYER_TWO_PIECE ) {
        if (checking->east->east->pieceOn == -1 && checking->east->east == oldPieceToMove) {
            checking->curLookAt = false;
            return true;
        }
    }
    if(checking->northEast->pieceOn == PLAYER_ONE_PIECE || checking->northEast->pieceOn == PLAYER_TWO_PIECE ) {
        if (checking->northEast->northEast->pieceOn == -1 && checking->northEast->northEast == oldPieceToMove) {
            checking->curLookAt = false;
            return true;
        }
    }
    
    if(checking->northWest->pieceOn == PLAYER_ONE_PIECE || checking->northWest->pieceOn == PLAYER_TWO_PIECE) {
        if (checking->northWest->northWest->pieceOn == -1 && checking->northWest->northWest == oldPieceToMove) {
            checking->curLookAt = false;
            return true;
        }
    }
    if(checking->west->pieceOn == PLAYER_ONE_PIECE || checking->west->pieceOn == PLAYER_TWO_PIECE) {
        if (checking->west->west->pieceOn == -1 && checking->west->west == oldPieceToMove) {
            checking->curLookAt = false;
            return true;
        }
    }
    if(checking->southEast->pieceOn == PLAYER_ONE_PIECE || checking->southEast->pieceOn == PLAYER_TWO_PIECE) {
        if (checking->southEast->southEast->pieceOn == -1 && checking->southEast->southEast == oldPieceToMove) {
            checking->curLookAt = false;
            return true;
        }
    }
    if(checking->southWest->pieceOn == PLAYER_ONE_PIECE || checking->southWest->pieceOn == PLAYER_TWO_PIECE) {
        if (checking->southWest->southWest->pieceOn == -1 && checking->southWest->southWest == oldPieceToMove) {
            checking->curLookAt = false;
            return true;
        }
    }
    checking->curLookAt = false;
    return false;
    
}

/*Fragment incase I have implement dijkstra's somewhere else*/
bool GameBoard::dijkstraMove(int x, int y) {
	//Arr size 18
	int* looked = new int[18];
	int arrSize = 0;
	int moveSize = 2;
	return true;
    
}

/*Calculates where a new piece can be moved*/
bool GameBoard::canMove(int x, int y) {
	//return true;
	int pieceNum = getPiece(x,y);
	if (pieceNum == 1 || pieceNum == 0) {
		return false;
	}
	if (playerOneTurn) {
		if (isPlayerOneConnected(x,y) && !isPlayerTwoConnected(x,y))
			return true;
		else
			return false;
	} else {
		if(isPlayerTwoConnected(x,y)&&!isPlayerOneConnected(x,y))
			return true;
		else
			return false;
	}
}

/*Sets oldPieceToMove to aid in calculation of where old pieces can move*/
void GameBoard::setPieceToMove(int x, int y) {
	if (x == -1 && y == -1) {
		oldPieceToMove= NULL;
	} else {
        oldPieceToMoveX=x;
        oldPieceToMoveY=y;
        oldPieceToMove = &board[x][y];
	}
}

/*Checks to see if two pieces are adjacent to each other*/
bool GameBoard::isAdjTo(int x1, int y1, int x2, int y2) {
	GameNode* node1 = &board[x1][y1];
	GameNode* node2 = &board[x2][y2];
	if (node1->east == node2)
		return true;
	if (node1->west == node2)
		return true;
	if (node1->northEast == node2)
		return true;
	if (node1->northWest == node2)
		return true;
	if (node1->southEast == node2)
		return true;
	if (node1->southWest == node2)
		return true;
	return false;
}

/*Runs through the board and removes any piece that is caught in a vise*/
void GameBoard::removeVises() {
	GameNode* toCheck;
	for (int i = 0; i < 20; i++) {
		for (int y = 0; y < 20; y++) {
			toCheck = &board[i][y];
			if(toCheck->inVise == true)
				removePiece(i,y);
		}
	}
    
}

/*Resets a hex to have n o piece*/
void GameBoard::removePiece(int x, int y) {
	GameNode* piece = &board[x][y];
	piece->pieceOn = NO_PLAYER_PIECE;
}

/*Here is where I'm trying to figure out if a specific part WOULD be contigious or not if
 a piece is played there */
bool GameBoard::wouldBeCont(int x, int y) {
    
    int totalPieces = 0;
    for (int x = 0; x < 20; x++) {
		for (int y = 0; y < 20; y++) {
			if (getPiece(x,y) != -1)
				totalPieces++;
		}
	}
    
	int numConnectedIfPlacedThere = 0;
    //int* visited = new int[10];
	GameNode* check = &board[x][y];
	//if (playerOneTurn) {
    if (check->northWest->pieceOn != NO_PLAYER_PIECE)
        numConnectedIfPlacedThere += dijkstraRecursive(check->northWest, new int[10], 0);
    if (numConnectedIfPlacedThere==totalPieces) {
        return true;
    }
    if (check->northEast->pieceOn != NO_PLAYER_PIECE)
        numConnectedIfPlacedThere += dijkstraRecursive(check->northEast, new int[10], 0);
    if (numConnectedIfPlacedThere==totalPieces) {
        return true;
    }
    if (check->east->pieceOn != NO_PLAYER_PIECE)
        numConnectedIfPlacedThere += dijkstraRecursive(check->east, new int[10], 0);
    if (numConnectedIfPlacedThere==totalPieces) {
        return true;
    }
    if (check->west->pieceOn != NO_PLAYER_PIECE)
        numConnectedIfPlacedThere += dijkstraRecursive(check->west, new int[10], 0);
    if (numConnectedIfPlacedThere==totalPieces) {
        return true;
    }
    if (check->southEast->pieceOn != NO_PLAYER_PIECE)
        numConnectedIfPlacedThere += dijkstraRecursive(check->southEast, new int[10], 0);
    if (numConnectedIfPlacedThere==totalPieces) {
        return true;
    }
    if (check->southWest->pieceOn != NO_PLAYER_PIECE)
        numConnectedIfPlacedThere += dijkstraRecursive(check->southWest, new int[10], 0);
    if (numConnectedIfPlacedThere==totalPieces) {
        return true;
    }
    return false;
}


//Determines if you can move old pieces to a certain place. X,Y is the corrdinates of a hex, and this is called on every hex on the board.
bool GameBoard::canMoveOld(int x, int y){
	GameNode* moving = &board[x][y];
//	if (!isContigious()&&!wouldBeCont(x, y))
//		return false;
//    if (playerOneTurn) {
////		if ((isAdjTo(x,y,oldPieceToMoveX,oldPieceToMoveY) && isPlayerOneConnected(x,y)))
//        if (moveOld(x, y))
//			return true;
//		else
//			return false;
//	} else {
//		if(isAdjTo(x,y,oldPieceToMoveX,oldPieceToMoveY))
//			return true;
//		else
//			return false;
//	}
    
    //return ((isAdjTo(x, y, oldPieceToMoveX, oldPieceToMoveY)&&(isPlayerOneConnected(x, y)&&isPlayerTwoConnected(x, y)))||(jump(x, y)&&(isPlayerOneConnected(x, y)&&isPlayerTwoConnected(x, y))));
    return wouldBeCont(x, y) && (jump(x, y)||isAdjTo(x, y, oldPieceToMoveX, oldPieceToMoveY));
    
}

