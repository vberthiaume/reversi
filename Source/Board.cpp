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

#include "Board.h"
#include "assert.h"
#include <vector>

Board::Board()
    : changed(false)
{
    initBoard();
}

Board::~Board()
{
}

void Board::initBoard()
{
    isBlackTurn = true;

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = Square(i, j, Square::empty);

    //need an even number of squares
    assert(BOARD_SIZE % 2 == 0);
    int middle = BOARD_SIZE / 2;

    //put starting pieces
    board[middle][middle].state         = Square::black;
    board[middle - 1][middle - 1].state = Square::black;
    board[middle - 1][middle].state     = Square::white;
    board[middle][middle - 1].state     = Square::white;

    changed = true;
}

Square::SquareState Board::placeChip(SquareCoordinates coordinate)
{
    Square &square = board[coordinate.x][coordinate.y];

    if (square.state == Square::empty)
    {
        //based on square position, search in each of 8 directions for:
        // need to first find a square of the opposite color, if so add this square to a vector of chips to turn else return false
        // continue adding squares of opposite color to vector
        // if we find a chip of our color, 

        // a square of the same color or an empty one
        //if you get an empt
        //attempt to search for another square of the same color in all 8 directions

        searchUp(coordinate);




        square.state = isBlackTurn ? Square::black : Square::white;
        isBlackTurn = !isBlackTurn;
        changed = true;
    }
     
    return square.state;
}

void Board::searchUp(SquareCoordinates coordinates)
{
     Square::SquareState currentPlayer = isBlackTurn ? Square::black : Square::white;
    Square::SquareState otherPlayer   = isBlackTurn ? Square::white : Square::black;

    //bool foundOppositeColour = false;
    //bool foundSameColour = false;
    std::vector<Square*> squaresToTurn;
    
    for (int i = coordinates.x-1; i > 0; --i)
    {
        Square &curSquare = board[i][coordinates.y];
        if (curSquare.getState() == otherPlayer)
            squaresToTurn.push_back(&board[i][coordinates.y]);
        else if (curSquare.getState() == currentPlayer && squaresToTurn.size() > 0)
        {
            for (auto square : squaresToTurn)
                square->setState(currentPlayer);
            changed = true;
            return;
        }
        else if (curSquare.getState() == Square::empty)
            return;
    }
}

Square::SquareState Board::getSquareState(SquareCoordinates coordinates)
{
    return board[coordinates.x][coordinates.y].state;
}