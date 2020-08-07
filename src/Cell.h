#ifndef CELL_H
#define CELL_H

#include <fstream>

class Cell {
	
	public:
		Cell();
		Cell(int, int);
		bool operator==(const Cell&) const;

		int getRow() const;
		int getCol() const;

	private:
		int row, col;
};

#endif