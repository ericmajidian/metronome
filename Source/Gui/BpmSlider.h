/*
  ==============================================================================

    BpmSlider.h
    Created: 5 Jun 2020 9:52:24pm
    Author:  Eric Majidian

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class BpmSliderLookAndFeel : public LookAndFeel_V4
{
public:
    void drawLinearSlider (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider) override
    {
        drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
    
    void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                                     float sliderPos,
                                                     float minSliderPos,
                                                     float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override
    {
        auto sliderRadius = (float) (getSliderThumbRadius (slider) - 6);
        auto trackColour = slider.findColour (Slider::trackColourId);
        auto gradCol1 = trackColour.overlaidWith (Colours::black.withAlpha (slider.isEnabled() ? 0.25f : 0.13f));
        auto gradCol2 = trackColour.overlaidWith (Colour (0x14000000));

        Path indent;

        const float ix = x + width * 0.5f - sliderRadius * 0.5f;
        const float iw = sliderRadius;

        g.setGradientFill (ColourGradient::horizontal (gradCol1, ix, gradCol2, ix + iw));

        indent.addRoundedRectangle (ix,
                                    y - sliderRadius * 0.5f,
                                    iw,
                                    height + sliderRadius,
                                    5.0f);

        g.fillPath (indent);

        g.setColour (Colour (0x4c000000));
        g.strokePath (indent, PathStrokeType (0.5f));
    }

    void drawLinearSliderThumb (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider) override
    {
        auto sliderRadius = (float) (getSliderThumbRadius (slider) - 4);
        
        float kx, ky;

        kx = x + width * 0.5f;
        ky = sliderPos;

        g.setColour (mThumbColour);
        g.fillEllipse (kx - sliderRadius, ky - sliderRadius, sliderRadius * 2, sliderRadius * 2);
        g.setColour (Colours::black);
        g.drawEllipse (kx - sliderRadius, ky - sliderRadius, sliderRadius * 2, sliderRadius * 2, 5);
    }
    
    int getSliderThumbRadius (Slider& slider) override
    {
        return 16;
    }

    void setThumbColour (Colour colour)
    {
        mThumbColour = colour;
    }
    
private:
    Colour mThumbColour {Colours::black};
};

class BpmSlider : public Slider
{
public:
    BpmSlider();
    ~BpmSlider();
    
    void setThumbColour (Colour colour);
    
private:
    BpmSliderLookAndFeel mBpmSliderLookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BpmSlider)
};
