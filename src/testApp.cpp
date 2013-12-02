#include "testApp.h"
#include "gameBoard.h"


#include <set>


//////////////////
/* Function declarations
 *
 * These are all functions that are defined and used in this file, so we don't 
 * need to put them in the .h file. You can ignore this: The comments about what
 * each function does is down in the body of the code.
 */
//Functions you might want to use, game logic
bool inVise(int x, int y);
void doVise(); //DO
void checkNbrs(int x, int y, int& okayNbrs, int& badNbrs);
bool canPlaceNewPiece(int x, int y);
bool isNeighboringSpace(int x, int y);
bool isJumpSpace(int x, int y);
bool isConnected(); // DO
bool canPlaceOldPiece(int x, int y); //FIx
int pieceAt(int x,int y);
void putPieceAt(int x, int y, int whichPiece);


//Drawing functions
void drawHex(float x, float y, float sideLen);
void drawboard();
void drawSpares();


//////////////////
/*
 * Model variables
 *
 * These are the variables that keep track of the game model:
 * the state of the board and the number of pieces
 */


//Width and heigh of the board, in hexes.
int boardW = 20;
int boardH = 20;


//TODO: Make any variables you need for representing your board here


std::vector<hexSpace*> board;
int numBlack;
int numWhite;
int bankBlack;
int bankWhite;
int countRW = 0;
int countRB = 0;
int countLW = 0;
int countLB = 0;


//Number of spare playing pieces left, for each player
int pl1spares=4;
int pl2spares=4;


//Valid values are 1 or 2, to indicate whose turn it is
int whoseTurn=1;


/*
 * What is the current player doing?
 *
 * 0: Doing nothing
 * 1: Holding a new piece to place
 * 2: Holding an existing piece to move
 */
int currentAction=0;


//The coordinates of the selected piece, if the player is moving an existing piece. This is in board coordinates, not screen coordinates.
int selectedPieceX=0;
int selectedPieceY=0;


/////////////////////
/*
 * State variables
 *
 * These keep track of the current state of the program, but only the parts
 * that are NOT part of the game model
 */
int currentFrame = 0;


//Time at the start of the program
float startTime;


/////////////////
/*
 * View variables
 *
 * Variables that are used for drawing, but are unrelated to the model and
 * program state
 */


//The upper-left corner of the board should be at this x,y position
float boardXOffset = 50;
float boardYOffset = 50;


//The side length of each hex, in pixels
float sideLen = 20.0;


//The width and height of a hex, in pixels. Notice that you shouldn't
// change these, just change sideLen
float hexW = sideLen*2.0*0.86602540378444;
float hexH = 1.5*sideLen;










//--------------------------------------------------------------
void testApp::setup(){
    //This is the *maximum* rate. Your program might go slower if your
    // updates or draws are too time conusming.
    ofSetFrameRate(60);
    
    //TODO: Initialize your "gameBoard" data structure here
        board.resize(400);
        numBlack = 4;
        numWhite = 4;
        bankBlack = 3;
        bankWhite = 3;


    //TODO: Put 1 piece for each player in the middle of hte gameBoard, side by side
        for(int i=0; i<400; i++)
                board[i] = new hexSpace();
        for(int i = 0; i < 400; i++){
                if(i<19 && i>0){
                                board[i]->upleft = board[i+379];
                                board[i]->upright = board[i+380];
                                board[i]->left = board[i-1];
                                board[i]->right = board[i+1];
                                board[i]->downleft = board[i+19];
                                board[i]->downright = board[i+20];
                }
                else if(i<399 && i>380){
                                board[i]->upleft = board[i-20];
                                board[i]->upright = board[i-19];
                                board[i]->left = board[i-1];
                                board[i]->right = board[i+1];
                                board[i]->downleft = board[i-380];
                                board[i]->downright = board[i-379];
                }
                else if(i%40==0 && i!=0){
                                board[i]->upleft = board[i-1];
                                board[i]->upright = board[i-20];
                                board[i]->left = board[i+19];
                                board[i]->right = board[i+1];
                                board[i]->downleft = board[i+39];
                                board[i]->downright = board[i+20];
                }
                else if((i+20)%40==0 && i!=380){
                                board[i]->upleft = board[i-20];
                                board[i]->upright = board[i-19];
                                board[i]->left = board[i+19];
                                board[i]->right = board[i+1];
                                board[i]->downleft = board[i+20];
                                board[i]->downright = board[i+21];
                }
                else if((i+1)%40==0 && i!=399){
                                board[i]->upleft = board[i-20];
                                board[i]->upright = board[i-39];
                                board[i]->left = board[i-1];
                                board[i]->right = board[i-19];
                                board[i]->downleft = board[i+20];
                                board[i]->downright = board[i+1];
                }
                else if((i+21)%40==0 && i!=19){
                                board[i]->upleft = board[i-21];
                                board[i]->upright = board[i-20];
                                board[i]->left = board[i-1];
                                board[i]->right = board[i-19];
                                board[i]->downleft = board[i+19];
                                board[i]->downright = board[i+20];
                }
                else if(i>380 && i<399){
                                board[i]->upleft = board[i-20];
                                board[i]->upright = board[i-19];
                                board[i]->left = board[i-1];
                                board[i]->right = board[i+1];
                                board[i]->downleft = board[i-380];
                                board[i]->downright = board[i-379];
                }
                else if((i>40 && i<59)||(i>80 && i<99)||(i>120 && i<139)||(i>160 && i<179)||(i>200 && i<219)||(i>240 && i<259)||(i>280 && i<299)||(i>320 && i<339)||(i>360 && i<379)){
                                board[i]->upleft = board[i-21];
                                board[i]->upright = board[i-20];
                                board[i]->left = board[i-1];
                                board[i]->right = board[i+1];
                                board[i]->downleft = board[i+19];
                                board[i]->downright = board[i+20];
                }
                else if (i!=0 && i!=19 && i!=380 && i!=399){
                                board[i]->upleft = board[i-20];
                                board[i]->upright = board[i-19];
                                board[i]->left = board[i-1];
                                board[i]->right = board[i+1];
                                board[i]->downleft = board[i+20];
                                board[i]->downright = board[i+21];
                }
        }
        board[0]->upleft = board[399];
        board[0]->upright = board[380];
        board[0]->left = board[19];
        board[0]->right = board[1];
        board[0]->downleft = board[39];
        board[0]->downright = board[20];


        board[19]->upleft = board[398];
        board[19]->upright = board[399];
        board[19]->left = board[18];
        board[19]->right = board[0];
        board[19]->downleft = board[38];
        board[19]->downright = board[39];


        board[380]->upleft = board[360];
        board[380]->upright = board[361];
        board[380]->left = board[399];
        board[380]->right = board[381];
        board[380]->downleft = board[0];
        board[380]->downright = board[1];


        board[399]->upleft = board[379];
        board[399]->upright = board[360];
        board[399]->left = board[398];
        board[399]->right = board[380];
        board[399]->downleft = board[19];
        board[399]->downright = board[0];


        board[209]->type=1;
        board[210]->type=2;


    startTime = ofGetElapsedTimef();
}


//Return true iff there is a piece in gameBoard space (x,y), and that piece
// is caught in a vise. Note that x and y are in gameBoard coordinates,
// not screen coordinates
bool inVise(int x, int y){
        int target = 20*y+x;
		if(((board[target]->left->type != board[target]->type) && (board[target]->right->type == board[target]->left->type) && (board[target]->right->type != 0)) ||
			((board[target]->upleft->type != board[target]->type) && (board[target]->downright->type == board[target]->upleft->type) && (board[target]->downright->type != 0)) ||
			((board[target]->downleft->type != board[target]->type) && (board[target]->upright->type == board[target]->downleft->type) && (board[target]->upright->type != 0)))
                return true;
        return false;
}


/*
 * This is the method that updates the gameBoard if a player is caught in a vise at the end of the turn.
 * You may want to break this method up into several sub-methods.
 *
 * 1) FIRST, identify all pieces that are caught in a vise Note: If you have 0101, then
 *    both the middle 1 and middle 0 are caught in the vice. Use the "inVise" method defined above.
 * 2) NEXT, delete them all from the game (in previous example, you would get 0__1)
 * 3) LAST, find the largest connected component that contains
 *    at least 1 piece from each player. Place all other pieces back in the
 *    storehouse (that is, update pl1spares and pl2spares). If there is a tie, pick the one that has the most pieces from the player
 *    that just played.
 * 3b) If no such component exists, then select the largest
 *    connected component that contains a piece of the player who played
 *    most recently.
 * 3c) If no such component exists, then select the largest connected component.
 * 3d) Tie-breaking: If there is a tie under any of these rules, pick arbitrarily
 */
void doVise(){
	// left is either upleft,left,or downleft
/*countLW = 0;
countLB = 0;
countRW = 0;
countRB = 0; */

	std::cout << "START" << std::endl;
	std::cout << countLB << " " << countLW << std::endl;
	std::cout << countRB << " " << countRW << std::endl;
	std::cout << "END" << std::endl;
	/*
	int numBlack;
	int numWhite;
	int bankBlack;
	int bankWhite;
	checked
	*/

	int inV = 0;
	int target = 0;
	int temp = 0;
	vector<int> toDelete;
	toDelete.resize(0);

	// if 1 upleft and downright
	// if 2 left and right
	// if 3 upright and downleft
	
	int typeOFVise = 0;
	 int visePos = 0;

	 // Do 1010 - array?
	
	// Find all pieces in the vise
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 20; j++){
			if (inVise(i,j)){
				target = 20*j+i;
				inV = board[20*j+i]->type;
				toDelete.push_back(target);
			}
		}
	}

	if(!toDelete.empty()){
		for(int i = 0; i != toDelete.size(); i++)
			board[toDelete[i]]->type=0;
		toDelete.clear();
	}

	if (target != 0)
	
	temp = target;
	visePos = target;
		
	// Vise is upleft and downright
	if (board[target]->upleft->type != inV && board[target]->downright->type != inV){

	}
	
	// Vise is left and right
	if (board[target]->left->type != inV && board[target]->right->type != inV){
	}
	
	// Vise is downleft and upright
	if (board[target]->downleft->type != inV && board[target]->upright->type != inV){
		typeOFVise = 3;
		//upright first
		bool circle = true;

		target = target - 20;
		int start = target;
		
			if (board[target]->type == 1 && board[target]->checked == 0){
				countRW++;
				board[target]->checked = 1;
			}
			else if (board[target]->type == 2 && board[target]->checked == 0) {
				countRB++;
				board[target]->checked = 1;
			}

		while (circle){
			
			//upright first countRB countRW
			if (board[target]->upright->type != 0 && board[target]->upright->checked == 0){
				target = target - 20;
				if (board[target]->upright->type == 1){
					countRW++;
					board[target]->upright->checked = 1;
				}
				else {
					countRB++;
					board[target]->upright->checked = 1;
				}

			}
			//right
			else if (board[target]->right->type != 0 && board[target]->right->checked == 0){
				target = target + 1;
				if (board[target]->right->type == 1){
					countRW++;
					board[target]->right->checked = 1;
				}
				else {
					countRB++;
					board[target]->right->checked = 1;
				}
			
			
			}
			//downright
			else if (board[target]->downright->type != 0 && board[target]->downright->checked == 0){
				target = target + 20;
				if (board[target]->downright->type == 1){
					countRW++;
					board[target]->downright->checked = 1;
				}
				else {
					countRB++;
					board[target]->downright->checked = 1;
				}
			
			
			}
			//downleft
			else if (board[target]->downleft->type != 0 && board[target]->downleft->checked == 0){
				target = target + 19;
				if (board[target]->downleft->type == 1){
					countRW++;
					board[target]->downleft->checked = 1;
				}
				else {
					countRB++;
					board[target]->downleft->checked = 1;
				}
			
			
			}
			//left
			else if (board[target]->left->type != 0 && board[target]->left->checked == 0){
				target = target - 1;
				if (board[target]->left->type == 1){
					countRW++;
					board[target]->left->checked = 1;
				}
				else {
					countRB++;
					board[target]->left->checked = 1;
				}
			
			
			}
			//upleft
			else if (board[target]->upleft->type != 0 && board[target]->upleft->checked == 0){
				target = target - 21;
				if (board[target]->upleft->type == 1){
				countRW++;
					board[target]->upleft->checked = 1;
				}
				else {
					countRB++;
					board[target]->upleft->checked = 1;
				}
			}
			else if (board[start]->upright->checked == 0 || board[start]->right->checked == 0 
				|| board[start]->downright->checked == 0 || board[start]->downleft->checked == 0
				|| board[start]->left->checked == 0 || board[start]->upleft->checked == 0){
				//(board[target]->left->type == 0 || board[target]->downleft->type == 0){
				target = start;

			}
			else {
				circle = false;
			}
		}

		//downleft second
		circle = true;
		
		target = temp + 20;
		int start2 = target;
		
			if (board[target]->type == 1){
				countLW++;
				board[target]->checked = 1;
			}
			else {
				countLB++;
				board[target]->checked = 1;
			}

		while (circle){
			
			//upright
			if (board[target]->upright->type != 0 && board[target]->upright->checked == 0){
				target = target - 20;
				if (board[target]->upright->type == 1){
					countLW++;
					board[target]->upright->checked = 1;
				}
				else {
					countLB++;
					board[target]->upright->checked = 1;
				}

			}
			//right
			else if (board[target]->right->type != 0 && board[target]->right->checked == 0){
				target = target + 1;
				if (board[target]->right->type == 1){
					countLW++;
					board[target]->right->checked = 1;
				}
				else {
					countLB++;
					board[target]->right->checked = 1;
				}
			
			
			}
			//downright
			else if (board[target]->downright->type != 0 && board[target]->downright->checked == 0){
				target = target + 20;
				if (board[target]->downright->type == 1){
					countLW++;
					board[target]->downright->checked = 1;
				}
				else {
					countLB++;
					board[target]->downright->checked = 1;
				}
			
			
			}
			//downleft
			else if (board[target]->downleft->type != 0 && board[target]->downleft->checked == 0){
				target = target + 19;
				if (board[target]->downleft->type == 1){
					countLW++;
					board[target]->downleft->checked = 1;
				}
				else {
					countLB++;
					board[target]->downleft->checked = 1;
				}
			
			
			}
			//left
			else if (board[target]->left->type != 0 && board[target]->left->checked == 0){
				target = target - 1;
				if (board[target]->left->type == 1){
					countLW++;
					board[target]->left->checked = 1;
				}
				else {
					countLB++;
					board[target]->left->checked = 1;
				}
			
			
			}
			//upleft
			else if (board[target]->upleft->type != 0 && board[target]->upleft->checked == 0){
				target = target - 21;
				if (board[target]->upleft->type == 1){
					countLW++;
					board[target]->upleft->checked = 1;
				}
				else {
					countLB++;
					board[target]->upleft->checked = 1;
				}
			}
			else if (board[start2]->upright->checked == 0 || board[start2]->right->checked == 0 
				|| board[start2]->downright->checked == 0 || board[start2]->downleft->checked == 0
				|| board[start2]->left->checked == 0 || board[start2]->upleft->checked == 0){
				target = start2;
			}
			else{
				circle = false;
			}
		}

	// Left bundle is smaller
	int removed = 0;
	
	std::cout << "HERE" << std::endl;
	std::cout << countLB << " " << countLW << std::endl;
	std::cout << countRB << " " << countRW << std::endl;
	

	if ((countLB + countLW) < (countRB + countRW)){
		std::cout << "ddd" << std::endl;
		if (typeOFVise == 3){
			
		//	while((countLB + countLW) > removed){
			std::cout << "in vise3" << std::endl;
				if (board[visePos]->downleft->type == 1){
					bankWhite++;
					board[visePos]->downleft->type = 0;
					removed++;
				}
				else if (board[visePos]->downleft->type == 2){
					bankBlack++;
					board[visePos]->downleft->type = 0;
					removed++;
				}
			//}
		}
	}
		
		
		
		
		/*
	int firstW = 0;
	int firstB = 0;
	int secW = 0;
	int secB = 0;
	int lastK = 0;
	int rowAbove = 0;
	int empty = 0;

	for (int d = 0; d < 400; d++){
		rowAbove = 0;
		empty = 0;
		for (int k = 0; k < 399; k++){
			if (board[k]->type != 0){
				if (board[k]->type == 1){
					firstW++;		
					rowAbove++;
				}
				else if (board[k]->type == 2){
					firstB++;
					rowAbove++;
				}
				// check neighbors
				lastK = k;
				k = k + 1;
			}
			empty = empty + 1;
			if (empty >= rowAbove)
				k = 400;

		}

		// Check down now
		rowAbove = 0;
		for (int f = lastK + 20; f < 400; f++){
		
			if (board[f]->type != 0){
				if (board[f]->type == 1){
					firstW++;		
					rowAbove++;
				}
				else if (board[f]->type == 2){
					firstB++;
					rowAbove++;
				}
				// check neighbors
				int lastF = f;
				f = f - 1;
				empty = 0;
			}
			f = f - 1;
			empty = empty + 1;
			if (empty >= rowAbove)
				f = 400;
		}

	}
	std::cout << firstW << std::endl;
	std::cout << firstB << std::endl;
	*/
			//	if (isConnected() == false){
				// Count left subtree
				// Vise is upleft and downright
				/*if (board[target]->upleft->type != inV && board[target]->downright->type != inV){
				}
				// Vise is left and right
				if (board[target]->left->type != inV && board[target]->right->type != inV){
				}
				// Vise is downleft and upright
				int temp = target;
				if (board[target]->downleft->type != inV && board[target]->upright->type != inV){
					if (board[target]->downleft->type == 1)
						countLW++;
					else if (board[target]->downleft->type == 2)
						countLB++;
					while (board[target]->downleft->right->type == 1 || board[target]->downleft->right->type == 2){
						if (board[target]->downleft->right->type == 1)
							countLW++;
						else if (board[target]->downleft->right->type == 2)
							countLB++;
						target = target + 1;
					}
					target = temp;
					while (board[target]->downleft->left->type == 1 || board[target]->downleft->left->type == 2){
						if (board[target]->downleft->left->type == 1)
							countLW++;
						else if (board[target]->downleft->left->type == 2)
							countLB++;
						target = target - 1;
					}
					target = temp;
					if (board[target]->left->type == 1)
						countLW++;
					else if (board[target]->left->type == 2)
						countLB++;
					
					target = temp;
					while (board[target]->left->left->type == 1 || board[target]->left->left->type == 2){
						if (board[target]->left->left->type == 1)
						countLW++;
						else if (board[target]->left->left->type == 2)
						countLB++;
						target = target - 1;
					}
					target = temp;
					if (board[target]->upleft->type == 1)
						countLW++;
					else if (board[target]->upleft->type == 2)
						countLB++;
					
					target = temp;
					while (board[target]->upleft->left->type == 1 || board[target]->upleft->left->type == 2){
						if (board[target]->upleft->left->type == 1)
						countLW++;
						else if (board[target]->upleft->left->type == 2)
						countLB++;
						target = target - 1;
					}
					target = temp;
					if (board[target]->downleft->downleft->type == 1)
						countLW++;
					else if (board[target]->downleft->downleft->type == 2)
						countLB++;
					
					target = temp;
					while (board[target]->downleft->downleft->right->type == 1 || board[target]->downleft->upright->right->type == 2){
						if (board[target]->downleft->downleft->right->type == 1)
						countLW++;
						else if (board[target]->downleft->downleft->right->type == 2)
						countLB++;
						target = target + 1;
					}
				
					target = temp;
					while (board[target]->downleft->downleft->left->type == 1 || board[target]->downleft->downleft->left->type == 2){
						if (board[target]->downleft->downleft->left->type == 1)
						countLW++;
						else if (board[target]->downleft->downleft->left->type == 2)
						countLB++;
						target = target - 1;
					}

					// Do upright side
					target = temp;
					if (board[target]->upright->type == 1)
						countRW++;
					else if (board[target]->upright->type == 2)
						countRB++;
					
					target = temp;
					while (board[target]->upright->right->type == 1 || board[target]->upright->right->type == 2){
						if (board[target]->upright->right->type == 1)
						countRW++;
						else if (board[target]->upright->right->type == 2)
						countRB++;
						target = target + 1;
					}
					target = temp;
					if (board[target]->right->type == 1)
						countRW++;
					else if (board[target]->right->type == 2)
						countRB++;
					
					target = temp;
					while (board[target]->right->right->type == 1 || board[target]->right->right->type == 2){
						if (board[target]->right->right->type == 1)
						countRW++;
						else if (board[target]->right->right->type == 2)
						countRB++;
						target = target + 1;
					}
					//dddd
					target = temp;
					if (board[target]->upright->upright->type == 1)
						countRW++;
					else if (board[target]->upright->upright->type == 2)
						countRB++;
					
					target = temp;
					while (board[target]->upright->upright->right->type == 1 || board[target]->upright->upright->right->type == 2){
						if (board[target]->upright->upright->right->type == 1)
						countRW++;
						else if (board[target]->upright->upright->right->type == 2)
						countRB++;
						target = target + 1;
					}
				
					target = temp;
					while (board[target]->upright->upright->left->type == 1 || board[target]->upright->upright->left->type == 2){
						if (board[target]->upright->upright->left->type == 1)
						countRW++;
						else if (board[target]->upright->upright->left->type == 2)
						countRB++;
						target = target + 1;
					}
				}

		if ((countRB+countRW) < (countLW+countLB)){
			//pl1spares = countRW;
			//pl2spares = countRB;

			bankBlack = bankBlack + countRB;
			bankWhite = bankWhite + countRW;
		}
		else if ((countRB+countRW) > (countLW+countLB)){
			//pl1spares = countRW;
			//pl2spares = countRB;

			bankBlack = bankBlack + countLB;
			bankWhite = bankWhite + countLW;
		}
		/*if (countRW+countRB < countLW+countLW){
		pl1spares = countRW;
		pl2spares = countRB;

		//pl1spares and pl2spares
		}*/
//		}
		
						// Find largest connected component
	/*			if ((board[20*j+i]->upleft->type != inVise) && (board[20*j+i]->downright->type != inVise)){
					countL++;
					countR++;

				}
				else if ((board[20*j+i]->left->type != inVise) && (board[20*j+i]->right->type != inVise)){
					countL++;
					countR++;
					if ((board[20*j+i]->left->upright->type == 1 || board[20*j+i]->left->upright->type == 1)){
						countL++;
						if ((board[20*j+i]->left->upright->right->type == 1 || board[20*j+i]->left->upright->right->type == 1)){
							countL++;
						if ((board[20*j+i]->left->upright->upright->type == 1 || board[20*j+i]->left->upright->upright->type == 1)){
							countL++;
						if ((board[20*j+i]->left->upright->upleft->type == 1 || board[20*j+i]->left->upright->upleft->type == 1)){
							countL++;
					}
					if ((board[20*j+i]->left->upleft->type == 1 || board[20*j+i]->left->upleft->type == 1)){
						countL++;
						if ((board[20*j+i]->left->upleft->upleft->type == 1 || board[20*j+i]->left->upleft->upleft->type == 1)){
							countL++;
						if ((board[20*j+i]->left->upleft->left->type == 1 || board[20*j+i]->left->upleft->left->type == 1)){
							countL++;
					}
					if ((board[20*j+i]->left->left->type == 1 || board[20*j+i]->left->left->type == 1)){
						countL++;
						if ((board[20*j+i]->left->left->left->type == 1 || board[20*j+i]->left->left->left->type == 1)){
							countL++;
						if ((board[20*j+i]->left->left->downleft->type == 1 || board[20*j+i]->left->left->downleft->type == 1)){
							countL++;
					}
					if ((board[20*j+i]->left->downleft->type == 1 || board[20*j+i]->left->downleft->type == 1)){
						countL++;
						if ((board[20*j+i]->left->downleft->downleft->type == 1 || board[20*j+i]->left->downleft->downleft->type == 1)){
							countL++;
						if ((board[20*j+i]->left->downleft->downright->type == 1 || board[20*j+i]->left->downleft->downright->type == 1)){
							countL++;
					}
					if ((board[20*j+i]->left->downright->type == 1 || board[20*j+i]->left->downright->type == 1)){
						countL++;
						if ((board[20*j+i]->left->downright->downright->type == 1 || board[20*j+i]->left->downright->downright->type == 1)){
							countL++;
						if ((board[20*j+i]->left->downright->right->type == 1 || board[20*j+i]->left->downright->right->type == 1)){
							countL++;
					}
						//do right

				}
				else if ((board[20*j+i]->downleft->type != inVise) && (board[20*j+i]->upright->type != inVise)){
					countL++;
					countR++;
				}
			}*/
		
		
	
	

	// Find largest connected component
    //TODO
		}
		
}


//--------------------------------------------------------------
void testApp::update(){
    //This can be helpful if you are doing animations
    currentFrame = (ofGetElapsedTimef() - startTime)/(1.0/60);
    
    //Check for vised pieces on every update
    doVise();
}


//Draw a single hexagon centered at (x,y).
// These are screen coordinates, not board coordinates.
void drawHex(float x, float y, float sideLen){
    //point 1 is sideLen up from the center
    ofPoint pTop(x,y-sideLen);
    ofPoint pBot(x,y+sideLen);
    ofPoint pRtTop(x+0.86602540378444*sideLen,y-0.5*sideLen);
    ofPoint pRtBot(x+0.86602540378444*sideLen,y+0.5*sideLen);
    ofPoint pLtTop(x-0.86602540378444*sideLen,y-0.5*sideLen);
    ofPoint pLtBot(x-0.86602540378444*sideLen,y+0.5*sideLen);
    
    ofSetLineWidth(1.0);
    ofLine(pTop,pRtTop);
    ofLine(pRtTop,pRtBot);
    ofLine(pRtBot, pBot);
    ofLine(pBot,pLtBot);
    ofLine(pLtBot,pLtTop);
    ofLine(pLtTop,pTop);
}




/*
 * x and y are the input parameters, which are in board coordinates
 * For a given space (x,y), check to see how many of the neighboring spaces
 * contain a piece of the current player (that is okayNbrs) and how many
 * contain a piece of the opposing player (that is badNbrs). This is useful
 * in determining if the current player can play a new piece in the hex
 * under consideration.
 */
void checkNbrs(int x, int y, int& okayNbrs, int& badNbrs){
    //TODO
        int target = 20*y+x;
        if(board[target]->upleft->type!=whoseTurn && board[target]->upleft->type!=0)
                badNbrs++;
        else if(board[target]->upleft->type!=0)
                okayNbrs++;


        if(board[target]->upright->type!=whoseTurn && board[target]->upright->type!=0)
                badNbrs++;
        else if(board[target]->upright->type!=0)
                okayNbrs++;


        if(board[target]->left->type!=whoseTurn && board[target]->left->type!=0)
                badNbrs++;
        else if(board[target]->left->type!=0)
                okayNbrs++;


        if(board[target]->right->type!=whoseTurn && board[target]->right->type!=0)
                badNbrs++;
        else if(board[target]->right->type!=0)
                okayNbrs++;


        if(board[target]->downleft->type!=whoseTurn && board[target]->downleft->type!=0)
                badNbrs++;
        else if(board[target]->downleft->type!=0)
                okayNbrs++;


        if(board[target]->downright->type!=whoseTurn && board[target]->downright->type!=0)
                badNbrs++;
        else if(board[target]->downright->type!=0)
                okayNbrs++;
}


/*
 * Return true iff the current player can place a new piece
 * in row y, column x, without violating the rules. That is,
 * at least 1 neighboring hex must contain one of the player's
 * pieces, and none of the neighboring hex can contain an
 * opposing player's piece
 */
bool canPlaceNewPiece(int x, int y){
    int okayNbrs=0;
    int badNbrs=0;
    checkNbrs(x,y,okayNbrs,badNbrs);
    return(okayNbrs > 0 && badNbrs == 0);
}


//Return true iff (x,y) is neighboring to (selectedPieceX,selectedPieceY)
//These inputs are in board coordinates, not screen coordinates
bool isNeighboringSpace(int x, int y){
    //TODO
        int selected = selectedPieceY*20+selectedPieceX;
        int target = 20*y+x;
        if((board[selected]->upleft == board[target]) ||
                (board[selected]->upright == board[target]) ||
                (board[selected]->left == board[target]) ||
                (board[selected]->right == board[target]) ||
                (board[selected]->downleft == board[target]) ||
                (board[selected]->downright == board[target]))
                return true;
        return false;
}


//Return true iff (x,y) is one jump to (selectedPieceX,selectedPieceY)
//These inputs are in board coordinates, not screen coordinates
bool isJumpSpace(int x, int y){
    //TODO
        int selected = selectedPieceY*20+selectedPieceX;
        int target = 20*y+x;
        if((board[selected]->upleft->upleft == board[target] && board[selected]->upleft->type !=0) ||
                (board[selected]->upright->upright == board[target] && board[selected]->upright->type !=0) ||
                (board[selected]->left->left == board[target] && board[selected]->left->type !=0) ||
                (board[selected]->right->right == board[target] && board[selected]->right->type !=0) ||
                (board[selected]->downleft->downleft == board[target] && board[selected]->downleft->type !=0) ||
                (board[selected]->downright->downright == board[target] && board[selected]->downright->type !=0))
                return true;
    return false;
}


//Return true if and only if the board currently contains
// only 1 connected component
//Hint: In my solution I first counted the total number of pieces on the board.
// Then I looped to find any piece of the board. From there I did a depth
// first search, counting how many pieces I found. If the number found
// equals the total number on the board, then return true. Otherwise,
// return false
bool isConnected(){
    //TODO -- not working..

	int totalCount = 0;
	int countTogether = 0;

	for (int i = 0; i < 400; i++){
		if (board[i]->type == 1)
			numWhite++;
		else if(board[i]->type == 2)
			numBlack++;
	}

	int root = 0;
	for (int j = 0; j < 400; j++){
		root = j;
		if (board[j]->type == 1 || board[j]->type == 2){
			countTogether++;
			while (board[j]->right->type == 1 || board[j]->right->type == 2){
				countTogether++;
				j++;
			}
			j = root;
			while (board[j]->type == 1 || board[j]->type == 2) {
				while ((board[j]->downleft->type == 1 || board[j]->downleft->type == 2)){
					countTogether++;
			//while (board[j]->downleft->right->type == 1 || board[j]->downleft->right->type == 2){
				//countTogether++;
					j++;
				}
				j = root + 1;
				while (board[j]->downleft->type == 1 || board[j]->downleft->type == 2){
					countTogether++;
					j--;
				}
				j = root;
				j = j+19;

				}
		}
	}
	if ((numBlack+numWhite) == countTogether)
		return true;
    
        return false;
}


/* This is used when the player is moving one of her pieces that is
 * already on the board to a new space.
 *
 * Return true iff the current player can place the piece in board
 * position (x,y).
 *
 * We can move the old piece here if
 * 0) Target space is empty,
 * AND
 * 1a) Moving to an unoccupied neighboring space, OR
 * 1b) Moving to an unoccupied space that is one jump over a neighbor
 * AND
 * 2) The move does not result in disconnected board
 * AND
 * 3) Target space is still adjacent to an existing piece (could be our own
 *    piece or an enemy piece, doesn't matter)
 *
 * Hint: you may want to use checkNbrs, isNeighboringSpace,
 *       isJumpSpace, and isConnected as subroutines here.
 */
bool canPlaceOldPiece(int x, int y){
    //TODO MM
        int selected = selectedPieceY*20+selectedPieceX;
    int target = 20*y+x;
	bool isConnect = false;
	// Check to see how many neighbors selected has
	/*int neighbors = 0;
	int neighWhite = 0;
	int neighBlack = 0;
	
	if (board[selected]->upleft->type != 0){
		neighbors++;
		if (board[selected]->upleft->type = 1)
			neighWhite++;
		else
			neighBlack++;
	}
	if (board[selected]->upright->type != 0){
		neighbors++;
		//if (board[selected]->upright->type = 1)
			//neighWhite++;
		//else
			//neighBlack++;
	}
	if (board[selected]->right->type != 0){
		neighbors++;
		/*if (board[selected]->right->type = 1)
			neighWhite++;
		else
			neighBlack++;
			
	}
	if (board[selected]->downright->type != 0){
		neighbors++;
		/*if (board[selected]->downright->type = 1)
			neighWhite++;
		else
			neighBlack++;
			
	}
	if (board[selected]->downleft->type != 0){
		neighbors++;
		/*if (board[selected]->downleft->type = 1)
			neighWhite++;
		else
			neighBlack++;
			
	}
	if (board[selected]->left->type != 0){
		neighbors++;
		/*if (board[selected]->left->type = 1)
			neighWhite++;
		else
			neighBlack++;
			
	}

	int neighborsXY = 0;
	int neighXYWhite = 0;
	int neighXYBlack = 0;

	if (board[target]->upleft->type != 0){
		neighborsXY++;
		/*if (board[selected]->upleft->type = 1)
			neighXYWhite++;
		else
			neighXYBlack++;
			

	}
	if (board[target]->upright->type != 0){
		neighborsXY++;
		/*if (board[selected]->upright->type = 1)
			neighXYWhite++;
		else
			neighXYBlack++;
			

	}
	if (board[target]->right->type != 0){
		neighborsXY++;
		/*if (board[selected]->right->type = 1)
			neighXYWhite++;
		else
			neighXYBlack++;
			}
	if (board[target]->downright->type != 0){
		neighborsXY++;
	/*	if (board[selected]->downright->type = 1)
			neighXYWhite++;
		else
			neighXYBlack++;
			

	}
	if (board[target]->downleft->type != 0){
		neighborsXY++;
		/*if (board[selected]->downleft->type = 1)
			neighXYWhite++;
		else
			neighXYBlack++;
			
	}	
	if (board[target]->left->type != 0){
		neighborsXY++;
		/*if (board[selected]->left->type = 1)
			neighXYWhite++;
		else
			neighXYBlack++;
			
	}
	// Check if isconnected	
	//if (board[selected]
	//if (board[

	if (neighborsXY < neighbors)
		isConnect = false;
	//if (board[selected]->upleft->type != 0 && board[target]
//	else if (neighXYWhite < neighWhite)
//		isConnect = false;
//	else if (neightXYBlack < neighBlack)
//		isConnect = false;
	/*else
		isConnect = true;*/




	if ((board[target]->type == 0) && (isNeighboringSpace(x,y) || isJumpSpace(x,y))){
		if ((board[target]->upright->type == 1 || board[target]->upright->type == 2)
			|| (board[target]->right->type == 1 || board[target]->right->type == 2)
			|| (board[target]->downright->type == 1 || board[target]->downright->type == 2)
			|| (board[target]->downleft->type == 1 || board[target]->downleft->type == 2)
			|| (board[target]->left->type == 1 || board[target]->left->type == 2)
			|| (board[target]->upleft->type == 1 || board[target]->upleft->type == 2)){
		//		if (isConnect){
				 
			//	if (isConnected())
		//&& canPlaceNewPiece(x,y))
		//&& (isConnected()))
			return true;
		//		}
		}
	}
    return false;
}


/*
 * Which type of piece is at board position (x,y)?
 * If no piece, return 0. Otherwise, return the player number of the piece
 * (1 or 2)
 */
int pieceAt(int x,int y){
    //TODO
        int target = 20*y+x;
        return board[target]->type;
}


void drawboard(){
    //NOTE: This will need to be adapted to your board
    // data structure!
    //For each board hex...
    for(int y=0;y<boardH;y++){
        for(int x=0;x<boardW;x++){
            //Calculate the center, and draw the border
            float offset = (hexW/2) * (y%2);
            ofSetColor(0, 0, 0);
            drawHex(boardXOffset+x*hexW+offset,boardYOffset+y*hexH,sideLen);
            
            if(pieceAt(x,y) != 0){
                //If there is a playing piece in the current hex,
                // draw it
                if(pieceAt(x,y) == 1){
                    ofSetColor(255,255,255);
                } else {
                    ofSetColor(0,0,0);
                }
                ofCircle(boardXOffset+x*hexW+offset,boardYOffset+y*hexH,sideLen/2);
            } else {
                //This is an unoccupied space, but we might need to draw some
                // highlights...
                if(currentAction == 1){
                    //If the user is trying to place a new piece,
                    // higlight the space if it is valid to place the piece here
                    ofSetColor(64,192,64); //green highlight
                    
                    if(canPlaceNewPiece(x, y)){
                        ofCircle(boardXOffset+x*hexW+offset,boardYOffset+y*hexH,sideLen/2);
                    }
                                        
                } else if(currentAction == 2){
                    //If the user is trying to move an old piece,
                    // higlight the space if it is valid to place the piece here
                    ofSetColor(64,192,64); //green
                    
                    if(canPlaceOldPiece(x, y)){
                        ofCircle(boardXOffset+x*hexW+offset,boardYOffset+y*hexH,sideLen/2);
                    }
                }
            }
        }
    }
    
    if(currentAction == 1){
        //If placing a new piece, draw the piece that the user is placing
        // at the mouse location
        if(whoseTurn == 1){
            ofSetColor(255,255,255);
        } else {
            ofSetColor(0,0,0);
        }
        
        ofCircle(ofGetMouseX(),ofGetMouseY(),sideLen/2);
    } else if(currentAction == 2){
        //If moving an old piece...
        
        //...show where it is being moved FROM
        ofSetColor(64,64,192); //blue
        float offset = (hexW/2) * (selectedPieceY%2);
        ofCircle(boardXOffset+selectedPieceX*hexW+offset,boardYOffset+selectedPieceY*hexH,sideLen/2);
        
        //...and also show the piece in the player's "hand" being moved
        if(whoseTurn == 1){
            ofSetColor(255,255,255);
        } else {
            ofSetColor(0,0,0);
        }
        ofCircle(ofGetMouseX(),ofGetMouseY(),sideLen/2);
    }
    
}


/*
 * Draw the store of remaining pieces on the right side of the screen
 */
void drawSpares(){
    float xOffset = boardXOffset + (1+boardW)*hexW;
    
    ofSetColor(255, 255, 255);
    for(int i=0;i<pl1spares;i++){
        ofCircle(xOffset + i*2*sideLen,2*sideLen,sideLen/2);
    }
    
    ofSetColor(0, 0, 0);
    for(int i=0;i<pl2spares;i++){
        ofCircle(xOffset + i*2*sideLen,3.5*sideLen,sideLen/2);
    }
}


//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(128,128,128); //gray
    drawboard();
    drawSpares();
}


/*
 * Put a piece on the board at position (x,y). 
 * If whichPieces is 0, then it clears that board position.
 */
void putPieceAt(int x, int y, int whichPiece){
    //TODO
        int target = 20*y+x;
        board[target]->type=whichPiece;
}


//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(x >= boardXOffset + (boardW)*hexW){
        //We are clicking the right-hand side of the screen, so we are
        // picking up or putting back a piece
        if(whoseTurn == 1 && pl1spares > 0 && currentAction == 0){
            currentAction = 1;
            pl1spares--;
        } else if(whoseTurn == 2 && pl2spares > 0 && currentAction == 0){
            currentAction = 1;
            pl2spares--;
        } else if (whoseTurn == 1 && currentAction == 1){
            currentAction = 0;
            pl1spares++;
        } else if (whoseTurn == 2 && currentAction == 1){
            currentAction = 0;
            pl2spares++;
        }
    } else if(x > boardXOffset && x <= boardXOffset +(boardW)*hexW ) {
        //We are clicking on the board...
        if(currentAction == 1){
            //...placing a new piece
            int whichRow = (y-boardYOffset+hexH/2)/hexH;
            int whichCol = (x-(boardXOffset+(whichRow%2)*(hexW/2))+hexW/2)/hexW;
            if(whichRow >= 0 && whichRow < boardH && whichCol >= 0 && whichCol < boardW){
                if(canPlaceNewPiece(whichCol,whichRow)){
                    currentAction = 0;
                    putPieceAt(whichCol,whichRow,whoseTurn);
					if(whoseTurn == 1)
						bankWhite--;
					else
						bankBlack--;
                    whoseTurn = 3 - whoseTurn;
                }
            }
        } else if(currentAction == 0){
            //...picking up and old piece
            int whichRow = (y-boardYOffset+hexH/2)/hexH;
            int whichCol = (x-(boardXOffset+(whichRow%2)*(hexW/2))+hexW/2)/hexW;
            
            if(pieceAt(whichCol,whichRow) == whoseTurn){
                selectedPieceX = whichCol;
                selectedPieceY  = whichRow;
                currentAction = 2;
                putPieceAt(whichCol,whichRow,0);
            }
        } else if(currentAction == 2){
            //...placing an old piece back on the board
            int whichRow = (y-boardYOffset+hexH/2)/hexH;
            int whichCol = (x-(boardXOffset+(whichRow%2)*(hexW/2))+hexW/2)/hexW;
            if(whichRow == selectedPieceY && whichCol == selectedPieceX){
                currentAction = 0;
                putPieceAt(whichCol,whichRow,whoseTurn);
            } else if(whichRow >= 0 && whichRow < boardH && whichCol >= 0 && whichCol < boardW){
                if(canPlaceOldPiece(whichCol, whichRow)){
                    currentAction = 0;
                    putPieceAt(whichCol,whichRow,whoseTurn);
                    whoseTurn = 3 - whoseTurn;
                }
            }
        }
    }
}
