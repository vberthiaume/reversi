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

#include "MainComponent.h"
#include "BoardComponent.h"
#include <string>

//==============================================================================
MainComponent::MainComponent ()
{
    addAndMakeVisible(boardComponent = new BoardComponent(&board));
    board.addBoardBoardChangeListener(this);
    board.addBoardBoardChangeListener(boardComponent);

    addAndMakeVisible(blackScoreLabel = new Label("blackScoreLabel", "BLACK: 2"));
    addAndMakeVisible(whiteScoreLabel = new Label("whiteScoreLabel", "WHITE: 2"));
    blackScoreLabel->setJustificationType(Justification::centred);
    whiteScoreLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(blackScoreRectangle = new FlashingRectangle());
    addAndMakeVisible(whiteScoreRectangle = new FlashingRectangle());
        
    setSize (boardComponent->getWidth(), boardComponent->getHeight() + labelHeight);

    board.initBoard();
}

MainComponent::~MainComponent()
{
    boardComponent = nullptr;
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xffc1d0ff));
    boardComponent->paint(g);
}

void MainComponent::resized()
{
    boardComponent->resized();

    int width = boardComponent->getWidth();
    int height = boardComponent->getHeight();

    blackScoreLabel->setBounds(0, height, width/2, labelHeight);
    blackScoreRectangle->setBounds(0, height, width / 2, labelHeight);

    whiteScoreLabel->setBounds(width / 2, height, width/2, labelHeight);
    whiteScoreRectangle->setBounds(width / 2, height, width / 2, labelHeight);

    setSize(width, height + labelHeight);
}

//TODO: this event needs to receive a structure that says whose turn it is, if we need to reset and scores
void MainComponent::BoardChanged(Scores scores, bool needToReset)
{
    blackScoreLabel->setText("BLACK: " + std::to_string(scores.black), dontSendNotification);
    whiteScoreLabel->setText("WHITE: " + std::to_string(scores.white), dontSendNotification);

    blackScoreRectangle->startFlashing();
    whiteScoreRectangle->startFlashing();
}


