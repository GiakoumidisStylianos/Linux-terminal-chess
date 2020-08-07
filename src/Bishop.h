#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
	public:
		Bishop(int, int, int);
		bool checkMove(int, int);
		bool checkMove2(int, int, Board&);
};

#endif