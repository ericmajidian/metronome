/*
  ==============================================================================

    PlusButton.cpp
    Created: 6 Jun 2020 9:24:29am
    Author:  Eric Majidian

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlusButton.h"

PlusButton::PlusButton()
    : ShapeButton ("PlusButton", Colours::black, Colours::black, Colours::black)
{
    setSize (40, 40);
    
    int x = getX();
    int y = getY();
    int w = getWidth();
    int h = getHeight();
    int thickness = 8;
    
    Rectangle<int> horizontal (x, y + (h / 2) - (thickness / 2), w, thickness);
    Rectangle<int> vertical (x + (w / 2) - (thickness / 2), y, thickness, h);

    plusSign.addRoundedRectangle (horizontal.toFloat(), 3);
    plusSign.addRoundedRectangle (vertical.toFloat(), 3);

    setShape (plusSign, true, true, false);
}

PlusButton::~PlusButton()
{
}
