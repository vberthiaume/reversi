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

BoardComponent::BoardComponent()
{
    for (int i = 0; i < board.getBoardSize(); ++i)
        for (int j = 0; j < board.getBoardSize(); ++j)
            addSquare(Square::SquareState::empty, i, j);

    setSize(600, 600);
}

void BoardComponent::paint(Graphics& g) 
{
    g.fillAll(Colours::black);
}

void BoardComponent::resized() 
{
    Grid grid;

    grid.rowGap     = 5_px;
    grid.columnGap  = 5_px;

    for (int i = 0; i < board.getBoardSize(); ++i)
    {
        grid.templateRows.add(Grid::TrackInfo(1_fr));
        grid.templateColumns.add(Grid::TrackInfo(1_fr));
    }

    for (auto & squareComp : squareComponents)
        grid.items.add(squareComp);

    grid.performLayout(getLocalBounds());
}

void BoardComponent::buttonClicked(Button* buttonThatWasClicked)
{
    //TODO use a map or something more intelligent
    for (SquareComponent *squareComp : squareComponents)
    {
        if (buttonThatWasClicked == squareComp)
        {
            squareComp->setState(board.placeChip(squareComp->getCoordinates()));
        }
    }
}