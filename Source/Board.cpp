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
//#include "Square.h"
#include "assert.h"

Board::Board()
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
        {
            board[i][j] = Square(i, j, Square::empty);
        }

    //need an even number of squares
    assert(BOARD_SIZE % 2 == 0);
    int middle = BOARD_SIZE / 2;

    //put starting pieces
    board[middle][middle].state = Square::black;
    board[middle - 1][middle - 1].state = Square::black;
    board[middle - 1][middle].state = Square::white;
    board[middle][middle - 1].state = Square::white;
}

//Square::SquareState Board::PlaceColour(Square &square, Square::SquareState colour)
//{
//	bool attemptBlack;
//	switch (colour)
//	{
//	case Square::black:
//		attemptBlack = true;
//		break;
//	case Square::white:
//		attemptBlack = false;
//		break;
//	case Square::empty:
//	default:
//		assert(false);
//		return false;
//	}
//
//	//based on square position, search in each of 8 directions for:
//		// need to first find a square of the opposite color, if so add this square to a vector of chips to turn else return false
//		// continue adding squares of opposite color to vector
//		// if we find a chip of our color, 
//
//		// a square of the same color or an empty one
//	//if you get an empt
//	//attempt to search for another square of the same color in all 8 directions
//	return true;
//}

Square::SquareState Board::placeChip(SquareCoordinates point)
{
    Square &square = board[point.x][point.y];

    if (square.state == Square::empty)
    {
        //based on square position, search in each of 8 directions for:
        // need to first find a square of the opposite color, if so add this square to a vector of chips to turn else return false
        // continue adding squares of opposite color to vector
        // if we find a chip of our color, 

        // a square of the same color or an empty one
        //if you get an empt
        //attempt to search for another square of the same color in all 8 directions
        Square::SquareState state = isBlackTurn ? Square::black : Square::white;
        isBlackTurn = !isBlackTurn;
        return state;
    }
    else
        return Square::empty;
}

//bool Board::PlaceWhite(SquareCoordinates point)
//{
//    Square &square = board[point.x][point.y];
//	if (square.state == Square::empty)
//		return PlaceColour(square, Square::white);
//	else
//		return false;
//}
//
//bool Board::PlaceBlack(SquareCoordinates point)
//{
//    Square &square = board[point.x][point.y];
//	if (square.state == Square::empty)
//		return PlaceColour(square, Square::black);
//	else
//		return false;
//}

//Square::SquareState Board::placeChip(SquareCoordinates point)
//{
//    Square &square = board[point.x][point.y];
//    if (square.state == Square::empty)
//        return isBlackTurn ? PlaceColour(square, Square::black) : PlaceColour(square, Square::white);
//    else
//        return Square::empty;
//
//}