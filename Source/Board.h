/*
==============================================================================
Reversi!

Copyright (C) 2017  BMP4

Developer: Vincent Berthiaume

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
==============================================================================
*/

#pragma once

#ifndef BOARD_SIZE
#define BOARD_SIZE 8
#endif

#include "Square.h"
#include <vector>


class Board
{
public:
	Board();
	~Board();

    void initBoard();

    Square::SquareState placeChip(SquareCoordinates point);

    Square::SquareState getSquareState(SquareCoordinates point);

    int getBoardSize()  { return BOARD_SIZE; }
    
    bool isChanged()    { return changed; }

    void clearIsChanged() { changed = false; }

    

private:
    //void searchUp(SquareCoordinates coordinate);

    int search(SquareCoordinates coordinates, int searchDirR, int searchDirC);
    bool updateSquaresToTurn(std::vector<Square*> &squaresToTurn_OUT, Square &curSquare);

    bool isBlackTurn;
    bool changed;
	Square board[BOARD_SIZE][BOARD_SIZE];
};