#include "Cell.h"

Cell::Cell() {
	row = col = 0;
}

Cell::Cell(int r, int c) : row(r), col(c) {
}

bool Cell::operator==(const Cell& other) const{
	return row == other.row && col == other.col;
}

int Cell::getRow() const {
	return row;
}

int Cell::getCol() const {
	return col;
}