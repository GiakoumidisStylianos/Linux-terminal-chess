#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <fstream>
#include "Piece.h"
#include "MoveData.h"

class Piece;
class MoveData;

class Board {
    public:
    	Board();
		Board(std::ifstream&);
		~Board();

    	Piece* getPieceAt(int, int);
		bool movePiece(int, int, int, int);
		bool areThereAvailableMoves(int);
		bool isKingSafe(int);
		void goBack();
		void goForward();
		void addPiecesFromFile();
		void revertLastMove();
    	void printBoard(int, int, const std::vector<Cell>&);
    	void clear();
		void saveBoardToFile(std::ofstream&);

    private:
        const int CELL_SIZE_X = 6;
        const int CELL_SIZE_Y = 3;

        Piece** pieces; // All the pieces on the board.
		Piece *wKing, *bKing; // The kings are also saved here for fast access.
		std::vector<MoveData> moves; // All the moves made in the game are stored here.
		int currentMove; // What move the board is currently showing.

		void addPiece(Piece*);
		void addDefaultPieces();
		void addPiecesFromFile(std::ifstream&);
		void revertMove(MoveData);
		bool isAttacked(int, int, int);
		int convertToIndex(int, int);
};

#endif
