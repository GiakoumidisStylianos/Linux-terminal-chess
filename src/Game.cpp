#include <iostream>
#include <fstream>
#include <algorithm>
#include "Game.h"

using namespace std;

Game::Game(string filePath) {
	// Disable echo of input characters.
	system("stty -echo");

	if (!filePath.empty()) {
		ifstream stream(filePath, ios::in | ios::binary);
		if (!stream) {
			system("stty echo");
			exit(1);
		}
		board = new Board(stream);
		stream.close();
	}
	else
		board = new Board();
}

Game::~Game() {
	delete board;
}

void Game::startGame() {

	currentRow = currentCol = 1;
	selectedRow = selectedCol = -1;
	playerTurn = 1;

	vector<Cell> highlightedCells;

	char ch[3];
	bool gameOver = false;
	bool canMakeMove = true;
	int movesMade = 0;
	int currentMovePosition = 0;

    while(1) {

		drawBoard(currentRow, currentCol, highlightedCells);
		if (gameOver)
			break;
		ch[0] = getchar();

		// CTRL-C
		if (ch[0] == 3 || ch[0] == 'q' || ch[0] == 'Q')
			break;
		// ENTER
		else if (ch[0] == 13 && canMakeMove) {
			if (selectedRow == -1) {
				Piece* sel = board->getPieceAt(currentRow, currentCol);
				if (sel != NULL && playerTurn == sel->getPlayer()) {
					highlightedCells = sel->getAvailableCells(*board);
					if (highlightedCells.size() > 0) {
						selectedRow = currentRow;
						selectedCol = currentCol;
					}
				}
			}
			else if (currentRow == selectedRow && currentCol == selectedCol) {
				selectedRow = selectedCol = -1;
				highlightedCells.clear();
			}
			else if (find(highlightedCells.begin(), highlightedCells.end(), Cell(currentRow, currentCol)) != highlightedCells.end()) {
				bool success = board->movePiece(selectedRow, selectedCol, currentRow, currentCol);
				selectedRow = selectedCol = -1;
				highlightedCells.clear();

				if (success) {

					// Update the variables.
					movesMade++;
					currentMovePosition++;

					// Check for stalemate or checkmate.
					int otherPlayer = playerTurn == 1 ? 2 : 1;
					bool movesAvailable = board->areThereAvailableMoves(otherPlayer);
					bool kingSafe = board->isKingSafe(otherPlayer);
					if (!movesAvailable) {
						if (!kingSafe)
							message = string("The ") + (playerTurn == 1 ? "white" : "black") + " pieces win.";
						else
							message = "Stalemate.";
						gameOver = true;
					}

					// If the player that made the move is black, save the board.
					if (playerTurn == 2 && !gameOver)
						saveBoard();

					switchPlayer();
				}
				else
					message = "This move leaves the king unprotected.";
				
			}
			continue;
		}
		// Go back.
		else if ((ch[0] == 'B' || ch[0] == 'b') && selectedRow == -1) {
			
			if (currentMovePosition > 0) {
				board->goBack();
				currentMovePosition--;
				canMakeMove = false;
			}
			else
				message = "No more moves to go back.";

			continue;
		}
		// Go forward.
		else if (ch[0] == 'F' || ch[0] == 'f') {
			if (currentMovePosition < movesMade) {
				board->goForward();
				currentMovePosition++;
				canMakeMove = currentMovePosition == movesMade;
				
			}
			else
				message = "No more moves to go forward.";

			continue;
		}
		else if (ch[0] != 27) {
			cout << "Invalid input." << endl;
			continue;
		}

    	ch[1] = getchar();
    	ch[2] = getchar();

		// Arrow keys.
		if (ch[0] == 27 && ch[1] == 91) {
			switch(ch[2]) {
				case 65:
					moveUp();
					break;
				case 66:
					moveDown();
					break;
				case 67:
					moveRight();
					break;
				case 68:
					moveLeft();
					break;
			}
		}
    }

	// Restore the default terminal state.
	system("stty echo");
	system("stty cooked");
}

void Game::saveBoard() {
	ofstream stream(FILE_PATH, ios::out | ios::trunc | ios::binary);
	if (stream.is_open()) {
		board->saveBoardToFile(stream);
		stream.close();
	}
}

void Game::moveUp() {
	if (currentRow < 8)
		currentRow++;
	else
		currentRow = 1;
}

void Game::moveDown() {
	if (currentRow > 1)
		currentRow--;
	else
		currentRow = 8;
}

void Game::moveLeft() {
	if (currentCol > 1)
		currentCol--;
	else
		currentCol = 8;
}

void Game::moveRight() {
	if (currentCol < 8)
		currentCol++;
	else
		currentCol = 1;
}

void Game::switchPlayer() {
	playerTurn = playerTurn == 1 ? 2 : 1;
}

void Game::drawBoard(int currentRow, int currentCol, vector<Cell>& highlightedCells) {
	system("stty cooked");
	board->clear();
	board->printBoard(currentRow, currentCol, highlightedCells);

	// Print the message.
	if (!message.empty()) {
		cout << message << endl;
		message = "";
	}

	system("stty raw");
}