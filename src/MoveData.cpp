#include "MoveData.h"

MoveData::MoveData(Piece* mvPiece, Piece* attPiece, Piece* promPiece, int sRow, int sCol, int dRow, int dCol) {
	movedPiece = mvPiece;
	attackedPiece = attPiece;
	promotedPiece = promPiece;
	srcRow = sRow;
	srcCol = sCol;
	dstRow = dRow;
	dstCol = dCol;
	pieceHadMoved = movedPiece->getMoved();
}

Piece* MoveData::getMovedPiece() {
	return movedPiece;
}

Piece* MoveData::getAttackedPiece() {
	return attackedPiece;
}

Piece* MoveData::getPromotedPiece() {
	return promotedPiece;
}

int MoveData::getSourceRow() {
	return srcRow;
}

int MoveData::getSourceCol() {
	return srcCol;
}

int MoveData::getDestRow() {
	return dstRow;
}

int MoveData::getDestCol() {
	return dstCol;
}

bool MoveData::getPieceHadMoved() {
	return pieceHadMoved;
}