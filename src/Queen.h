#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
class Queen : public Piece {

	public:
		Queen(int, int, int);
		bool checkMove(int, int);
		bool checkMove2(int, int, Board&);
};

#endif