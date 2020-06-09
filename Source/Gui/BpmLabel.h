/*
  ==============================================================================

    BpmLabel.h
    Created: 5 Jun 2020 10:46:07pm
    Author:  Eric Majidian

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class BpmLabelLookAndFeel : public LookAndFeel_V4
{
public:
    Font getLabelFont (Label &) override
    {
        Font font ( Typeface::createSystemTypefaceFor (BinaryData::OxygenRegular_ttf,
                                                       BinaryData::OxygenRegular_ttfSize));
        font.setHeight (48);
        return font;
    }
};

class BpmLabel : public Label,
                 public Slider::Listener
{
public:
    BpmLabel();
    ~BpmLabel();
    
    void sliderValueChanged (Slider *slider) override;
    
    void setSlider (Slider* slider);

private:
    BpmLabelLookAndFeel mBpmLabelLookAndFeel;
    Slider* mSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BpmLabel)
};
