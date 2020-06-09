/*
  ==============================================================================

    BpmSlider.cpp
    Created: 5 Jun 2020 9:52:24pm
    Author:  Eric Majidian

  ==============================================================================
*/

#include "BpmSlider.h"

BpmSlider::BpmSlider()
{
    setSliderStyle (Slider::LinearVertical);
    setRange (40.0, 218.0, 1.0);
    setValue (120.0, NotificationType::dontSendNotification);
    setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    setColour (Slider::trackColourId, Colours::black);
    setLookAndFeel (&mBpmSliderLookAndFeel);
}

BpmSlider::~BpmSlider()
{
}

void BpmSlider::setThumbColour (Colour colour)
{
    mBpmSliderLookAndFeel.setThumbColour (colour);
}
