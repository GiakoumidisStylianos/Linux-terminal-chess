#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
	public:
		Knight(int, int, int);
		bool checkMove(int, int);
		bool checkMove2(int, int, Board&);
};

#endif