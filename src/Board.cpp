#include <algorithm>
#include <iostream>
#include "Board.h"
#include "Game.h"

#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

using namespace std;

Board::Board() {
	currentMove = 0;
	pieces = new Piece*[64];
	for (int i = 0; i < 64; i++)
		pieces[i] = NULL;

	addDefaultPieces();
}

Board::Board(ifstream& stream) {
	currentMove = 0;
	pieces = new Piece*[64];
	for (int i = 0; i < 64; i++)
		pieces[i] = NULL;

	addPiecesFromFile(stream);
}

Board::~Board() {

	// Make sure the board is up to date before deallocating anything.
	while (currentMove < moves.size())
		goForward();

	//Deallocate pieces on the board.
	for (int i = 0; i < 64; i++) {
		if (pieces[i] != NULL)
			delete pieces[i];
	}
	delete[] pieces;
	
	// Deallocate pieces not currently on the board.
	vector<MoveData>::iterator it;
	for (it = moves.begin(); it != moves.end(); it++) {

		// Deallocate destroyed pieces.
		if (it->getAttackedPiece() != NULL)
			delete it->getAttackedPiece();

		// Deallocate promoted pawns.
		if (it->getPromotedPiece() != NULL)
			delete it->getMovedPiece();
	}
}

void Board::addPiece(Piece* piece) {

	// Check if the piece added is a King.
	if (piece->getCharacter() == 'k')
		bKing = piece;
	else if (piece->getCharacter() == 'K')
		wKing = piece;

	// Add the piece to the array.
	int index = convertToIndex(piece->getRow(), piece->getCol());
	if (pieces[index] != NULL)
		delete pieces[index];
	pieces[index] = piece;
}

void Board::addDefaultPieces() {

	// White.
	Rook* r1 = new Rook(1, 1, 1);
	Knight* n1 = new Knight(1, 2, 1);
	Bishop* b1 = new Bishop(1, 3, 1);
	Queen* q = new Queen(1, 5, 1);
	Bishop* b2 = new Bishop(1, 6, 1);
	Knight* n2 = new Knight(1, 7, 1);
	King* k = new King(1, 4, 1);
	Rook* r2 = new Rook(1, 8, 1);
	Pawn* p1 = new Pawn(2, 1, 1);
	Pawn* p2 = new Pawn(2, 2, 1);
	Pawn* p3 = new Pawn(2, 3, 1);
	Pawn* p4 = new Pawn(2, 4, 1);
	Pawn* p5 = new Pawn(2, 5, 1);
	Pawn* p6 = new Pawn(2, 6, 1);
	Pawn* p7 = new Pawn(2, 7, 1);
	Pawn* p8 = new Pawn(2, 8, 1);

	// Black.
	Rook* R1 = new Rook(8, 1, 2);
	Knight* N1 = new Knight(8, 2, 2);
	Bishop* B1 = new Bishop(8, 3, 2);
	King* K = new King(8, 4, 2);
	Queen* Q = new Queen(8, 5, 2);
	Bishop* B2 = new Bishop(8, 6, 2);
	Knight* N2 = new Knight(8, 7, 2);
	Rook* R2 = new Rook(8, 8, 2);
	Pawn* P1 = new Pawn(7, 1, 2);
	Pawn* P2 = new Pawn(7, 2, 2);
	Pawn* P3 = new Pawn(7, 3, 2);
	Pawn* P4 = new Pawn(7, 4, 2);
	Pawn* P5 = new Pawn(7, 5, 2);
	Pawn* P6 = new Pawn(7, 6, 2);
	Pawn* P7 = new Pawn(7, 7, 2);
	Pawn* P8 = new Pawn(7, 8, 2);

	// Add pieces.
	addPiece(r1);
	addPiece(n1);
	addPiece(b1);
	addPiece(k);
	addPiece(q);
	addPiece(b2);
	addPiece(n2);
	addPiece(r2);
	addPiece(p1);
	addPiece(p2);
	addPiece(p3);
	addPiece(p4);
	addPiece(p5);
	addPiece(p6);
	addPiece(p7);
	addPiece(p8);

	addPiece(R1);
	addPiece(N1);
	addPiece(B1);
	addPiece(K);
	addPiece(Q);
	addPiece(B2);
	addPiece(N2);
	addPiece(R2);
	addPiece(P1);
	addPiece(P2);
	addPiece(P3);
	addPiece(P4);
	addPiece(P5);
	addPiece(P6);
	addPiece(P7);
	addPiece(P8);
}

void Board::addPiecesFromFile(ifstream& stream) {
	char row = -1;
	char col = -1;
	char ch = '\0';
	char moved = -1;

	while(1) {
		stream.read(&row, sizeof(char));
		stream.read(&col, sizeof(char));
		stream.read(&ch, sizeof(char));
		stream.read(&moved, sizeof(char));

		if (stream.eof())
			break;

		Piece* p;
		int player = isupper(ch) ? 1 : 2;
		if (ch == 'R' || ch == 'r')
			p = new Rook(row, col, player);
		else if (ch == 'N' || ch == 'n')
			p = new Knight(row, col, player);
		else if (ch == 'B' || ch == 'b')
			p = new Bishop(row, col, player);
		else if (ch == 'K' || ch == 'k')
			p = new King(row, col, player);
		else if (ch == 'Q' || ch == 'q')
			p = new Queen(row, col, player);
		else if (ch == 'P' || ch == 'p')
			p = new Pawn(row, col, player);

		p->setMoved(moved == 1);
		addPiece(p);

	}
}

bool Board::movePiece(int srcRow, int srcCol, int dstRow, int dstCol) {
	int srcIndex = convertToIndex(srcRow, srcCol);
	int dstIndex = convertToIndex(dstRow, dstCol);

	Piece* srcP = pieces[srcIndex];
	Piece* dstP = pieces[dstIndex];

	if (srcP != NULL) {

		// Check if a pawn was promoted in this move.
		bool promoteMove = false;
		if (dynamic_cast<Pawn*> (srcP)) {
			if (dstRow == 8 && srcP->getPlayer() == 1) {
				promoteMove = true;
			}
			else if (dstRow == 1 && srcP->getPlayer() == 2) {
				promoteMove = true;
			}
		}

		// Create the new queen if necessary.
		Queen* q = NULL;
		if (promoteMove)
			q = new Queen(dstRow, dstCol, srcP->getPlayer());

		// Add the move to the vector.
		MoveData mData(srcP, dstP, q, srcRow, srcCol, dstRow, dstCol);
		moves.push_back(mData);

		if (q == NULL) {
			srcP->move(dstRow, dstCol);
			pieces[dstIndex] = srcP;
		}
		else
			pieces[dstIndex] = q;
		pieces[srcIndex] = NULL;
		currentMove++;

		// Revert the move if the king is not safe.
		if (!isKingSafe(srcP->getPlayer())) {
			revertLastMove();
			return false;
		}
		return true;
	}
	return false;
}

void Board::revertMove(MoveData mData) {
	int srcIndex = convertToIndex(mData.getSourceRow(), mData.getSourceCol());
	int dstIndex = convertToIndex(mData.getDestRow(), mData.getDestCol());

	mData.getMovedPiece()->move(mData.getSourceRow(), mData.getSourceCol());
	mData.getMovedPiece()->setMoved(mData.getPieceHadMoved());

	pieces[srcIndex] = mData.getMovedPiece();
	pieces[dstIndex] = mData.getAttackedPiece();

	currentMove--;
}

void Board::revertLastMove() {
	if (moves.size() > 0) {
		MoveData data = moves[moves.size() - 1];
		revertMove(data);
		moves.pop_back();
	}
}

void Board::goBack() {
	if (currentMove > 0) {
		MoveData mData = moves[currentMove - 1];
		
		int srcIndex = convertToIndex(mData.getSourceRow(), mData.getSourceCol());
		int dstIndex = convertToIndex(mData.getDestRow(), mData.getDestCol());

		mData.getMovedPiece()->move(mData.getSourceRow(), mData.getSourceCol());
		mData.getMovedPiece()->setMoved(mData.getPieceHadMoved());

		pieces[srcIndex] = mData.getMovedPiece();
		pieces[dstIndex] = mData.getAttackedPiece();

		currentMove--;
	}
}

void Board::goForward() {
	if (currentMove < moves.size()) {
		MoveData mData = moves[currentMove];
		
		int srcIndex = convertToIndex(mData.getSourceRow(), mData.getSourceCol());
		int dstIndex = convertToIndex(mData.getDestRow(), mData.getDestCol());

		Piece* srcP = pieces[srcIndex];

		srcP->move(mData.getDestRow(), mData.getDestCol());
		if (mData.getPromotedPiece() == NULL)
			pieces[dstIndex] = srcP;
		else
			pieces[dstIndex] = mData.getPromotedPiece();
		pieces[srcIndex] = NULL;

		currentMove++;
	}
}

bool Board::isAttacked(int row, int col, int byPlayer) {
	for (int i = 0; i < 64; i++) {
		Piece* p = pieces[i];
		if (p == NULL)
			continue;
		
		if (p->getPlayer() == byPlayer) {
			// Pawns have different rules for attacking and moving.
			Pawn* pawn = dynamic_cast<Pawn*>(p);
			if (pawn) {
				if (pawn->checkAttack(row, col))
					return true;
			}
			else if (p->checkMove(row, col) && p->checkMove2(row, col, *this))
				return true;
		}
	}
	return false;
}

bool Board::isKingSafe(int which) {
	if (which == 1)
		return !isAttacked(wKing->getRow(), wKing->getCol(), 2);
	return !isAttacked(bKing->getRow(), bKing->getCol(), 1);
}

bool Board::areThereAvailableMoves(int player) {

	for (int i = 0; i < 64; i++) {
		Piece* p = pieces[i];
		if (p == NULL || p->getPlayer() != player)
			continue;
		
		vector<Cell> availMoves = p->getAvailableCells(*this);
		vector<Cell>::iterator it;
		for (it = availMoves.begin(); it != availMoves.end(); it++) {
			bool success = movePiece(p->getRow(), p->getCol(), it->getRow(), it->getCol());
			
			// If the move was successful, revert it and return true.
			if (success) {
				revertLastMove();
				return true;
			}
		}
	}

	// If this point is reached, no move is available.
	return false;
}

int Board::convertToIndex(int row, int col) {
    return (row-1) * 8 + (col-1);
}

Piece* Board::getPieceAt(int row, int col) {
	if (row < 1 || row > 8 || col < 1 || col > 8)
		return NULL;
    return pieces[convertToIndex(row, col)];
}

void Board::saveBoardToFile(ofstream& stream) {
	for (int i = 0; i < 64; i++) {
		Piece* p = pieces[i];
		if (p != NULL) {

			// Save the piece data in variables.
			char row = p->getRow();
			char col = p->getCol();
			char ch = p->getCharacter();
			char mv = p->getMoved() ? 1 : 0;

			// Save the data.
			stream.write(&row, sizeof(char));
			stream.write(&col, sizeof(char));
			stream.write(&ch, sizeof(char));
			stream.write(&mv, sizeof(char));
		}
	}
}

void Board::printBoard(int selectedRow, int selectedCol, const vector<Cell>& highlightedCells) {
    
	// Color codes.
    const string WHITE = "\033[30;47m";
    const string BLACK = "\033[37;40m";
    const string BLUE = "\033[37;44m";
    const string GREEN = "\033[37;42m";
    const string DEFAULT = "\033[0m";

    cout << "       a     b     c     d     e     f     g     h" << endl << endl;
    
    for (int j = 1; j <= CELL_SIZE_Y * 8; j++) {
        for (int i = 0; i <= CELL_SIZE_X * 8; i++) {

            // Get the coordinates of the current cell.
			int cellRow = 9 - ((j-1)/CELL_SIZE_Y + 1);
            int cellCol = i == 0 ? -1 : (i-1)/CELL_SIZE_X + 1;
            
            if (i == 0) {
                if ( (j-2) % 3 == 0)
                    cout << 8 - (j-2) / 3 << "   ";
                else
                    cout << "    ";
            }
            else {
                // Select color.
                if (cellCol == selectedCol && cellRow == selectedRow)
                    cout << BLUE;
                else if (find(highlightedCells.begin(), highlightedCells.end(), Cell(cellRow, cellCol)) != highlightedCells.end()) {
                    cout << GREEN;
                }
                else {
                    if (cellCol % 2 == cellRow % 2)
                        cout << WHITE;
                    else
                        cout << BLACK;
                }

                // Draw.
				if ((i-10) % CELL_SIZE_X == 0 && (j-2) % CELL_SIZE_Y == 0) {
					Piece* p = getPieceAt(cellRow, cellCol);
					if (p != NULL)
						cout << p->getCharacter();
					else
						cout << " ";
				}
				else
                	cout << " ";

				// Restore color.
                cout << DEFAULT;

                // Add the numbers at the end.
                if (i == CELL_SIZE_X * 8 && (j-2) % 3 == 0)
                    cout << "   " << 8 - (j-2) / 3;
            }
        }
        cout << endl;
    }

    cout << endl << "       a     b     c     d     e     f     g     h" << endl;
}

void Board::clear() {
    cout << "\033c";
}
