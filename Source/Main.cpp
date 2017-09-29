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
        : DocumentWindow ("JUCE Hello World!",
                          LookAndFeel::getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId),
                          DocumentWindow::allButtons,
                          true)
    {
        // Create an instance of our main content component, and add it to our window..
        setContentOwned (new MainComponent(), true);

        // Centre the window on the screen
        centreWithSize (getWidth(), getHeight());

        // And show it!
        setVisible (true);
    }

    ~ReversiWindow()
    {
        // (the content component will be deleted automatically, so no need to do it here)
    }

    //==============================================================================
    void closeButtonPressed() override
    {
        JUCEApplication::quit();
    }
};

//==============================================================================
/** This is the application object that is started up when Juce starts. It handles
    the initialisation and shutdown of the whole application.
*/
class ReversiApplication : public JUCEApplication
{
public:
    //==============================================================================
    ReversiApplication() {}

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // For this demo, we'll just create the main window...
        reversiWindow = new ReversiWindow();

        /*  ..and now return, which will fall into to the main event
            dispatch loop, and this will run until something calls
            JUCEAppliction::quit().

            In this case, JUCEAppliction::quit() will be called by the
            hello world window being clicked.
        */
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
        // The ProjectInfo::versionString value is automatically updated by the Jucer, and
        // can be found in the JuceHeader.h file that it generates for our project.
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed() override
    {
        return true;
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
    }

private:
    ScopedPointer<ReversiWindow> reversiWindow;
};


//==============================================================================
// This macro creates the application's main() function..
START_JUCE_APPLICATION (ReversiApplication)
