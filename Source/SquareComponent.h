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

#ifndef USE_IMAGES
#define USE_IMAGES 1
#endif

struct SquareComponent 
    : public TextButton
{
public:
    SquareComponent(Square::SquareState p_state = Square::SquareState::empty, SquareCoordinates p_coordinates = SquareCoordinates(0,0))
        : TextButton("square")
        , state(p_state)
        , coordinates(p_coordinates)
    {
#if USE_IMAGES
        emptySquare = ImageFileFormat::loadFrom(BinaryData::greenSquare_png, (size_t)BinaryData::greenSquare_pngSize);
        blackChip = ImageFileFormat::loadFrom(BinaryData::blackChip225_png, (size_t)BinaryData::blackChip225_pngSize);
        whiteChip = ImageFileFormat::loadFrom(BinaryData::whiteChip225_png, (size_t)BinaryData::whiteChip225_pngSize);
#endif
    }

    void paint(Graphics& g) override
    {
#if USE_IMAGES
        g.drawImage(emptySquare, getLocalBounds().toFloat(), RectanglePlacement::centred);
#else
        g.fillAll(Colours::saddlebrown);
#endif
        switch (state)
        {
        case Square::empty:
            break;
        case Square::black:
#if USE_IMAGES
            g.drawImage(blackChip, getLocalBounds().toFloat(), RectanglePlacement::centred);
#else
            g.setColour(Colours::black);
            g.fillEllipse(getLocalBounds().toFloat());
#endif
            break;
        case Square::white:
#if USE_IMAGES
            g.drawImage(whiteChip, getLocalBounds().toFloat(), RectanglePlacement::centred);
#else
            g.setColour(Colours::white);
            g.fillEllipse(getLocalBounds().toFloat());
#endif
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
    Image emptySquare;
    Image blackChip;
    Image whiteChip;
    Square::SquareState state;
    SquareCoordinates coordinates;
};