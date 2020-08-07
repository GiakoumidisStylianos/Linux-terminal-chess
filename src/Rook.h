#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Piece {
	public:
		Rook(int, int, int);
		bool checkMove(int, int);
		bool checkMove2(int, int, Board&);
};
#endif