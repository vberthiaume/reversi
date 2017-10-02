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

#include "../JuceLibraryCode/JuceHeader.h"
#include "Board.h"
#include "SquareComponent.h"


class BoardComponent 
    : public Component
    , public SquareComponent::Listener
    , private Timer
{
public:
    BoardComponent();

    void BoardComponent::initBoard();

    void paint(Graphics& g) override;

    void resized() override;

    void buttonClicked(Button* buttonThatWasClicked) override;

    void timerCallback() override;

private:
    //void addSquare(Square::SquareState state, SquareCoordinates coordinates);
    void updateWholeBoard();

    /*OwnedArray<SquareComponent> squareComponents;*/
    SquareComponent squareComponents[BOARD_SIZE][BOARD_SIZE];
    Board board;
};