#include "testApp.h"
#include "GameBoard.h"

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
void doVise();
void checkNbrs(int x, int y, int& okayNbrs, int& badNbrs);
bool canPlaceNewPiece(int x, int y);
bool isNeighboringSpace(int x, int y);
//bool isJumpSpace(int x, int y);
bool isConnected();
bool canPlaceOldPiece(int x, int y);
int pieceAt(int x,int y);
void putPieceAt(int x, int y, int whichPiece);

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


GameBoard myBoard;
ofColor player1, player2, player1Turn, player2Turn;
ofColor start, end2, customBlack;
ofSoundPlayer tada, p1Wins, p2Wins;
ofSoundPlayer music2;
ofTrueTypeFont text;
bool checkedWinDetection = true;

bool colorDirection;
bool p1StillInGame = true;
bool p2StillInGame = true;



//--------------------------------------------------------------
void testApp::setup(){
    //This is the *maximum* rate. Your program might go slower if your
    // updates or draws are too time conusming.
    ofSetFrameRate(60);
    player1.set(33,133,197);
    player1Turn.set(126, 206, 253);
    player2.set(255,89,89);
    player2Turn.set(255,143,143);
    start.set(255, 246, 229);
    customBlack.set(1, 1, 1);
    colorDirection = true;
    text.loadFont("Arial.ttf", 48);

    music2.loadSound("ViseMusic.mp3");
    music2.setLoop(true);
    music2.play();
    
    tada.loadSound("TaDa.wav");
    
    p1Wins.loadSound("p1Wins.mp3");
    p2Wins.loadSound("p2Wins.mp3");
    
    //TODO: Initialize your "board" data structure here
        //GameBoard myBoard;
        myBoard.makeGameBoard();
    //TODO: Put 1 piece for each player in the middle of hte board, side by side
    
    startTime = ofGetElapsedTimef();
}

//Return true iff there is a piece in board space (x,y), and that piece
// is caught in a vise. Note that x and y are in board coordinates,
// not screen coordinates
bool inVise(int x, int y){
	
	return myBoard.inVise(x,y);;
}

/*
 * This is the method that updates the board if a player is caught in a vise at the end2 of the turn.
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
    bool viseFound = false;
    for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if(myBoard.inVise(i,j)){
                viseFound = true;
            }
		}
	}
    /*
     
     */
    if (viseFound) {
        tada.play();
        myBoard.removeVises();
        myBoard.returnDisconnectedPieces();
        myBoard.resetVise();
        pl1spares = myBoard.getP1Spares();
        pl2spares = myBoard.getP2Spares();

    }
    if (currentAction==0 && !checkedWinDetection){
         p1StillInGame = myBoard.playerStillInGame(1);
         p2StillInGame = myBoard.playerStillInGame(2);
        
        if (!p1StillInGame) {
            music2.stop();
            p2Wins.play();
        }
        
        if (!p2StillInGame) {
            music2.stop();
            text.drawString("Player 1 Wins!", 350, 384);
            p1Wins.play();
        }
        
        checkedWinDetection = true;
    }

}

//--------------------------------------------------------------
void testApp::update(){
    //This can be helpful if you are doing animations
    currentFrame = (ofGetElapsedTimef() - startTime)/(1.0/60);
    
    //Check for vised pieces on every update
    doVise();
    if(whoseTurn==1)
        end2.set(player1Turn);
    else end2.set(player2Turn);
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
    myBoard.checkNbrs(x,y,okayNbrs,badNbrs);
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
    //checkNbrs(x,y,okayNbrs,badNbrs);

    return myBoard.canMove(x,y);
}

//Return true iff (x,y) is neighboring to (selectedPieceX,selectedPieceY)
//These inputs are in board coordinates, not screen coordinates
bool isNeighboringSpace(int x, int y){
    if (myBoard.isPlayerOneConnected(x,y) || myBoard.isPlayerTwoConnected(x,y))
         return true;
    return false;
}

//Return true iff (x,y) is one jump to (selectedPieceX,selectedPieceY)
//These inputs are in board coordinates, not screen coordinates
bool isJumpSpace(int x, int y){
    //TODO
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
	return myBoard.isContigious();
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
 * AN-D
 * 3) Target space is still adjacent to an existing piece (could be our own
 *    piece or an enemy piece, doesn't matter)
 *
 * Hint: you may want to use checkNbrs, isNeighboringSpace,
 *       isJumpSpace, and isConnected as subroutines here.
 */
bool canPlaceOldPiece(int x, int y){
    return myBoard.canMoveOld(x,y);

}

/*
 * Which type of piece is at board position (x,y)?
 * If no piece, return 0. Otherwise, return the player number of the piece
 * (1 or 2)
 */
int pieceAt(int x,int y){
    int piece = myBoard.getPiece(x,y);
    return piece;
}

void drawBoard(){
    //NOTE: This will need to be adapted to your board
    // data structure!
    //For each board hex...
    for(int y=0;y<boardH;y++){
        for(int x=0;x<boardW;x++){
            //Calculate the center, and draw the border
            float offset = (hexW/2) * (y%2);
            ofSetColor(0,0,0);
            drawHex(boardXOffset+x*hexW+offset,boardYOffset+y*hexH,sideLen);
            
            if(pieceAt(x,y) != -1){
                //If there is a playing piece in the current hex,
                // draw it
                if(pieceAt(x,y) == 1){
                    ofSetColor(player1);
                } else {
                    ofSetColor(player2);
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
            ofSetColor(player1);
        } else {
            ofSetColor(player2);
        }
        
        ofCircle(ofGetMouseX(),ofGetMouseY(),sideLen/2);
    } else if(currentAction == 2){
        //If moving an old piece...
        
        //...show where it is being moved FROM
        ofSetColor(192,64,192); //PURPLE, due to color scheme
        float offset = (hexW/2) * (selectedPieceY%2);
        ofCircle(boardXOffset+selectedPieceX*hexW+offset,boardYOffset+selectedPieceY*hexH,sideLen/2);
        
        //...and also show the piece in the player's "hand" being moved
        if(whoseTurn == 1){
            ofSetColor(player1);
        } else {
            ofSetColor(player2);
        }
        ofCircle(ofGetMouseX(),ofGetMouseY(),sideLen/2);
    }
    
}

/*
 * Draw the store of remaining pieces on the right side of the screen
 */
void drawSpares(){
    float xOffset = boardXOffset + (1+boardW)*hexW;
    
    ofSetColor(player1);
    for(int i=0;i<pl1spares;i++){
        ofCircle(xOffset + i*2*sideLen,2*sideLen,sideLen/2);
    }
    
    ofSetColor(player2);
    for(int i=0;i<pl2spares;i++){
        ofCircle(xOffset + i*2*sideLen,3.5*sideLen,sideLen/2);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    if (p1StillInGame && p2StillInGame){
    if (currentFrame%1 ==0) {
        if (customBlack==ofColor(1,1,1)) {
            colorDirection = true;
        }
        else if(customBlack==ofColor(255,255,255)){
            colorDirection = false;
        }
        if (colorDirection)
        customBlack += ofColor(1,1,1);
        else customBlack -= ofColor(1,1,1);
    }
    
    end2.set(end2 -=customBlack);
    ofBackgroundGradient(start,end2,OF_GRADIENT_BAR);
//    for (double i=0.; i<384; i +=.1) {
//        ofSetColor(player1Turn.lerp(end2, 1));
//        ofFill();
//        ofRect(0, i, 1024, 1);
//    }
    
    
    
    //ofBackgroundGradient(end2,start,OF_GRADIENT_BAR); //gray
    //ofBackground(255, 246, 229);
    drawBoard();
    drawSpares();
    }
    else{
    if (!p1StillInGame) {
        ofSetColor(player2);
        text.drawString("Player 2 Wins!", 300, 384);
    }
    if (!p2StillInGame) {
        ofSetColor(player1);
        text.drawString("Player 1 Wins!", 300, 384);
    }
    }
}

/*
 * Put a piece on the board at position (x,y). 
 * If whichPieces is 0, then it clears that board position.
 */
void putPieceAt(int x, int y, int whichPiece){
    myBoard.addPiece(x,y,whichPiece);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(x >= boardXOffset + (boardW)*hexW){
        //We are clicking the right-hand side of the screen, so we are
        // picking up or putting back a piece
        if(whoseTurn == 1 && pl1spares > 0 && currentAction == 0){
            currentAction = 1;
            pl1spares--;
            myBoard.setP1Spares(pl1spares);
        } else if(whoseTurn == 2 && pl2spares > 0 && currentAction == 0){
            currentAction = 1;
            pl2spares--;
            myBoard.setP2Spares(pl2spares);
        } else if (whoseTurn == 1 && currentAction == 1){
            currentAction = 0;
            pl1spares++;
            myBoard.setP1Spares(pl1spares);
        } else if (whoseTurn == 2 && currentAction == 1){
            currentAction = 0;
            pl2spares++;
            myBoard.setP2Spares(pl2spares);
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
                    whoseTurn = 3 - whoseTurn;
                    checkedWinDetection = false;
                    if (whoseTurn==2){
                        myBoard.setPlayerOneTurn(false);
                    }
                    else myBoard.setPlayerOneTurn(true);
                }
            }
        } else if(currentAction == 0){
            //...picking up and old piece
            int whichRow = (y-boardYOffset+hexH/2)/hexH;
            int whichCol = (x-(boardXOffset+(whichRow%2)*(hexW/2))+hexW/2)/hexW;
            myBoard.setPieceToMove(whichCol,whichRow);
            if(pieceAt(whichCol,whichRow) == whoseTurn){
                selectedPieceX = whichCol;
                selectedPieceY  = whichRow;
                currentAction = 2;
                putPieceAt(whichCol,whichRow,-1);
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
                    checkedWinDetection = false;
                    if (whoseTurn==2){
                        myBoard.setPlayerOneTurn(false);
                    }
                    else myBoard.setPlayerOneTurn(true);
                }
            }
        }
    }
}
