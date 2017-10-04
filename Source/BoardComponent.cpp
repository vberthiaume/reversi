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

#include "BoardComponent.h"
#include <algorithm>
#include <string>

BoardComponent::BoardComponent(Board* p_board)
    : board(p_board)
{
    int squareSize = 75;
    int gapSize = 2;
    int squareCount = board->getBoardSize();
    int sideSize = squareCount*squareSize + (squareCount-1)*gapSize;
    setSize(sideSize, sideSize);

    //build the board
    for (int r = 0; r < squareCount; ++r)
        for (int c = 0; c < squareCount; ++c)
        {
            if (r == 0 && c == 0)
                addSquareComponent(r, c, squareSize, 0, 0);
            else if (r == 0)
                addSquareComponent(r, c, squareSize, 0, gapSize);
            else if (c == 0)
                addSquareComponent(r, c, squareSize, gapSize, 0);
            else
                addSquareComponent(r, c, squareSize, gapSize, gapSize);
        }
    
    //sort in order to use binary search to resolve which squareComponent was clicked on
    std::sort(squareComponents.begin(), squareComponents.end());
}

void BoardComponent::addSquareComponent(int r, int c, int squareSize, int rGapSize, int cGapSize)
{
    SquareComponent *squareComp = new SquareComponent(Square::empty, SquareCoordinates(r, c));
    squareComp->addListener(this);
    squareComponents.add(squareComp);
    squareComp->setBounds(c*(squareSize + cGapSize), r*(squareSize + rGapSize), squareSize, squareSize);
    addAndMakeVisible(squareComp);
}

void BoardComponent::BoardChanged(Scores /*scores*/, bool /*needToReset*/)
{
    updateWholeBoard();
}

void BoardComponent::updateWholeBoard()
{
    for (SquareComponent* squareComp : squareComponents)
    {
        squareComp->setState(board->getSquareState(squareComp->getCoordinates()));
        squareComp->repaint();
    }
}

void BoardComponent::paint(Graphics& g) 
{
    g.fillAll(Colours::black);
}

void BoardComponent::buttonClicked(Button* buttonThatWasClicked)
{
    SquareComponent* squareComp = reinterpret_cast<SquareComponent*>(buttonThatWasClicked);

    if (std::binary_search(squareComponents.begin(), squareComponents.end(), squareComp))
        squareComp->setState(board->placeChip(squareComp->getCoordinates()));
    else
        jassertfalse; //buttonThatWasClicked not in squareComponents!
}