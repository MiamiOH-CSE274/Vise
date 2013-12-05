#pragma once

class GameEvent {
public:

	struct Node {
		int index;
		int player;

		Node* topRight;
		Node* topLeft;
		Node* right;
		Node* left;
		Node* bottomRight;
		Node* bottomLeft;
	};

	Node** gameBoard;
	GameEvent();
	~GameEvent();

};

