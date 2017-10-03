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

BoardComponent::BoardComponent()
{
    startTimer(100);
    setSize(600, 600);
    
    Grid grid;
    grid.rowGap = 2_px;
    grid.columnGap = 2_px;
    
    //build the board
    for (int r = 0; r < board.getBoardSize(); ++r)
    {
        for (int c = 0; c < board.getBoardSize(); ++c)
        {
            SquareComponent *squareComp = new SquareComponent(Square::empty, SquareCoordinates(r, c));
            squareComp->addListener(this);
            squareComponents.add(squareComp);
            addAndMakeVisible(squareComp);
        }

        grid.templateRows.add(Grid::TrackInfo(1_fr));
        grid.templateColumns.add(Grid::TrackInfo(1_fr));
    }

    //place the squares component in a grid
    for (SquareComponent *squareComp : squareComponents)
        grid.items.add(squareComp);
    grid.performLayout(getLocalBounds());

    //sort in order to use binary search to resolve which squareComponent was clicked on
    std::sort(squareComponents.begin(), squareComponents.end());
}

void BoardComponent::timerCallback()
{
    if (board.isChanged())
    {
        updateWholeBoard();
        board.clearIsChanged();
    }
}

void BoardComponent::updateWholeBoard()
{
    for (SquareComponent* squareComp : squareComponents)
    {
        squareComp->setState(board.getSquareState(squareComp->getCoordinates()));
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
        squareComp->setState(board.placeChip(squareComp->getCoordinates()));
    else
        jassertfalse; //buttonThatWasClicked not in squareComponents!
}