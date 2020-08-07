#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Board.h"

class Pawn : public Piece {
	public:
		Pawn(int, int, int);
		bool checkMove(int, int);
		bool checkMove2(int, int, Board&);
		bool checkAttack(int, int);
};

#endif