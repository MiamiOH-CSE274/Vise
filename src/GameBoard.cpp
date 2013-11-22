#include "GameBoard.h"
#include <vector>
#include <iostream>


GameBoard::GameBoard() {

}

void GameBoard::makeGameBoard() {
	playerOneTurn = true;
		 board.resize(20);
	 for (int i = 0; i < 20; i++) {
		 board[i].resize(20);
	 }
	 assignPointers();
	 addPiece(19,0,1);


	
 }

void GameBoard::assignPointers() {
	/*NOTE TO SELF:
	Ues X and Y coordinates instead of row and column*/

//TODO:
//	Fix i == 0 pointers and i== 19 for odd and even rows
//	Fix k ==0 && k == 19 pointers for opposite reason
//	Double check all pointers
	for (int k = 0; k < 20; k++) {
		for (int i = 0; i < 20; i++) {
			if (i != 0 && i != 19 &&  k != 0 && k!= 19) {
				GameNode* edit = &board[i][k];
				
				if (k%2 == 0) {
					edit->east = &board[i+1][k];
					edit->west = &board[i-1][k];
					edit->northEast = &board[i-1][k-1];
					edit->northWest = &board[i][k-1];
					edit->southEast = &board[i][k+1];
					edit->southWest = &board[i-1][k+1];
					
				} else {
					edit->east = &board[i+1][k];
					edit->west = &board[i-1][k];
					edit->northEast = &board[i+1][k-1];
					edit->northWest = &board[i][k-1];
					edit->southEast = &board[i+1][k+1];
					edit->southWest = &board[i][k+1];

				}
				
			} else if (i == 0 && k == 0) {
					GameNode* edit = &board[i][k];
					edit->east = &board[1][0];
					edit->west = &board[19][0];
					edit->northEast = &board[1][19];
					edit->northWest = &board[19][19];
					edit->southEast = &board[1][1]; 
					edit->southWest = &board[1][0];
					
			} else if (i == 0 && k == 19) {
				GameNode* edit = &board[i][k];
					edit->east = &board[1][19];
					edit->west = &board[19][19];
					edit->northEast = &board[0][18];
					edit->northWest = &board[19][18];
					edit->southEast = &board[0][1];
					edit->southWest = &board[0][0];
					
			} else if (i == 19 && k == 0) {
				GameNode* edit = &board[i][k];
					edit->east = &board[0][0];
					edit->west = &board[18][0];
					edit->northEast = &board[19][0];
					edit->northWest = &board[18][19];
					edit->southEast = &board[0][1];
					edit->southWest = &board[0][19];
					
			} else if (i == 19 && k == 19) {
				GameNode* edit = &board[i][k];
					edit->east = &board[19][0];
					edit->west = &board[19][18];
					edit->northEast = &board[18][0];
					edit->northWest = &board[19][19];
					edit->southEast = &board[19][1];
					edit->southWest = &board[18][1];
					
			} else if (i == 0) {
				GameNode* edit = &board[i][k];
					edit->east = &board[i][k];
					edit->west = &board[i][k-1];
					edit->northEast = &board[i][19];
					edit->northWest = &board[i][19];
					edit->southEast = &board[i+1][1];
					edit->southWest = &board[i][1];
					
			} else if (i == 19) {
				   GameNode* edit = &board[i][k];
					edit->east = &board[19][k+1];
					edit->west = &board[19][k-1];
					edit->northEast = &board[18][k+1];
					edit->northWest = &board[18][k];
					edit->southEast = &board[0][k+1];
					edit->southWest = &board[0][k];
					
			} else if (k == 0) {
				GameNode* edit = &board[i][k];
				edit->east = &board[i][1];
				edit->west = &board[i][19];
				if (i%2 == 0) {
					edit->northEast = &board[i-1][0];
					edit->northWest = &board[i-1][19];
					edit->southEast = &board[i+1][0];
					edit->southWest = &board[i+1][19];
					
				} else {
					edit->northEast = &board[i-1][k+1];
					edit->northWest = &board[i-1][k];
					edit->southEast = &board[i+1][k+1];
					edit->southWest = &board[i+1][k];
					
				}

			}else if (k == 19) {
				GameNode* edit = &board[i][k];
				edit->east = &board[i][0];
				edit->west = &board[i][18];
				if (i%2 == 0) {
					edit->northEast = &board[i-1][0];
					edit->northWest = &board[i-1][18];
					edit->southEast = &board[i+1][0];
					edit->southWest = &board[i+1][18];
				} else {
					edit->northEast = &board[i-1][k];
					edit->northWest = &board[i-1][k-1];
					edit->southEast = &board[i+1][k];
					edit->southWest = &board[i+1][k-1];
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



void GameBoard::addPiece(int row, int column,int player) {
	GameNode* toAdd = &board[row][column];
	toAdd->pieceOn = player;
	//toAdd->east->canMove = true;
	//toAdd->northEast->canMove = true;
	//toAdd->northWest->canMove = true;
	//toAdd->west->canMove = true;
	//toAdd->southEast->canMove = true;
	//toAdd->southWest->canMove = true;
	playerOneTurn = !playerOneTurn;
	return;
}

int GameBoard::getPiece(int row, int column) {
	GameNode get = board[row][column];
	return get.pieceOn;
}

bool GameBoard::canMove(int row, int column) {
	GameNode* check = &board[row][column];
	if (check->northWest->pieceOn == 1)
		return false;
	if (check->northEast->pieceOn == 1)
		return false;
	if (check->east->pieceOn == 1)
		return false;
	if (check->west->pieceOn == 1)
		return false;
	if (check->southEast->pieceOn == 1)
		return false;
	if (check->southWest->pieceOn == 1)
		return false;
	return true;
}


