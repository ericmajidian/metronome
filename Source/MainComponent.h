/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Gui/BpmSlider.h"
#include "Gui/BpmLabel.h"
#include "Gui/MinusButton.h"
#include "Gui/PlusButton.h"
#include "Gui/PlayButton.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    //==============================================================================
    void mouseEnter (const MouseEvent &event) override;
    void mouseExit (const MouseEvent &event) override;
    void buttonClicked (Button* button) override;

private:
    //==============================================================================
    // Your private member variables go here...
    Random mRandom;
    Colour mColour {Colours::black};
    
    BpmSlider mBpmSlider;
    BpmLabel mBpmLabel;
    MinusButton mMinusButton;
    PlusButton mPlusButton;
    PlayButton mPlayButton;
    
    WavAudioFormat wavAudioFormat;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
