#include "Rook.h"

Rook::Rook(int row, int col, int player) : Piece(row, col, player) {
	character = player == 1 ? 'R' : 'r';
}

bool Rook::checkMove(int destRow, int destCol) {

	// Cannot go to the same cell.
	if (row == destRow && col == destCol)
		return false;

	if (row == destRow || col == destCol)
		return true;


	return false;
}

bool Rook::checkMove2(int destRow, int destCol, Board& board) {

	// Find the direction of the movement.
	int dirX = destCol - col > 0 ? 1 : (destCol - col == 0 ? 0 : -1);
	int dirY = destRow - row > 0 ? 1 : (destRow - row == 0 ? 0 : -1);
	
	int r = row + dirY;
	int c = col + dirX;

	while(1) {
		Piece* p = board.getPieceAt(r, c);
		
		if (p != NULL) {
			if (p->getPlayer() == player)
				return false;
			else {
				return r == destRow && c == destCol;
			}
		}

		if (r == destRow && c == destCol)
			return true;

		r += dirY;
		c += dirX;
	}
}