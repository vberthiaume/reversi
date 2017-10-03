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

    for (int r = 0; r < board.getBoardSize(); ++r)
    {
        for (int c = 0; c < board.getBoardSize(); ++c)
        {
            /*SquareComponent &squareComp = squareComponents[i][j];
            squareComp.setState(Square::empty);
            squareComp.setCoordinates(i, j);
            squareComp.addListener(this);
            addAndMakeVisible(squareComp);*/
            SquareCoordinates coordinates(r, c);
            SquareComponent *squareComp = new SquareComponent(Square::empty, coordinates);
            squareComp->addListener(this);
            squareComponents.add(squareComp);
            addAndMakeVisible(squareComp);
        }

        grid.templateRows.add(Grid::TrackInfo(1_fr));
        grid.templateColumns.add(Grid::TrackInfo(1_fr));
    }

    for (SquareComponent *squareComp : squareComponents)
        grid.items.add(squareComp);
    grid.performLayout(getLocalBounds());

    std::sort(squareComponents.begin(), squareComponents.end());
}

BoardComponent::~BoardComponent()
{
    //squareComponents.clear();
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
    //for (int i = 0; i < board.getBoardSize(); ++i)
    //    for (int j = 0; j < board.getBoardSize(); ++j)
    //    {
    //        SquareCoordinates coordinates(i, j);
    //        squareComponents[i][j].setState(board.getSquareState(coordinates));
    //        squareComponents[i][j].repaint();
    //    }

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

//void BoardComponent::resized() 
//{
//    Grid grid;
//
//    grid.rowGap     = 2_px;
//    grid.columnGap  = 2_px;
//
//    for (int i = 0; i < board.getBoardSize(); ++i)
//    {
//        grid.templateRows.add(Grid::TrackInfo(1_fr));
//        grid.templateColumns.add(Grid::TrackInfo(1_fr));
//    }
//
//    //for (int i = 0; i < board.getBoardSize(); ++i)
//    //    for (int j = 0; j < board.getBoardSize(); ++j)
//    //        grid.items.add(squareComponents[i][j]);
//
//    for (SquareComponent *squareComp : squareComponents)
//        grid.items.add(squareComp);
//
//
//    grid.performLayout(getLocalBounds());
//}

void BoardComponent::buttonClicked(Button* buttonThatWasClicked)
{
    //TODO use a map or something more intelligent
    //for (int i = 0; i < board.getBoardSize(); ++i)
    //    for (int j = 0; j < board.getBoardSize(); ++j)
    //    {
    //        SquareComponent &squareComp = squareComponents[i][j];
    //        if (buttonThatWasClicked == &squareComp)
    //        {
    //            squareComp.setState(board.placeChip(squareComp.getCoordinates()));
    //            return;
    //        }
    //    }

    SquareComponent* squareComp = reinterpret_cast<SquareComponent*>(buttonThatWasClicked);

    if (std::binary_search(squareComponents.begin(), squareComponents.end(), squareComp))
        squareComp->setState(board.placeChip(squareComp->getCoordinates()));
    else
        jassertfalse; //buttonThatWasClicked not in squareComponents!
}