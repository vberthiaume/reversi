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


class BoardComponent : public Component, public SquareComponent::Listener
{
public:
    BoardComponent();

    void paint(Graphics& g) override;

    void resized() override;

    void buttonClicked(Button* buttonThatWasClicked) override;

private:
    void addSquare(Square::SquareState state, int x, int y)
    {
        SquareComponent *squareComp = new SquareComponent(state, x, y);
        addAndMakeVisible(items.add(squareComp));
        squareComp->addListener(this);
    }

    OwnedArray<SquareComponent> items;
    Board board;
};