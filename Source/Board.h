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

struct Scores {
    int black = 2;
    int white = 2;
};

class BoardChangeListener
{
public:
    virtual void BoardChanged(Scores scores, bool needToReset) = 0;
};


class BoardChangeListenerList : public std::vector<BoardChangeListener*>
{
public:
    void notifyAllListeners(Scores score) 
    {
        for (std::vector<BoardChangeListener*>::iterator it = begin() ; it != end(); ++it)
            (*it)->BoardChanged(score, false);
    }
};

class Board
{
public:
	Board();
	~Board();

    void initBoard();

    Square::SquareState placeChip(SquareCoordinates point);
    Square::SquareState getSquareState(SquareCoordinates point);

    int getBoardSize()      { return BOARD_SIZE; }
    Scores getScores()      { return scores; }

    void addBoardBoardChangeListener(BoardChangeListener* listener){ boardChangeListenerList.push_back(listener); }

private:
    int search(SquareCoordinates coordinates, int searchDirR, int searchDirC);
    bool updateSquaresToTurn(std::vector<Square*> &squaresToTurn_OUT, Square &curSquare);
    
    BoardChangeListenerList boardChangeListenerList;

    bool isBlackTurn;
	Square board[BOARD_SIZE][BOARD_SIZE];

    Scores scores;
};