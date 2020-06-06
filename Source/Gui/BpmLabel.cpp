/*
  ==============================================================================

    BpmLabel.cpp
    Created: 5 Jun 2020 10:46:07pm
    Author:  Eric Majidian

  ==============================================================================
*/

#include "BpmLabel.h"

BpmLabel::BpmLabel()
{
    setLookAndFeel (&mBpmLabelLookAndFeel);
    setJustificationType (Justification::centred);
}

BpmLabel::~BpmLabel()
{
}

void BpmLabel::sliderValueChanged (Slider *slider)
{
    setText (std::to_string (static_cast<int> (mSlider->getValue())), NotificationType::dontSendNotification);
    repaint();
}

void BpmLabel::setSlider (Slider* slider)
{
    mSlider = slider;
    setText (std::to_string (static_cast<int> (mSlider->getValue())), NotificationType::dontSendNotification);
}
