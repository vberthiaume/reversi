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

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "Board.h"
#include "BoardComponent.h"

//==============================================================================
/**
    This is the top-level window that we'll pop up. Inside it, we'll create and
    show a component from the MainComponent.cpp file (you can open this file using
    the Jucer to edit it).
*/
class ReversiWindow  : public DocumentWindow
{
public:
    //==============================================================================
    ReversiWindow()
        : DocumentWindow ("Reversi!",
                          LookAndFeel::getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId),
                          DocumentWindow::allButtons,
                          true)
    {
        setContentOwned (new MainComponent(), true);
        centreWithSize (getWidth(), getHeight());
        setVisible (true);
    }

    ~ReversiWindow()
    {
    }

    //==============================================================================
    void closeButtonPressed() override
    {
        JUCEApplication::quit();
    }
};

//==============================================================================

class ReversiApplication : public JUCEApplication
{
public:
    //==============================================================================
    ReversiApplication() {}

    //==============================================================================
    void initialise (const String& /*commandLine*/) override
    {
        reversiWindow = new ReversiWindow();
    }

    void shutdown() override
    {
        reversiWindow = nullptr;
    }

    //==============================================================================
    const String getApplicationName() override
    {
        return "Reversi!";
    }

    const String getApplicationVersion() override
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed() override
    {
        return true;
    }

    void anotherInstanceStarted (const String& /*commandLine*/) override
    {
    }

private:
    ScopedPointer<ReversiWindow> reversiWindow;
};


//==============================================================================
// This macro creates the application's main() function..
START_JUCE_APPLICATION (ReversiApplication)
