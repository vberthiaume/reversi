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
#include "Square.h"

struct SquareComponent : public TextButton
{
public:
    SquareComponent(Square::SquareState p_state = Square::SquareState::empty, SquareCoordinates p_coordinates = SquareCoordinates(0,0))
        : TextButton("square")
        , state(p_state)
        , coordinates(p_coordinates)
    {}

    void paint(Graphics& g) override
    {
        g.fillAll(Colours::saddlebrown);
        switch (state)
        {
        case Square::empty:
            break;
        case Square::black:
            g.setColour(Colours::black);
            g.fillEllipse(getLocalBounds().toFloat());
            break;
        case Square::white:
            g.setColour(Colours::white);
            g.fillEllipse(getLocalBounds().toFloat());
            break;
        default:
            jassertfalse;
            break;
        }        
    }

    SquareCoordinates getCoordinates() { return coordinates; }

    void setState(Square::SquareState p_state)
    {
        state = p_state;
    }

    void setCoordinates(int p_r, int p_c)
    {
        coordinates.r = p_r;
        coordinates.c = p_c;
    }

private:
    Square::SquareState state;
    SquareCoordinates coordinates;
};