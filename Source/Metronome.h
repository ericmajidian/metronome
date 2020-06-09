/*
  ==============================================================================

    Metronome.h
    Created: 8 Jun 2020 12:33:26pm
    Author:  Eric Majidian

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/**
    Provides methods to manage playback of a circular buffer containing a metronome 'click' tone.
 */
class Metronome
{
public:
    /** Read in the metronome tone and store it in the local private buffer. */
    Metronome();
    
    ~Metronome();
    
    /** Set mNumSamples to the number of samples in a beat given the sample rate and
        beats per minute.
         
        mBuffer may be resized if the number of samples in a beat exceeds the length of
        the buffer.
     
        Note: This will also reset the buffer's read position to 0.
     */
    void prepareToPlay (double sampleRate, int bpm);
    
    /** Start playback.
     
        Note: This will also reset the buffer's read position to 0.
     */
    void start();
    
    /** Stop playback. */
    void stop();
    
    /** Pause playback. The metronome state (i.e. playing, stopped) can still be changed freely. */
    void pause();
    
    /** Unpause playback. */
    void unpause();

    /** Get the next audio block from the local buffer. */
    void getNextAudioBlock (const AudioSourceChannelInfo& info);
    
    enum class State {playing, stopped};

private:
    AudioBuffer<float> mBuffer;
    int mNumSamples {0};
    int mReadPosition {0};
    std::atomic<Metronome::State> mState {Metronome::State::stopped};
    std::atomic<bool> mPaused {false};

    CriticalSection mCriticalSection;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Metronome)
};
