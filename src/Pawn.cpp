#include "Pawn.h"

Pawn::Pawn(int row, int col, int player) : Piece(row, col, player) {
	character = player == 1 ? 'P' : 'p';
}

bool Pawn::checkMove(int destRow, int destCol) {

	int sign = player == 1 ? 1 : -1; // The direction of the movement.

	if (col == destCol) {
		if (moved) {
			if (destRow == row + 1 * sign)
				return true;
		}
		else {
			if (destRow == row + 1 * sign || destRow == row + 2 * sign)
				return true;
		}
	}
	else if (abs(col - destCol) == 1) {
		if (destRow == row + 1 * sign)
			return true;
	}
	return false;
}

bool Pawn::checkMove2(int destRow, int destCol, Board& board) {

	if (col == destCol) {
		if (player == 1) {
			for (int i = row + 1; i <= destRow; i++) {
				if (board.getPieceAt(i, col) != NULL)
					return false;
			}
		}
		else {
			for (int i = row - 1; i >= destRow; i--) {
				if (board.getPieceAt(i, col) != NULL)
					return false;
			}
		}
		return true;
	}
	else {
		Piece* p = board.getPieceAt(destRow, destCol);
		if (p != NULL && p->getPlayer() != player)
			return true;
		else
			return false;
	}
}

bool Pawn::checkAttack(int r, int c) {
	int dir = player == 1 ? 1 : -1;
	if (r == row + dir && abs(c - col) == 1)
		return true;
	return false;
}