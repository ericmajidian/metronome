/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible (mBpmLabel);
    addAndMakeVisible (mMinusButton);
    addAndMakeVisible (mPlusButton);
    addAndMakeVisible (mPlayButton);
    addAndMakeVisible (mBpmSlider);

    mBpmLabel.setSlider (&mBpmSlider);
    
    mBpmSlider.setThumbColour (mColour);
    mBpmSlider.addListener (&mBpmLabel);
    
    mMinusButton.addListener (this);
    mMinusButton.addMouseListener (this, false);
    
    mPlusButton.addListener (this);
    mPlusButton.addMouseListener (this, false);
    
    mPlayButton.addListener (this);
    mPlayButton.addMouseListener (this, false);
    mPlayButton.setEnabled (false);

    // Make sure you set the size of the component after
    // you add any child components.
    setSize (200, 500);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
    
    auto* reader = wavAudioFormat.createReaderFor (new MemoryInputStream (BinaryData::WoodBlock_wav, BinaryData::WoodBlock_wavSize, false), true);
    
    if (reader != nullptr)
    {
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, true));
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
        mPlayButton.setEnabled (true);
        readerSource.reset (newSource.release());
    }
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()
    if (readerSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    
    transportSource.getNextAudioBlock (bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    transportSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (mColour);
}

void MainComponent::resized()
{
    auto metronomeBounds = getLocalBounds();
    metronomeBounds.reduce (10, 10);
    
    auto sliderBounds = metronomeBounds.removeFromTop (300);
    sliderBounds.reduce (74, 0);
    mBpmSlider.setBounds (sliderBounds);
    
    auto playButtonBounds = metronomeBounds.removeFromBottom (120);
    playButtonBounds.removeFromTop (20);
    playButtonBounds.reduce (40, 0);
    mPlayButton.setBounds (playButtonBounds);
    
    auto minusButtonBounds = metronomeBounds.removeFromLeft (40);
    minusButtonBounds = minusButtonBounds.removeFromBottom (40);
    minusButtonBounds.reduce (5, 5);
    mMinusButton.setBounds (minusButtonBounds);
    
    auto plusButtonBounds = metronomeBounds.removeFromRight(40);
    plusButtonBounds = plusButtonBounds.removeFromBottom (40);
    plusButtonBounds.reduce (5, 5);
    mPlusButton.setBounds (plusButtonBounds);

    auto labelBounds = metronomeBounds.removeFromBottom (40);
    mBpmLabel.setBounds (labelBounds);
}

void MainComponent::mouseEnter (const MouseEvent &event)
{
    // Expand buttons on hover.
    if (event.eventComponent->isEnabled() &&
        (event.eventComponent == &mPlusButton ||
        event.eventComponent == &mMinusButton ||
        event.eventComponent == &mPlayButton))
    {
        auto bounds = event.eventComponent->getBounds();
        bounds.expand (2, 2);
        event.eventComponent->setBounds (bounds);
    }
}

void MainComponent::mouseExit (const MouseEvent &event)
{
    // Reduce buttons when mouse is no longer hovering.
    if (event.eventComponent->isEnabled() &&
        (event.eventComponent == &mPlusButton ||
        event.eventComponent == &mMinusButton ||
        event.eventComponent == &mPlayButton))
    {
        auto bounds = event.eventComponent->getBounds();
        bounds.reduce (2, 2);
        event.eventComponent->setBounds (bounds);
    }
}

//==============================================================================
void MainComponent::buttonClicked (Button* button)
{
    if (button == &mMinusButton)
    {
        mBpmSlider.setValue (mBpmSlider.getValue() - 1);
    }
    else if (button == &mPlusButton)
    {
        mBpmSlider.setValue (mBpmSlider.getValue() + 1);
    }
    else if (button == &mPlayButton)
    {
        if (button->getToggleState())
        {
            transportSource.start();
        }
        else
        {
            transportSource.stop();
            transportSource.setPosition (0.0);
        }
    }
}
