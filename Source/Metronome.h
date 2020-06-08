/*
  ==============================================================================

    Metronome.h
    Created: 8 Jun 2020 12:33:26pm
    Author:  Eric Majidian

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Metronome
{
public:
    Metronome();
    ~Metronome();
    
    /** Set mNumSamples to the number of samples in a beat given the sample rate and
        beats per minute.
         
        mBuffer may be resized if the number of samples in a beat exceeds the length of
        the buffer.
     */
    void prepareToPlay (double sampleRate, int bpm);
    
    /** Get the next audio block from the local buffer. */
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);

private:
    AudioBuffer<float> mBuffer;
    int mNumSamples {0};
    int mReadPosition {0};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Metronome)
};
