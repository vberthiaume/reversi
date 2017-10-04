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
{
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

    updatePossibleMoves();

    boardChangeListenerList.notifyAllListeners(BoardChangeEvent());
}

Square::SquareState Board::placeChip(SquareCoordinates coordinate)
{
    Square &square = board[coordinate.r][coordinate.c];

    if (square.state == Square::empty)
    {
        int numberTurned = searchAllDirections(isBlackTurn, coordinate, false);
        if (numberTurned > 0)
        {
            if (isBlackTurn)
            {
                square.state = Square::black;
                scores.black += numberTurned + 1;
                scores.white -= numberTurned;
            }
            else
            {
                square.state = Square::white;
                scores.white += numberTurned + 1;
                scores.black -= numberTurned;
            }
            isBlackTurn = !isBlackTurn;
            BoardChangeEvent event(scores, isBlackTurn, false, 0, 0);
            boardChangeListenerList.notifyAllListeners(event);
        }
    }
    
    return square.state;
}

void Board::updatePossibleMoves()
{
    //possibleMoves.black = searchAllDirections(true, coordinate, false);
    //possibleMoves.white = searchAllDirections(false, coordinate, false);
}

size_t Board::searchAllDirections(bool curIsBlack, SquareCoordinates coordinate, bool justCheckForAtLeastOnePossibility)
{
    size_t numberTurned = 0;
    for(int deltaR = -1; deltaR <= 1; ++deltaR)
    {
        for(int deltaC = -1; deltaC <= 1; ++deltaC)
        {
            if(deltaR == 0 && deltaC == 0)
                continue;
            numberTurned += searchOneDirection(curIsBlack, coordinate, deltaR, deltaC, justCheckForAtLeastOnePossibility);
        }
    }
    return numberTurned;
}

size_t Board::searchOneDirection(bool curIsBlack, SquareCoordinates coordinates, int searchDirR, 
                                 int searchDirC, bool justCheckForAtLeastOnePossibility)
{
    std::vector<Square*> squaresToTurn;
    
    //searching in diagonals
    if (searchDirR != 0 && searchDirC != 0)
    {
        int r = coordinates.r + searchDirR;
        int c = coordinates.c + searchDirC;
        while(r > 0 && r < BOARD_SIZE && c > 0 && c < BOARD_SIZE)
        { 
            if (addSquaresToTurn(curIsBlack, squaresToTurn, board[r][c], justCheckForAtLeastOnePossibility))
                return squaresToTurn.size();
            r += searchDirR;
            c += searchDirC;
        }
    }

    //searching in the same row
    else if (searchDirR == 0 && searchDirC != 0)
    {
        for (int c = coordinates.c + searchDirC; c > 0 && c < BOARD_SIZE; c += searchDirC)
            if (addSquaresToTurn(curIsBlack, squaresToTurn, board[coordinates.r][c], justCheckForAtLeastOnePossibility))
                return squaresToTurn.size();
    }

    //searching in the same column
    else if (searchDirR != 0 && searchDirC == 0)
    {
        for (int r = coordinates.r + searchDirR; r > 0 && r < BOARD_SIZE; r += searchDirR)
            if (addSquaresToTurn(curIsBlack, squaresToTurn, board[r][coordinates.c], justCheckForAtLeastOnePossibility))
                return squaresToTurn.size();
    }

    //we've hit the edge of the board without turning anything
    return 0;
}

bool Board::addSquaresToTurn(bool curIsBlack, std::vector<Square*> &squaresToTurn_OUT, Square &curSquare, bool justCheckForAtLeastOnePossibility)
{
    bool doneSearching;
    Square::SquareState currentPlayer = curIsBlack ? Square::black : Square::white;
    Square::SquareState otherPlayer   = curIsBlack ? Square::white : Square::black;

    if (curSquare.getState() == otherPlayer)
    {
        squaresToTurn_OUT.push_back(&curSquare);
        doneSearching = false;
    }
    else if (curSquare.getState() == currentPlayer && squaresToTurn_OUT.size() > 0)
    {
        if (!justCheckForAtLeastOnePossibility)
        {
            for(auto square : squaresToTurn_OUT)
                square->setState(currentPlayer);
        }
        doneSearching = true;
    }
    else 
    {
        squaresToTurn_OUT.clear();
        doneSearching = true;
    }
    return doneSearching;
}

Square::SquareState Board::getSquareState(SquareCoordinates coordinates)
{
    return board[coordinates.r][coordinates.c].state;
}