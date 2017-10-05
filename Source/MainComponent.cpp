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

void MainComponent::BoardChanged(const BoardChangeEvent &event)
{
    if (event.needToReset)
    {
        blackScoreRectangle->stopFlashing();
        whiteScoreRectangle->stopFlashing();
        showGameOverPopUp (event.scores.black, event.scores.white);
        board.initBoard();
        return;
    }

    blackScoreLabel->setText("BLACK: " + std::to_string(event.scores.black), dontSendNotification);
    whiteScoreLabel->setText("WHITE: " + std::to_string(event.scores.white), dontSendNotification);
    
    if (event.isBlackTurn)
    {
        blackScoreRectangle->startFlashing();
        whiteScoreRectangle->stopFlashing();
    }
    else
    {
        whiteScoreRectangle->startFlashing();
        blackScoreRectangle->stopFlashing();
    }
}

void MainComponent::showGameOverPopUp(size_t blackScore, size_t whiteScore)
{
    std::string text = "Game over! ";
    if (blackScore > whiteScore)
        text += "Black won " + std::to_string(blackScore) + " vs " + std::to_string(whiteScore) + ".";
    else if (whiteScore > blackScore)
        text += "White won " + std::to_string(whiteScore) + " vs " + std::to_string(blackScore) + ".";
    else
        text += "It's a tie, " + std::to_string(whiteScore) + " vs " + std::to_string(blackScore) + ".";
            
    text += " Click OK to play again!";
    AlertWindow::showMessageBox(AlertWindow::InfoIcon, "Game over!", text);
}
