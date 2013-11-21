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
	 addPiece(11,10,0);
	 addPiece(10,10,1);


	
 }

void GameBoard::assignPointers() {
	for (int i = 0; i < 20; i++) {
		for (int k = 0; k < 20; k++) {
			if (i != 0 && i != 19 &&  k != 0 && k!= 19) {
				GameNode* edit = &board[i][k];
				edit->east = &board[i][k+1];
				edit->west = &board[i][k-1];
				if (k%2 == 0) {
					edit->northEast = &board[i-1][k];
					edit->northWest = &board[i-1][k-1];
					edit->southEast = &board[i+1][k];
					edit->southWest = &board[i+1][k-1];
				} else {
					edit->northEast = &board[i-1][k+1];
					edit->northWest = &board[i-1][k];
					edit->southEast = &board[i+1][k+1];
					edit->southWest = &board[i+1][k];
				}
			/*} else if (i == 0 && k == 0) {
				GameNode* edit = &board[i][k];
				edit->south = &board[i+1][k];
				edit->north = &board[i-1][k];
				edit->northEast = &board[i][k+1];
				edit->northWest = &board[i][k-1];
				edit->southEast = &board[i+1][k+1];
				edit->southWest = &board[i+1][k-1];
				*/

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
	toAdd->east->canMove = true;
	toAdd->northEast->canMove = true;
	toAdd->northWest->canMove = true;
	toAdd->west->canMove = true;
	toAdd->southEast->canMove = true;
	toAdd->southWest->canMove = true;
	return;
}

int GameBoard::getPiece(int row, int column) {
	GameNode get = board[row][column];
	return get.pieceOn;
}

bool GameBoard::canMove(int row, int column) {
	GameNode* check = &board[row][column];
	return true;
	if (playerOneTurn) {
		GameNode* cur;
		cur = check->east;

		if (cur->pieceOn == 1)
			return false;
		/*if (check->northEast->pieceOn == 1)
			return false;
		if (check->northWest->pieceOn == 1)
			return false;
		if (check->south->pieceOn == 1)
			return false;
		if (check->southEast->pieceOn == 1)
			return false;
		if (check->southWest->pieceOn == 1)
			return false;

		if (check->north->pieceOn == 0 ||check->northEast->pieceOn == 0 
			|| check->northWest->pieceOn == 0 || check->south->pieceOn == 0 || 
			check->southEast->pieceOn == 0 || check->southWest->pieceOn == 0 )
			return true;
		else 
			return false;*/
	


	}
	return true;
}


