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
    SquareComponent(Square::SquareState p_state, int p_x, int p_y)
        : TextButton("square")
        , state(p_state)
        , coordinates(p_x, p_y)
    {}

    void paint(Graphics& g) override
    {
        switch (state)
        {
        case Square::empty:
            g.fillAll(Colours::grey);
            break;
        case Square::black:
            g.fillAll(Colours::black);
            break;
        case Square::white:
            g.fillAll(Colours::white);
            break;
        default:
            jassertfalse;
            break;
        }

        g.setColour(Colours::purple);
    }

    SquareCoordinates getCoordinates() { return coordinates; }

    void setState(Square::SquareState p_state)
    {
        state = p_state;
    }

private:
    Square::SquareState state;
    SquareCoordinates coordinates;
};