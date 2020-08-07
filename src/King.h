#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece {
	public:
		King(int, int, int);
		bool checkMove(int, int);
		bool checkMove2(int, int, Board&);
};

#endif