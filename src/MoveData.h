#ifndef MOVEDATA_H
#define MOVEDATA_H

#include "Piece.h"

class Piece;

class MoveData {
	private:
		Piece* movedPiece;
		Piece* attackedPiece;
		Piece* promotedPiece; // Set only for promotion moves.
		int srcRow, srcCol, dstRow, dstCol;
		bool pieceHadMoved;

	public:
		MoveData(Piece*, Piece*, Piece*, int, int, int, int);
		Piece* getMovedPiece();
		Piece* getAttackedPiece();
		Piece* getPromotedPiece();
		int getSourceRow();
		int getSourceCol();
		int getDestRow();
		int getDestCol();
		bool getPieceHadMoved();
};

#endif