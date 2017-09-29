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

    setSize (600, 300);

}

MainComponent::~MainComponent()
{


    //helloWorldLabel = nullptr;
    //quitButton = nullptr;


}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xffc1d0ff));

}

void MainComponent::resized()
{

}

void MainComponent::buttonClicked (Button* /*buttonThatWasClicked*/)
{

}


