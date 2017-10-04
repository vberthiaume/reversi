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
#define BOARD_SIZE 4
#endif

#include "Square.h"
#include <vector>

struct Scores {
    size_t black = 2;
    size_t white = 2;
};

struct PossibleMoves {
    std::vector<SquareCoordinates> black;
    std::vector<SquareCoordinates> white;

    bool blackCanPlay;
    bool whiteCanPlay;
};

struct BoardChangeEvent
{
    BoardChangeEvent() {}

    BoardChangeEvent(Scores p_scores, bool p_isBlackTurn, bool p_needToReset, 
                    int p_numBlackMovesRemaining, int p_numWhiteMovesRemaining)
        : scores (p_scores)
        , isBlackTurn (p_isBlackTurn)
        , needToReset(p_needToReset)
        , numBlackMovesRemaining(p_numBlackMovesRemaining)
        , numWhiteMovesRemaining(p_numWhiteMovesRemaining)
    {}

    Scores scores;
    bool isBlackTurn = true;
    bool needToReset = false;
    int numBlackMovesRemaining = 0;
    int numWhiteMovesRemaining = 0;
};

class BoardChangeListener
{
public:
    virtual void BoardChanged(const BoardChangeEvent &event) = 0;
};


class BoardChangeListenerList : public std::vector<BoardChangeListener*>
{
public:
    void notifyAllListeners(const BoardChangeEvent &event) 
    {
        for (std::vector<BoardChangeListener*>::iterator it = begin() ; it != end(); ++it)
            (*it)->BoardChanged(event);
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
    size_t searchAllDirections(bool curIsBlack, SquareCoordinates coordinate, bool actuallyTurnSquares);
    size_t searchOneDirection(bool curIsBlack, SquareCoordinates coordinates, int searchDirR, int searchDirC, bool actuallyTurnSquares);
    bool addSquaresToTurn(bool isBlackTurn, std::vector<Square*> &squaresToTurn_OUT, Square &curSquare, bool justCheckForAtLeastOnePossibility);
    void updatePossibleMoves();

    bool isBlackTurn;
	Square board[BOARD_SIZE][BOARD_SIZE];
    Scores scores;
    PossibleMoves possibleMoves;
    BoardChangeListenerList boardChangeListenerList;
};