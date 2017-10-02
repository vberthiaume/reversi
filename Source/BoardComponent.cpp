/*
  ==============================================================================

    BoardComponent.cpp
    Created: 29 Sep 2017 1:39:57pm
    Author:  barth

  ==============================================================================
*/

#include "BoardComponent.h"

BoardComponent::BoardComponent()
{
    for (int i = 0; i < board.GetBoardSize(); ++i)
        for (int j = 0; j < board.GetBoardSize(); ++j)
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

    for (int i = 0; i < board.GetBoardSize(); ++i)
    {
        grid.templateRows.add(Grid::TrackInfo(1_fr));
        grid.templateColumns.add(Grid::TrackInfo(1_fr));
    }

    for (auto & item : items)
        grid.items.add(item);

    grid.performLayout(getLocalBounds());
}