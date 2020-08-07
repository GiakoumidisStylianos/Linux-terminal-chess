#include "King.h"

King::King(int row, int col, int player) : Piece(row, col, player) {
	character = player == 1 ? 'K' : 'k';
}

bool King::checkMove(int destRow, int destCol) {

	// Cannot go to the same cell.
	if (row == destRow && col == destCol)
		return false;

	if (abs(row - destRow) <= 1 && abs(col - destCol) <= 1)
		return true;

	return false;
}

bool King::checkMove2(int destRow, int destCol, Board& board) {
	Piece* p = board.getPieceAt(destRow, destCol);
	if (p == NULL || p->getPlayer() != player)
		return true;
	return false;
}