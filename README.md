# Linux terminal chess

A 2-player chess game playable on the linux terminal.  
White pieces: upper-case letters  
Black pieces: lower-case letters

## Compilation

The included make file can be used to compile the project into an executable. Alternatively, it may also be compiled directly with g++ with the command:  
>`g++ main.cpp Board.cpp Piece.cpp Game.cpp Pawn.cpp Cell.cpp King.cpp Queen.cpp Rook.cpp Bishop.cpp Knight.cpp MoveData.cpp`

## Key features

* Each time the blacks make a move, the state of the board is automatically saved in a file called *lastgame*. The user is asked if he wishes to load this, or any other, file at the beginning.
* There is support for going back and forward one move, but it is only used for viewing. The actual move cannot be recalled.

## Controls

* **Q**: Exit game
* **B**: Go back one move
* **F**: Go forward one move
* **Arrows**: Move selection
* **Enter**: Select piece / confirm move

## Unimplemented features

* En passant
* Castling
* Proper pawn promotion (pawns are always promoted to queens)
* Some of the more elaborate stalemate states