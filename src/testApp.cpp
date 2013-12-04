#include "GameEvent.h"
#include "testApp.h"
#include <set>
#include <cmath>

//////////////////
/* Function declarations
 *
 * These are all functions that are defined and used in this file, so we don't 
 * need to put them in the .h file. You can ignore this: The comments about what
 * each function does is down in the body of the code.
 */
//Functions you might want to use, game logic
bool inVise(int x);
void doVise();
void checkNbrs(int x, int& okayNbrs, int& badNbrs);
bool canPlaceNewPiece(int x);
bool isNeighboringSpace(int x);
bool isJumpSpace(int x);
bool isConnected();
bool canPlaceOldPiece(int x);
int pieceAt(int x);
void putPieceAt(int x, int whichPiece);

//Drawing functions
void drawHex(float x, float y, float sideLen);
void drawBoard();
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

//The coordinates of the selected piece, if the player is moving an existing piece. This is in Board coordinates, not screen coordinates.
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


//gameEvent->gameBoard variable
GameEvent* gameEvent;

//--------------------------------------------------------------
void testApp::setup(){
    //This is the *maximum* rate. Your program might go slower if your
    // updates or draws are too time conusming.
    ofSetFrameRate(60);
    
    //TODO: Initialize your "board" data structure here
	gameEvent = new GameEvent();
    //TODO: Put 1 piece for each player in the middle of the board, side by side
    putPieceAt(209, 1);
	putPieceAt(210, 2);

    startTime = ofGetElapsedTimef();
}

//Return true iff there is a piece in board space (x,y), and that piece
// is caught in a vise. Note that x and y are in board coordinates,
// not screen coordinates
bool inVise(int x){
    if(gameEvent->gameBoard[x]->player == 0)
		return false;
	else if(gameEvent->gameBoard[x]->player == 1) {
		if((gameEvent->gameBoard[x]->topRight->player == 2  && gameEvent->gameBoard[x]->bottomLeft->player == 2) || (gameEvent->gameBoard[x]->topLeft->player == 2 && gameEvent->gameBoard[x]->bottomRight->player == 2) || (gameEvent->gameBoard[x]->left->player == 2 && gameEvent->gameBoard[x]->right->player == 2))
			return true;
		return false;
	}
	else if(gameEvent->gameBoard[x]->player == 2) {
		if((gameEvent->gameBoard[x]->topRight->player == 1  && gameEvent->gameBoard[x]->bottomLeft->player == 1) || (gameEvent->gameBoard[x]->topLeft->player == 1 && gameEvent->gameBoard[x]->bottomRight->player == 1) || (gameEvent->gameBoard[x]->left->player == 1 && gameEvent->gameBoard[x]->right->player == 1))
			return true;
		return false;
	}
	return false;
}

/*
 * This is the method that updates the board if a player is caught in a vise at the end of the turn.
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
    //Identify All pieces in vise using inVise()

	//for (int i = 0; i < 399; i++) {
	//	if (inVise(i))
	//		if (inVise(gameEvent->gameBoard[i]->topRight->index))
	//			gameEvent->gameBoard[i]->topRight->player = 0;
	//		if (inVise(gameEvent->gameBoard [i]->topLeft->index))
	//			gameEvent->gameBoard[i]->topLeft->player = 0;
	//		if (inVise(gameEvent->gameBoard [i]->right->index))
	//			gameEvent->gameBoard[i]->right->player = 0;
	//		if (inVise(gameEvent->gameBoard [i]->left->index))
	//			gameEvent->gameBoard[i]->left->player = 0;
	//		if (inVise(gameEvent->gameBoard [i]->bottomRight->index))
	//			gameEvent->gameBoard[i]->bottomRight->player = 0;
	//		if (inVise(gameEvent->gameBoard [i]->bottomLeft->index))
	//			gameEvent->gameBoard[i]->bottomLeft->player = 0;
	//		gameEvent->gameBoard[i]->player = 0;
	//}

	//Find the largest connected component and place pieces back into storehouse

	//
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
void checkNbrs(int x, int& okayNbrs, int& badNbrs){
	//check good neighbors
	if (gameEvent->gameBoard[x]->topRight->player == whoseTurn)
		okayNbrs += 1;
	if (gameEvent->gameBoard[x]->topLeft->player == whoseTurn)
		okayNbrs += 1;
	if (gameEvent->gameBoard[x]->right->player == whoseTurn)
		okayNbrs += 1;
	if (gameEvent->gameBoard[x]->left->player == whoseTurn)
		okayNbrs += 1;
	if (gameEvent->gameBoard[x]->bottomRight->player == whoseTurn)
		okayNbrs += 1;
	if (gameEvent->gameBoard[x]->bottomLeft->player == whoseTurn)
		okayNbrs += 1;

	//check bad neighbors
	if ((gameEvent->gameBoard[x]->topRight->player != whoseTurn) && (gameEvent->gameBoard[x]->topRight->player != 0))
		badNbrs += 1;
	if ((gameEvent->gameBoard[x]->topLeft->player != whoseTurn) && (gameEvent->gameBoard[x]->topLeft->player != 0))
		badNbrs += 1;
	if ((gameEvent->gameBoard[x]->right->player != whoseTurn) && (gameEvent->gameBoard[x]->right->player != 0))
		badNbrs += 1;
	if ((gameEvent->gameBoard[x]->left->player != whoseTurn) && (gameEvent->gameBoard[x]->left->player != 0))
		badNbrs += 1;
	if ((gameEvent->gameBoard[x]->bottomRight->player != whoseTurn) && (gameEvent->gameBoard[x]->bottomRight->player != 0))
		badNbrs += 1;
	if ((gameEvent->gameBoard[x]->bottomLeft->player != whoseTurn) && (gameEvent->gameBoard[x]->bottomLeft->player != 0))
		badNbrs += 1;
}

/*
 * Return true if the current player can place a new piece
 * in row y, column x, without violating the rules. That is,
 * at least 1 neighboring hex must contain one of the player's
 * pieces, and none of the neighboring hex can contain an
 * opposing player's piece
 */
bool canPlaceNewPiece(int x){
    int okayNbrs=0;
    int badNbrs=0;
    checkNbrs(x,okayNbrs,badNbrs);
    return(okayNbrs > 0 && badNbrs == 0);
}

//Return true if (x) is neighboring to (selectedPieceX)
//These inputs are in board coordinates, not screen coordinates
bool isNeighboringSpace(int x){
 
	if(gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->right->index == x) 
		return true;
	else if(gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->left->index == x) 
		return true;
	else if(gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->topLeft->index == x) 
		return true;
	else if(gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->topRight->index == x) 
		return true;
	else if(gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->bottomLeft->index == x) 
		return true;
	else if(gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->bottomRight->index == x) 
		return true;
	else
		return false;
		
}

//Return true if (x) is one jump to (selectedPieceX)
//These inputs are in board coordinates, not screen coordinates
bool isJumpSpace(int x){

	if(gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->topRight->player != 0 && gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->topRight->topRight->index == x) 
		return true;
	else if(gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->topLeft->player != 0 && gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->topLeft->topLeft->index == x) 
		return true;
	else if(gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->right->player != 0 && gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->right->right->index == x) 
		return true;
	else if(gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->left->player != 0 && gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->left->left->index == x) 
		return true;
	else if(gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->bottomRight->player != 0 && gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->bottomRight->bottomRight->index == x) 
		return true;
	else if(gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->bottomLeft->player != 0 && gameEvent->gameBoard[(selectedPieceY*20) + selectedPieceX]->bottomLeft->bottomLeft->index == x) 
		return true;
	else
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
	//RETURN TRUE FOR DEMO
	return true;
	int* myArray = new int[10];
	int count = 0;
	int secondCount = 1; // Since you are starting at the first piece index later
	// start the count at 1. 
	int foundPiece = 0;
	bool found = false;
	bool connected = false;

	// Count the total number of pieces
	for (int i = 0; i < 400; i++) {
		if (gameEvent->gameBoard[i]->player == 2 || gameEvent->gameBoard[i]->player == 1) {
			count++;
		}
	}
	// Not sure why count is only recording one number and not two. 
	std::cout << "count: " << count << std::endl;
	// Find the first piece on the board
	for (int i = 0; i < 400; i++) {
		if (gameEvent->gameBoard[i]->player == 2 || gameEvent->gameBoard[i]->player == 1) {
			foundPiece = i;
			found = true;
			myArray[0] = foundPiece;
			// Break once you find the first piece
			break;
		}
	}
	// Begin to test and see if the other pieces are connected to that first piece.
	for (int j = foundPiece; j < 400; j++) {
		// Set j to the foundPiece since there is no piece prior to it. 
		if ((gameEvent->gameBoard[j]->right->player == 1) || (gameEvent->gameBoard[j]->right->player == 2)) {
			for (int i = 0; i < 10; i++) {
				if (gameEvent->gameBoard[j]->index != myArray[i]) {
					// Testing to see if the index is already been accounted for if so don't count it again. 
					connected = true;
					myArray[secondCount] = gameEvent->gameBoard[j]->right->index;
					secondCount = secondCount + 1;
				}
			}
		}
		else if ((gameEvent->gameBoard[j]->bottomLeft->player == 1) || (gameEvent->gameBoard[j]->bottomLeft->player == 2)) {
			for (int i = 0; i < 10; i++) {
				if (gameEvent->gameBoard[j]->index != myArray[i]) {
					connected = true;
					myArray[secondCount] = gameEvent->gameBoard[j]->bottomLeft->index;
					secondCount = secondCount + 1;
				}
			}
		}
		else if ((gameEvent->gameBoard[j]->bottomRight->player == 1) || (gameEvent->gameBoard[j]->bottomRight->player == 2)) {
			for (int i = 0; i < 10; i++) {
				if (gameEvent->gameBoard[j]->index != myArray[i]) {
					connected = true;
					myArray[secondCount] = gameEvent->gameBoard[j]->bottomRight->index;
					secondCount = secondCount + 1;
				}
			}

		}//****If I comment everything out below this point it will run. Not sure why below this point it won't run. 
		/*else if ((gameEvent->gameBoard[j]->left->player == 1) || (gameEvent->gameBoard[j]->left->player == 2)) {
		for(int i = 0; i < 10; i++) {
		if (gameEvent->gameBoard[j]->index != myArray[i]) {
		connected = true;
		myArray[secondCount] = gameEvent->gameBoard[j]->left->index;
		secondCount = secondCount+1;
		}
		}

		} else if ((gameEvent->gameBoard[j]->topLeft->player == 1) || (gameEvent->gameBoard[j]->topLeft->player == 2)) {
		for(int i = 0; i < 10; i++) {
		if (gameEvent->gameBoard[j]->index != myArray[i]) {
		connected = true;
		myArray[secondCount] = gameEvent->gameBoard[j]->topLeft->index;
		secondCount = secondCount+1;
		}
		}
		} else if ((gameEvent->gameBoard[j]->topRight->player == 1) || (gameEvent->gameBoard[j]->topRight->player == 2)) {
		for(int i = 0; i < 10; i++) {
		if (gameEvent->gameBoard[j]->index != myArray[i]) {
		connected = true;
		myArray[secondCount] = gameEvent->gameBoard[j]->topRight->index;
		secondCount = secondCount+1;
		}
		}
		}
		*/
	}

	// If the counts equal one another then the board is connected. 
	/* At some point we need this just commented it out for testing reasons.
	if (count == secondCount) {
	connected = true;
	}
	*/
	return connected;
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
bool canPlaceOldPiece(int x){
	int okayNbrs = 0;
	int badNbrs  = 0;
	checkNbrs(x,okayNbrs, badNbrs);

    if( (gameEvent->gameBoard[x]->player == 0) && ((isNeighboringSpace(x)) || (isJumpSpace(x)) && (okayNbrs > 0 || badNbrs > 0)) && (isConnected()))
		return true;
	else
		return false;
}

/*
 * Which type of piece is at board position (x,y)?
 * If no piece, return 0. Otherwise, return the player number of the piece
 * (1 or 2)
 */
int pieceAt(int x){
    return gameEvent->gameBoard[x]->player;
}

void drawBoard(){
    //NOTE: This will need to be adapted to your board
    // data structure!
    //For each board hex...
    for(int y=0;y<boardH;y++){
        for(int x=0;x<boardW;x++){
            //Calculate the center, and draw the border
            float offset = (hexW/2) * (y%2);
            ofSetColor(0, 0, 0);
            drawHex(boardXOffset+x*hexW+offset,boardYOffset+y*hexH,sideLen);
            
            if(pieceAt((y*20)+x) != 0){
                //If there is a playing piece in the current hex,
                // draw it
                if(pieceAt((y*20)+x) == 1){
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
                    
                    if(canPlaceNewPiece((y*20)+x)){
                        ofCircle(boardXOffset+x*hexW+offset,boardYOffset+y*hexH,sideLen/2);
                    }
                } else if(currentAction == 2){
                    //If the user is trying to move an old piece,
                    // higlight the space if it is valid to place the piece here
                    ofSetColor(64,192,64); //green
                    
                    if(canPlaceOldPiece((y*20)+x)){
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
    drawBoard();
    drawSpares();
}

/*
 * Put a piece on the board at position (x,y). 
 * If whichPieces is 0, then it clears that board position.
 */
void putPieceAt(int x, int whichPiece){
     gameEvent->gameBoard[x]->player = whichPiece;
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
                if(canPlaceNewPiece((whichRow*20)+whichCol)){
                    currentAction = 0;
                    putPieceAt((whichRow*20)+whichCol,whoseTurn);
                    whoseTurn = 3 - whoseTurn;
                }
            }
        } else if(currentAction == 0){
            //...picking up and old piece
            int whichRow = (y-boardYOffset+hexH/2)/hexH;
            int whichCol = (x-(boardXOffset+(whichRow%2)*(hexW/2))+hexW/2)/hexW;
            
            if(pieceAt((whichRow*20)+whichCol) == whoseTurn){
                selectedPieceX  = whichCol;
                selectedPieceY  = whichRow;
                currentAction = 2;
                putPieceAt((whichRow*20)+whichCol,0);
            }
        } else if(currentAction == 2){
            //...placing an old piece back on the board
            int whichRow = (y-boardYOffset+hexH/2)/hexH;
            int whichCol = (x-(boardXOffset+(whichRow%2)*(hexW/2))+hexW/2)/hexW;
            if(whichRow == selectedPieceY && whichCol == selectedPieceX){
                currentAction = 0;
                putPieceAt((whichRow*20)+whichCol,whoseTurn);
            } else if(whichRow >= 0 && whichRow < boardH && whichCol >= 0 && whichCol < boardW){
                if(canPlaceOldPiece((whichRow*20)+whichCol)){
                    currentAction = 0;
                    putPieceAt((whichRow*20)+whichCol,whoseTurn);
                    whoseTurn = 3 - whoseTurn;
                }
            }
        }
    }
}

