/*
  ==============================================================================

    BoardComponent.h
    Created: 29 Sep 2017 1:39:57pm
    Author:  barth

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Board.h"
#include "SquareComponent.h";


class BoardComponent : public Component
{
public:
    BoardComponent();

    void paint(Graphics& g) override;

    void resized() override;

private:
    void addSquare(Square::SquareState state, int x, int y)
    {
        addAndMakeVisible(items.add(new SquareComponent(state)));
    }

    OwnedArray<SquareComponent> items;
    Board board;
};