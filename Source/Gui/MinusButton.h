/*
  ==============================================================================

    MinusButton.h
    Created: 6 Jun 2020 8:44:04am
    Author:  Eric Majidian

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MinusButton : public ShapeButton
{
public:
    MinusButton();
    ~MinusButton();
    
private:
    Path minusSign;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MinusButton)
};
