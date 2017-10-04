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

struct SquareComponent 
    : public TextButton
    //, public ImageComponent
{
public:
    SquareComponent(Square::SquareState p_state = Square::SquareState::empty, SquareCoordinates p_coordinates = SquareCoordinates(0,0))
        : TextButton("square")
        , state(p_state)
        , coordinates(p_coordinates)
    {
        woodenBlock = ImageFileFormat::loadFrom(BinaryData::woodenSquare_png, (size_t)BinaryData::woodenSquare_pngSize);
        blackChip   = ImageFileFormat::loadFrom(BinaryData::blackChip_png, (size_t)BinaryData::blackChip_pngSize);
        whiteChip   = ImageFileFormat::loadFrom(BinaryData::whiteChip_png, (size_t)BinaryData::whiteChip_pngSize);
    }

    void paint(Graphics& g) override
    {
        //g.fillAll(Colours::saddlebrown);
        g.drawImage(woodenBlock, getLocalBounds().toFloat(), RectanglePlacement::centred);
        switch (state)
        {
        case Square::empty:
            break;
        case Square::black:
            //g.setColour(Colours::black);
            //g.fillEllipse(getLocalBounds().toFloat());
            g.drawImage(blackChip, getLocalBounds().toFloat(), RectanglePlacement::centred);
            break;
        case Square::white:
            //g.setColour(Colours::white);
            //g.fillEllipse(getLocalBounds().toFloat());
            g.drawImage(whiteChip, getLocalBounds().toFloat(), RectanglePlacement::centred);
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
    Image woodenBlock;
    Image blackChip;
    Image whiteChip;
    Square::SquareState state;
    SquareCoordinates coordinates;
};