#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Board.h"

using namespace std;

class Game {

	private:
		const string FILE_PATH = "./lastgame";

		string message; // A message that will appear at the terminal.
		Board* board;
		int playerTurn; // Whose player's turn it is.
		int currentRow, currentCol; // Cursor coordinates.
		int selectedRow, selectedCol; // Selected cell coordinates.
		
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void switchPlayer();
		void drawBoard(int, int, vector<Cell>&);
		void saveBoard();

	public:
		Game(string);
		~Game();

		void startGame();
};


#endif