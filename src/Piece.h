#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "Cell.h"
#include "Board.h"

class Board;

class Piece {
    public:
        Piece(int, int, int);
        char getCharacter();
		int getRow();
		int getCol();
		int getPlayer();
		bool getMoved();
		void setMoved(bool);
        void move(int, int);
        std::vector<Cell> getAvailableCells(Board&);

        // Pure virtual methods.
        virtual bool checkMove(int, int) = 0; // Check based on start and end position only.
		virtual bool checkMove2(int, int, Board&) = 0; // Check based on the positions of other pieces.

    protected:
        char character;
        int row, col;
        int player;
        bool moved; // Whether the piece has moved at all.
};

#endif
