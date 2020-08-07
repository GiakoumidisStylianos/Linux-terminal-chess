#include "Knight.h"

Knight::Knight(int row, int col, int player) : Piece(row, col, player) {
	character = player == 1 ? 'N' : 'n';
}

bool Knight::checkMove(int destRow, int destCol) {

	if (abs(row - destRow) == 2 && abs(col - destCol) == 1)
		return true;

	if (abs(row - destRow) == 1 && abs(col - destCol) == 2)
		return true;


	return false;
}

bool Knight::checkMove2(int destRow, int destCol, Board& board) {
	Piece* p = board.getPieceAt(destRow, destCol);
	if (p == NULL || p->getPlayer() != player)
		return true;
	return false;
}