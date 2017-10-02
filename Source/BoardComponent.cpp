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
    startTimer(100);
    setSize(600, 600);
    for (int i = 0; i < board.getBoardSize(); ++i)
    {
        for (int j = 0; j < board.getBoardSize(); ++j)
        {
            SquareComponent &squareComp = squareComponents[i][j];
            squareComp.setState(Square::empty);
            squareComp.setCoordinates(i, j);
            squareComp.addListener(this);
            addAndMakeVisible(squareComp);
        }
    }
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
    for (int i = 0; i < board.getBoardSize(); ++i)
        for (int j = 0; j < board.getBoardSize(); ++j)
        {
            SquareCoordinates coordinates(i, j);
            squareComponents[i][j].setState(board.getSquareState(coordinates));
            squareComponents[i][j].repaint();
        }
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

    for (int i = 0; i < board.getBoardSize(); ++i)
        for (int j = 0; j < board.getBoardSize(); ++j)
            grid.items.add(squareComponents[i][j]);

    grid.performLayout(getLocalBounds());
}

void BoardComponent::buttonClicked(Button* buttonThatWasClicked)
{
    //TODO use a map or something more intelligent
    for (int i = 0; i < board.getBoardSize(); ++i)
        for (int j = 0; j < board.getBoardSize(); ++j)
        {
            SquareComponent &squareComp = squareComponents[i][j];
            if (buttonThatWasClicked == &squareComp)
            {
                squareComp.setState(board.placeChip(squareComp.getCoordinates()));
                return;
            }
        }
    
}