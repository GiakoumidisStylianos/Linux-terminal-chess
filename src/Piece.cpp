#include "Piece.h"

Piece::Piece(int row, int col, int player) : row(row), col(col), player(player) {
	moved = false;
}

std::vector<Cell> Piece::getAvailableCells(Board& board) {
	std::vector<Cell> ret;
	for (int r = 1; r <= 8; r++) {
		for (int c = 1; c <= 8; c++) {
			if (checkMove(r, c) && checkMove2(r, c, board)) {
				ret.push_back(Cell(r, c));
			}
		}
	}
	return ret;
}

int Piece::getRow() {
	return row;
}

int Piece::getCol() {
	return col;
}

int Piece::getPlayer() {
	return player;
}

void Piece::move(int r, int c) {
	row = r;
	col = c;
	moved = true;
}

char Piece::getCharacter() {
	return character;
}

bool Piece::getMoved() {
	return moved;
}

void Piece::setMoved(bool moved) {
	this->moved = moved;
}