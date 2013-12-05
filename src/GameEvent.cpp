#include "GameEvent.h"

GameEvent::GameEvent() {

	gameBoard = new Node*[400];

	for(int i = 0; i < 400; i++) {

		Node* newNode = new Node();
		newNode->index		 = i;
		newNode->player      = 0;
		newNode->topRight	 = nullptr;
		newNode->topLeft	 = nullptr;
		newNode->right		 = nullptr;
		newNode->left		 = nullptr;
		newNode->bottomRight = nullptr;
		newNode->bottomLeft  = nullptr;
		gameBoard[i]		 = newNode;

	}


	for(int i = 0; i < 400; i++) {

		//Set Up Corners
		if(i == 0) {
			gameBoard[i]->topRight    = gameBoard[380];
			gameBoard[i]->topLeft     = gameBoard[399];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i+19];
			gameBoard[i]->bottomRight = gameBoard[i+20];
			gameBoard[i]->bottomLeft  = gameBoard[i+39];
		}
		if(i == 19) {
			gameBoard[i]->topRight    = gameBoard[399];
			gameBoard[i]->topLeft     = gameBoard[399];
			gameBoard[i]->right       = gameBoard[i-19];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+20];
			gameBoard[i]->bottomLeft  = gameBoard[i+19];
		}
		if(i == 380) {
			gameBoard[i]->topRight    = gameBoard[i-19];
			gameBoard[i]->topLeft     = gameBoard[i-20];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[0];
			gameBoard[i]->bottomLeft  = gameBoard[1];
		}
		if(i == 399) {
			gameBoard[i]->topRight    = gameBoard[360];
			gameBoard[i]->topLeft     = gameBoard[379];
			gameBoard[i]->right       = gameBoard[380];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[19];
			gameBoard[i]->bottomLeft  = gameBoard[0];
		}
		//Set up Edge Rows
		if(i > 0 && i < 19) { 	
			gameBoard[i]->topRight    = gameBoard[i+380];
			gameBoard[i]->topLeft     = gameBoard[i+379];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+19];
			gameBoard[i]->bottomLeft  = gameBoard[i+20];
		}

		if(i > 380 && i < 399) {
			gameBoard[i]->topRight    = gameBoard[i-19];
			gameBoard[i]->topLeft     = gameBoard[i-20];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i-380];
			gameBoard[i]->bottomLeft  = gameBoard[i-379];
		}

		//Odd Rows
		if(i > 40 && i < 59) {
			gameBoard[i]->topRight    = gameBoard[i-20];
			gameBoard[i]->topLeft     = gameBoard[i-21];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+20];
			gameBoard[i]->bottomLeft  = gameBoard[i+19];
		}
		if(i > 80 && i < 99) {
			gameBoard[i]->topRight    = gameBoard[i-20];
			gameBoard[i]->topLeft     = gameBoard[i-21];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+20];
			gameBoard[i]->bottomLeft  = gameBoard[i+19];
		}
		if(i > 120 && i < 139) {
			gameBoard[i]->topRight    = gameBoard[i-20];
			gameBoard[i]->topLeft     = gameBoard[i-21];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+20];
			gameBoard[i]->bottomLeft  = gameBoard[i+19];
		}
		if(i > 160 && i < 179) {
			gameBoard[i]->topRight    = gameBoard[i-20];
			gameBoard[i]->topLeft     = gameBoard[i-21];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+20];
			gameBoard[i]->bottomLeft  = gameBoard[i+19];
		}
		if(i > 200 && i < 219) {
			gameBoard[i]->topRight    = gameBoard[i-20];
			gameBoard[i]->topLeft     = gameBoard[i-21];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+20];
			gameBoard[i]->bottomLeft  = gameBoard[i+19];
		}
		if(i > 240 && i < 259) {
			gameBoard[i]->topRight    = gameBoard[i-20];
			gameBoard[i]->topLeft     = gameBoard[i-21];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+20];
			gameBoard[i]->bottomLeft  = gameBoard[i+19];
		}
		if(i > 280 && i < 299) {
			gameBoard[i]->topRight    = gameBoard[i-20];
			gameBoard[i]->topLeft     = gameBoard[i-21];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+20];
			gameBoard[i]->bottomLeft  = gameBoard[i+19];
		}
		if(i > 320 && i < 339) {
			gameBoard[i]->topRight    = gameBoard[i-20];
			gameBoard[i]->topLeft     = gameBoard[i-21];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+20];
			gameBoard[i]->bottomLeft  = gameBoard[i+19];
		}
		if(i > 360 && i < 379) {
			gameBoard[i]->topRight    = gameBoard[i-20];
			gameBoard[i]->topLeft     = gameBoard[i-21];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+20];
			gameBoard[i]->bottomLeft  = gameBoard[i+19];
		}

		//Even Rows
		if(i > 20 && i < 39) {
			gameBoard[i]->topRight    = gameBoard[i-19];
			gameBoard[i]->topLeft     = gameBoard[i-20];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+21];
			gameBoard[i]->bottomLeft  = gameBoard[i+20];
		}
		if(i > 60 && i < 79) {
			gameBoard[i]->topRight    = gameBoard[i-19];
			gameBoard[i]->topLeft     = gameBoard[i-20];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+21];
			gameBoard[i]->bottomLeft  = gameBoard[i+20];
		}
		if(i > 100 && i < 119) {
			gameBoard[i]->topRight    = gameBoard[i-19];
			gameBoard[i]->topLeft     = gameBoard[i-20];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+21];
			gameBoard[i]->bottomLeft  = gameBoard[i+20];
		}
		if(i > 140 && i < 159) {
			gameBoard[i]->topRight    = gameBoard[i-19];
			gameBoard[i]->topLeft     = gameBoard[i-20];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+21];
			gameBoard[i]->bottomLeft  = gameBoard[i+20];
		}
		if(i > 180 && i < 199) {
			gameBoard[i]->topRight    = gameBoard[i-19];
			gameBoard[i]->topLeft     = gameBoard[i-20];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+21];
			gameBoard[i]->bottomLeft  = gameBoard[i+20];
		}
		if(i > 220 && i < 239) {
			gameBoard[i]->topRight    = gameBoard[i-19];
			gameBoard[i]->topLeft     = gameBoard[i-20];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+21];
			gameBoard[i]->bottomLeft  = gameBoard[i+20];
		}
		if(i > 260 && i < 279) {
			gameBoard[i]->topRight    = gameBoard[i-19];
			gameBoard[i]->topLeft     = gameBoard[i-20];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+21];
			gameBoard[i]->bottomLeft  = gameBoard[i+20];
		}
		if(i > 300 && i < 319) {
			gameBoard[i]->topRight    = gameBoard[i-19];
			gameBoard[i]->topLeft     = gameBoard[i-20];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+21];
			gameBoard[i]->bottomLeft  = gameBoard[i+20];
		}
		if(i > 340 && i < 359) {
			gameBoard[i]->topRight    = gameBoard[i-19];
			gameBoard[i]->topLeft     = gameBoard[i-20];
			gameBoard[i]->right       = gameBoard[i+1];
			gameBoard[i]->left        = gameBoard[i-1];
			gameBoard[i]->bottomRight = gameBoard[i+21];
			gameBoard[i]->bottomLeft  = gameBoard[i+20];
		}
	}

	//Set up Left Side Edge Nodes
	for(int i = 20; i < 341; i += 40) {
		gameBoard[i]->topRight    = gameBoard[i-19];
		gameBoard[i]->topLeft     = gameBoard[i-20];
		gameBoard[i]->right       = gameBoard[i+1];
		gameBoard[i]->left        = gameBoard[i+19];
		gameBoard[i]->bottomRight = gameBoard[i+21];
		gameBoard[i]->bottomLeft  = gameBoard[i+20];
	}

	for(int i = 40; i < 361; i += 40) {
		gameBoard[i]->topRight    = gameBoard[i-20];
		gameBoard[i]->topLeft     = gameBoard[i-1];
		gameBoard[i]->right       = gameBoard[i+1];
		gameBoard[i]->left        = gameBoard[i+19];
		gameBoard[i]->bottomRight = gameBoard[i+20];
		gameBoard[i]->bottomLeft  = gameBoard[i+39];
	}

	//Set up Right Side Edge Nodes
	for(int i = 39; i < 360; i += 40) {
		gameBoard[i]->topRight    = gameBoard[i-39];
		gameBoard[i]->topLeft     = gameBoard[i-20];
		gameBoard[i]->right       = gameBoard[i-19];
		gameBoard[i]->left        = gameBoard[i-1];
		gameBoard[i]->bottomRight = gameBoard[i+1];
		gameBoard[i]->bottomLeft  = gameBoard[i+20];
	}

	for(int i = 59; i < 380; i += 40) {
		gameBoard[i]->topRight    = gameBoard[i-20];
		gameBoard[i]->topLeft     = gameBoard[i-21];
		gameBoard[i]->right       = gameBoard[i-19];
		gameBoard[i]->left        = gameBoard[i-1];
		gameBoard[i]->bottomRight = gameBoard[i+20];
		gameBoard[i]->bottomLeft  = gameBoard[i+19];
	}
}
