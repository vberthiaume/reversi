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
#include "BoardComponent.h"


//==============================================================================
class FlashingRectangle : public Component,
    private Timer
{
public:
    FlashingRectangle()
        : flashAlpha(0.0f)
        , colour(Colours::darkgreen)
        , isFadingOut(true)
        , isFlashing(false)
    { }

    void startFlashing()
    {
        isFlashing = true;
        flashAlpha = 1.0f;
        startTimerHz(25);
    }

    void stopFlashing()
    {
        isFlashing = false;
        stopTimer();
        flashAlpha = 0.0f;
        repaint();
    }

    void paint(Graphics& g) override
    {
        Rectangle<float> area(getLocalBounds().toFloat().reduced(2.0f));
        if (isFlashing)
            g.setColour(colour.overlaidWith(Colours::white.withAlpha(flashAlpha)));
        else
            g.setColour(Colours::black);
        g.drawRoundedRectangle(area, 10.0f, 2.0f);
    }

private:
    float flashAlpha;
    Colour colour;
    bool isFadingOut;
    bool isFlashing;

    void timerCallback() override
    {
        if (isFadingOut)
        {
            flashAlpha -= 0.075f;
            if (flashAlpha < 0.05f)
            {
                flashAlpha = 0.05f;
                isFadingOut = false;
            }
        }
        else
        {
            flashAlpha += 0.075f;
            if (flashAlpha > 0.95f)
            {
                flashAlpha = 0.95f;
                isFadingOut = true;
            }
        }

        repaint();
    }
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlashingRectangle)
};

class MainComponent  
    : public Component
    , public BoardChangeListener
{
public:
    //==============================================================================
    MainComponent ();
    ~MainComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void BoardChanged(const BoardChangeEvent &event) override;

private:
    void showGameOverPopUp(size_t blackScore, size_t whiteScore);

    Board board;
    const int labelHeight = 50;

    ScopedPointer<BoardComponent> boardComponent;
    ScopedPointer<Label> blackScoreLabel;
    ScopedPointer<Label> whiteScoreLabel;
    ScopedPointer<FlashingRectangle> blackScoreRectangle;
    ScopedPointer<FlashingRectangle> whiteScoreRectangle;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


