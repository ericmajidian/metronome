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
#include "Metronome.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Slider::Listener,
                        public Button::Listener,
                        public Timer
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
    void sliderValueChanged (Slider*) override;
    void buttonClicked (Button* button) override;
    void timerCallback() override;

private:
    Random mRandom;
    Colour mColour {Colours::black};
    
    BpmSlider mBpmSlider;
    BpmLabel mBpmLabel;
    MinusButton mMinusButton;
    PlusButton mPlusButton;
    PlayButton mPlayButton;
    
    Metronome mMetronome;
    
    double mSampleRate {44100};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
