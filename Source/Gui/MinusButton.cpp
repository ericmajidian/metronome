/*
  ==============================================================================

    MinusButton.cpp
    Created: 6 Jun 2020 8:44:04am
    Author:  Eric Majidian

  ==============================================================================
*/

#include "MinusButton.h"

MinusButton::MinusButton()
    : ShapeButton ("MinusButton", Colours::black, Colours::black, Colours::black)
{
    setSize (40, 40);
    
    int x = getX();
    int y = getY();
    int w = getWidth();
    int h = getHeight();
    int thickness = 8;
    
    Rectangle<int> horizontal (x, y + (h / 2) - (thickness / 2), w, thickness);

    minusSign.addRoundedRectangle (horizontal.toFloat(), 3);

    setShape (minusSign, true, true, false);
}

MinusButton::~MinusButton()
{
}
