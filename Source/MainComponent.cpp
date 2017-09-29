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


//==============================================================================
MainComponent::MainComponent ()
{

    addAndMakeVisible (helloWorldLabel = new Label (String(), TRANS("Hello World!")));
    helloWorldLabel->setFont (Font (40.00f, Font::bold));
    helloWorldLabel->setJustificationType (Justification::centred);
    helloWorldLabel->setEditable (false, false, false);
    helloWorldLabel->setColour (Label::textColourId, Colours::black);
    helloWorldLabel->setColour (TextEditor::textColourId, Colours::black);
    helloWorldLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (quitButton = new TextButton (String()));
    quitButton->setButtonText (TRANS("Quit"));
    quitButton->addListener (this);

    setSize (600, 300);

}

MainComponent::~MainComponent()
{


    helloWorldLabel = nullptr;
    quitButton = nullptr;


}

//==============================================================================
void MainComponent::paint (Graphics& g)
{


    g.fillAll (Colour (0xffc1d0ff));

    g.setColour (Colours::white);
    g.fillPath (internalPath1);
    g.setColour (Colour (0xff6f6f6f));
    g.strokePath (internalPath1, PathStrokeType (5.200f));


}

void MainComponent::resized()
{


    helloWorldLabel->setBounds (152, 80, 296, 48);
    quitButton->setBounds (getWidth() - 176, getHeight() - 60, 120, 32);
    internalPath1.clear();
    internalPath1.startNewSubPath (136.0f, 80.0f);
    internalPath1.quadraticTo (176.0f, 24.0f, 328.0f, 32.0f);
    internalPath1.quadraticTo (472.0f, 40.0f, 472.0f, 104.0f);
    internalPath1.quadraticTo (472.0f, 192.0f, 232.0f, 176.0f);
    internalPath1.lineTo (184.0f, 216.0f);
    internalPath1.lineTo (200.0f, 168.0f);
    internalPath1.quadraticTo (96.0f, 136.0f, 136.0f, 80.0f);
    internalPath1.closeSubPath();


}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{

    if (buttonThatWasClicked == quitButton)
    {

        JUCEApplication::quit();


    }

}


