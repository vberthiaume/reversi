/*
  ==============================================================================

    SquareComponent.h
    Created: 29 Sep 2017 3:46:09pm
    Author:  barth

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Square.h"

struct SquareComponent : public Component
{
    SquareComponent(Square::SquareState p_state)
        : state(p_state)
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
    Square::SquareState state;
};