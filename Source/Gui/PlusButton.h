/*
  ==============================================================================

    PlusButton.h
    Created: 6 Jun 2020 9:24:29am
    Author:  Eric Majidian

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PlusButton : public ShapeButton
{
public:
    PlusButton();
    ~PlusButton();
    
private:
    Path plusSign;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlusButton)
};
