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
	playerOneTurn = false;
		 board.resize(20);
	 for (int i = 0; i < 20; i++) {
		 board[i].resize(20);
	 }
	 assignPointers();
	 addPiece(10,10,1);
	 addPiece(11,10,2);


	
 }

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
					edit->northEast = &board[i-1][k-1];
					edit->northWest = &board[i][k-1];
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

bool GameBoard::inVise(int x, int y) {
	int numAdj = 0;
	GameNode* check = &board[x][y];
	//if (playerOneTurn) {
		if (check->northWest->pieceOn == 1)
			numAdj++;
		if (check->northEast->pieceOn == 1)
			numAdj++;
		if (check->east->pieceOn == 1)
			numAdj++;
		if (check->west->pieceOn == 1)
			numAdj++;
		if (check->southEast->pieceOn == 1)
			numAdj++;
		if (check->southWest->pieceOn == 1)
			numAdj++;
		std::cout<<"Nums Around" << numAdj<<std::endl;
		return numAdj >= 2;
	/*} else {
		if (check->pieceOn != -1)
			return false;
		if (check->northWest->pieceOn == 2)
			return false;
		if (check->northEast->pieceOn == 2)
			return false;
		if (check->east->pieceOn == 2)
			return false;
		if (check->west->pieceOn == 2)
			return false;
		if (check->southEast->pieceOn == 2)
			return false;
		if (check->southWest->pieceOn == 2)
			return false;
		if (check->northWest->pieceOn == 1)
			return true;
		if (check->northEast->pieceOn == 1)
			return true;
		if (check->east->pieceOn == 1)
			return true;
		if (check->west->pieceOn == 1)
			return true;
		if (check->southEast->pieceOn == 1)
			return true;
		if (check->southWest->pieceOn == 1)
			return true;
		return false;*/
	//}


}

void GameBoard::addPiece(int row, int column,int player) {
	GameNode* toAdd = &board[row][column];
	toAdd->pieceOn = player;
	playerOneTurn = !playerOneTurn;
	std::cout<<"Vise Status" << inVise(row,column)<<std::endl;
	return;
}

int GameBoard::getPiece(int row, int column) {
	GameNode get = board[row][column];
	return get.pieceOn;
}

bool GameBoard::isAdjacent(int x,int y) {
	if(isPlayerOneConnected(x,y) || isPlayerTwoConnected(x,y))
		return true;
	else
		return false;
}

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

int GameBoard::dijkstraTotal(int x, int y) {
	int count = 0;
	int* visited = new int[10];
	GameNode* check = &board[x][y];
	return dijkstraRecursive(check,visited,0);


}

int GameBoard::dijkstraRecursive(GameNode* cur, int* visited, int arrSize) {
	int curCount = 0;
	if (cur->pieceOn == -1)
		return 0;
	for (int i = 0; i < 10; i++) {
		if (cur->numIdentifier == visited[i])
			return 0;
	}
	visited[arrSize] = cur->numIdentifier;
	arrSize++;
	curCount++;
	
	curCount = curCount + dijkstraRecursive(cur->west,visited,arrSize);
	curCount = curCount + dijkstraRecursive(cur->east,visited,arrSize);
	curCount = curCount + dijkstraRecursive(cur->northEast,visited,arrSize);
	curCount = curCount + dijkstraRecursive(cur->northWest,visited,arrSize);
	curCount = curCount + dijkstraRecursive(cur->southEast,visited,arrSize);
	curCount = curCount + dijkstraRecursive(cur->southWest,visited,arrSize);

	return curCount;
	
	

}

bool GameBoard::isPlayerOneConnected(int x, int y) {
	GameNode* check = &board[x][y];
		if (check->northWest->pieceOn == 2)
			return true;
		if (check->northEast->pieceOn == 2)
			return true;
		if (check->east->pieceOn == 2)
			return true;
		if (check->west->pieceOn == 2)
			return true;
		if (check->southEast->pieceOn == 2)
			return true;
		if (check->southWest->pieceOn == 2)
			return true;
		return false;
}

bool GameBoard::isPlayerTwoConnected(int x, int y) {
	GameNode* check = &board[x][y];
		if (check->northWest->pieceOn == 1)
			return true;
		if (check->northEast->pieceOn == 1)
			return true;
		if (check->east->pieceOn == 1)
			return true;
		if (check->west->pieceOn == 1)
			return true;
		if (check->southEast->pieceOn == 1)
			return true;
		if (check->southWest->pieceOn == 1)
			return true;
		return false;
}


bool GameBoard::moveOld(int x, int y) {
	GameNode* checking = &board[x][y];
	checking->curLookAt = true;
	//if (playerOneTurn) {

		if(checking->pieceOn != -1) {
			checking->curLookAt = false;
			return false;
		}
		if(checking->east->pieceOn == PLAYER_ONE_PIECE || checking->east->pieceOn == PLAYER_TWO_PIECE ) {
			if (checking->east->east->pieceOn == -1 && checking->east->east->curLookAt == true) {
				checking->curLookAt = false;
				return true;
			}
		}
		if(checking->northEast->pieceOn == PLAYER_ONE_PIECE || checking->northEast->pieceOn == PLAYER_TWO_PIECE ) {
			if (checking->northEast->northEast->pieceOn == -1 && checking->northEast->northEast->curLookAt == true) {
				checking->curLookAt = false;
				return true;
			}
		}
		if(checking->northWest->pieceOn == PLAYER_ONE_PIECE || checking->northWest->pieceOn == PLAYER_TWO_PIECE) {
			if (checking->northWest->northWest->pieceOn == -1 && checking->northWest->northWest->curLookAt == true) {
				checking->curLookAt = false;
				return true;
			}
		}
		if(checking->west->pieceOn == PLAYER_ONE_PIECE || checking->west->pieceOn == PLAYER_TWO_PIECE) {
			if (checking->west->west->pieceOn == -1 && checking->west->west->curLookAt == true) {
				checking->curLookAt = false;
				return true;
			}
		}
		if(checking->southEast->pieceOn == PLAYER_ONE_PIECE || checking->southEast->pieceOn == PLAYER_TWO_PIECE) {
			if (checking->southEast->southEast->pieceOn == -1 && checking->southEast->southEast->curLookAt == true) {
				checking->curLookAt = false;
				return true;
			}
		}
		if(checking->southWest->pieceOn == PLAYER_ONE_PIECE || checking->southWest->pieceOn == PLAYER_TWO_PIECE) {
			if (checking->southWest->southWest->pieceOn == -1 && checking->southWest->southWest->curLookAt == true) {
				checking->curLookAt = false;
				return true;
			}
		}
		checking->curLookAt = false;
		return false;
}
	/*} else {
		if(checking->pieceOn != -1)
			return false;
		if(checking->east->pieceOn != -1) {
			if (checking->east->east->pieceOn == -1)
				return true;
		}
		if(checking->northEast->pieceOn != -1) {
			if (checking->northEast->northEast->pieceOn == -1)
				return true;
		}
		if(checking->northWest->pieceOn != -1) {
			if (checking->northWest->northWest->pieceOn == -1)
				return true;
		}
		if(checking->west->pieceOn != -1) {
			if (checking->west->west->pieceOn == -1)
				return true;
		}
		if(checking->southEast->pieceOn != -1) {
			if (checking->southEast->southEast->pieceOn == -1)
				return true;
		}
		if(checking->southWest->pieceOn != -1) {
			if (checking->southWest->southWest->pieceOn == -1)
				return true;
		}
		if (isPlayerTwoConnected(x,y))
			return true;
		checking->curLookAt = false;
		return false;


	}
	return false;*/

bool GameBoard::dijkstraMove(int x, int y) {
	//Arr size 18
	int* looked = new int[18];
	int arrSize = 0;
	int moveSize = 2;
	return true;

}

bool GameBoard::dijkstraMoveRecursive (GameNode* cur, int* visited, int arrSize, int movesLeft) {
	return false;


}

bool GameBoard::canMove(int x, int y) {
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


bool GameBoard::canMoveOld(int x, int y){
    if (!playerOneTurn) {
		if (isPlayerOneConnected(x,y) && isContigious())
			return true;
		else
			return false;
	} else {
		if(isPlayerTwoConnected(x,y)&&isContigious())
			return true;
		else
			return false;
	}
    
}
