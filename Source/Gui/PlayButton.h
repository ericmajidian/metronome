/*
  ==============================================================================

    PlayButton.h
    Created: 6 Jun 2020 9:47:56am
    Author:  Eric Majidian

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PlayButtonLookAndFeel : public LookAndFeel_V4
{
public:
    void drawToggleButton (Graphics& g, ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
    {
        auto bounds = button.getLocalBounds();
        bounds.reduce (8, 8);
        g.drawEllipse (bounds.toFloat(), 8);
        
        Path p;

        if (button.getToggleState())
        {
            bounds.reduce (25, 25);
            p.addRectangle (bounds.getX() + 2, bounds.getY(), 10, bounds.getHeight());
            p.addRectangle (bounds.getX() + bounds.getWidth() - 12, bounds.getY(), 10, bounds.getHeight());
        }
        else
        {
            bounds.reduce (25, 20);
            bounds.setX (bounds.getX() + 5);
            p.addTriangle (bounds.getX(), bounds.getY(),
                           bounds.getX(), bounds.getY() + bounds.getHeight(),
                           bounds.getX() + bounds.getWidth(), bounds.getY() + (bounds.getHeight() / 2));
        }
        
        g.fillPath (p);
    }
};

//==============================================================================
/*
*/
class PlayButton : public ToggleButton
{
public:
    PlayButton();
    ~PlayButton();

private:
    PlayButtonLookAndFeel mPlayButtonLookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayButton)
};
