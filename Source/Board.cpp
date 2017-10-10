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
#include <iostream>

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
    scores = Scores();

    boardChangeListenerList.notifyAllListeners(BoardChangeEvent());
}

Square::SquareState Board::attemptToPlaceDisk(SquareCoordinates coordinate)
{
    Square &square = board[coordinate.r][coordinate.c];

    //TODO: need to check this move is in possibleMoves, instead of searching all directions
    //size_t numberTurned = searchAllDirections(isBlackTurn, coordinate, false);
    int numberTurned = isBlackTurn ? possibleMoves.black[coordinate].size() : possibleMoves.white[coordinate].size();
    if (numberTurned > 0)
    {
        placeDisk(square, numberTurned);
            
        //change turn
        isBlackTurn = !isBlackTurn;
            
        //send event
        BoardChangeEvent event(scores, isBlackTurn, false, 0, 0);
        boardChangeListenerList.notifyAllListeners(event);
#if TEST_MODE
        //automatically fill the board until game over
        fillBoard();
#else
        //update list of possible moves
        updatePossibleMoves();
#endif
    }
    return square.state;
}

void Board::placeDisk(Square &square, size_t numberTurned)
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
}

bool Board::updatePossibleMoves()
{
    searchWholeBoard();

    //no one can play, game over
    if (!possibleMoves.blackCanPlay && !possibleMoves.whiteCanPlay)
    {
        boardChangeListenerList.notifyAllListeners(BoardChangeEvent(scores, isBlackTurn, true, 0, 0));
        return false;
    }
    //current player can't play, go back to other player
    else if (isBlackTurn && !possibleMoves.blackCanPlay || !isBlackTurn && !possibleMoves.whiteCanPlay)
    {
        isBlackTurn = !isBlackTurn;
        boardChangeListenerList.notifyAllListeners(BoardChangeEvent(scores, isBlackTurn, false, 0, 0));
    }

    return true; 
}

void Board::searchWholeBoard()
{
    PossibleMoves possibleMovesTemp;
    
    for(int r = 0; r < BOARD_SIZE; ++r)
        for (int c = 0; c < BOARD_SIZE; ++c)
            if(board[r][c].state == Square::empty)
                searchAllDirections(SquareCoordinates(r, c), possibleMovesTemp);

//need to lock this
    {
        possibleMoves = possibleMovesTemp;
    }
}

#if TEST_MODE
void Board::fillBoard()
{
    while(updatePossibleMoves())
    {
        bool placedDisk = false;
        for(int r = 0; !placedDisk && r < BOARD_SIZE; ++r)
        {
            for(int c = 0; !placedDisk && c < BOARD_SIZE; ++c)
            {
                int toTurn = searchAllDirections(isBlackTurn, SquareCoordinates(r, c), false);
                if(toTurn > 0)
                {
                    placeDisk(board[r][c], toTurn);
                    isBlackTurn = !isBlackTurn;
                    boardChangeListenerList.notifyAllListeners(BoardChangeEvent(scores, isBlackTurn, false, 0, 0));
                    placedDisk = true;
                }
            }
        }
    }
}
#endif

void Board::searchAllDirections(SquareCoordinates coordinate, PossibleMoves &possibleMoves_OUT)
{
    if(board[coordinate.r][coordinate.c].state != Square::empty)
        return;

    for(int deltaR = -1; deltaR <= 1; ++deltaR)
    {
        for(int deltaC = -1; deltaC <= 1; ++deltaC)
        {
            if(deltaR == 0 && deltaC == 0)
                continue;
            searchOneDirection(true, coordinate, deltaR, deltaC, possibleMoves_OUT);
            searchOneDirection(false, coordinate, deltaR, deltaC, possibleMoves_OUT);
        }
    }
}

void Board::searchOneDirection(bool curIsBlack, SquareCoordinates coordinates, int searchDirR,  
                               int searchDirC, PossibleMoves &possibleMoves_OUT)
{
    SquareCoordinates originalCoordinates = coordinates;
    //searching in diagonals
    if (searchDirR != 0 && searchDirC != 0)
    {
        int r = coordinates.r + searchDirR;
        int c = coordinates.c + searchDirC;
        while(r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE)
        { 
            if(addSquaresToTurn(curIsBlack, originalCoordinates, board[r][c], possibleMoves_OUT))
                return;
            r += searchDirR;
            c += searchDirC;
        }
    }

    //searching in the same row
    else if (searchDirR == 0 && searchDirC != 0)
    {
        for (int c = coordinates.c + searchDirC; c >= 0 && c < BOARD_SIZE; c += searchDirC)
            if (addSquaresToTurn(curIsBlack, originalCoordinates, board[coordinates.r][c], possibleMoves_OUT))
                return;
    }

    //searching in the same column
    else if (searchDirR != 0 && searchDirC == 0)
    {
        for (int r = coordinates.r + searchDirR; r >= 0 && r < BOARD_SIZE; r += searchDirR)
            if (addSquaresToTurn(curIsBlack, originalCoordinates, board[r][coordinates.c], possibleMoves_OUT))
                return;
    }

    //we've hit the edge of the board without turning anything
    return;
}

bool Board::addSquaresToTurn(bool curIsBlack, SquareCoordinates originalCoordinates, 
                             Square &curSquare, PossibleMoves &possibleMoves_OUT)
{
    bool doneSearching;
    Square::SquareState currentPlayer;
    std::vector<SquareCoordinates>*  currentPlayerListToTurn;
    Square::SquareState otherPlayer;
    if (curIsBlack)
    {
        currentPlayer           = Square::black;
        currentPlayerListToTurn = &possibleMoves_OUT.black[originalCoordinates];
        otherPlayer             = Square::white;
    }
    else
    {
        currentPlayer = Square::white;
        currentPlayerListToTurn = &possibleMoves_OUT.white[originalCoordinates];
        otherPlayer   = Square::black;
    }

    if (curSquare.getState() == otherPlayer)
    {
        currentPlayerListToTurn->push_back(curSquare.coordinates);
        doneSearching = false;
    }
    else if (curSquare.getState() == currentPlayer && currentPlayerListToTurn->size() > 0)
    {
        doneSearching = true;
    }
    else 
    {
        currentPlayerListToTurn->clear();
        doneSearching = true;
    }
    return doneSearching;
}

Square::SquareState Board::getSquareState(SquareCoordinates coordinates)
{
    return board[coordinates.r][coordinates.c].state;
}