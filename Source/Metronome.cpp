/*
  ==============================================================================

    Metronome.cpp
    Created: 8 Jun 2020 12:33:26pm
    Author:  Eric Majidian

  ==============================================================================
*/

#include "Metronome.h"

Metronome::Metronome()
{
    const ScopedLock sl (mCriticalSection);
    
    WavAudioFormat wavAudioFormat;
    std::unique_ptr<AudioFormatReader> reader (wavAudioFormat.createReaderFor (new MemoryInputStream (BinaryData::WoodBlock_wav, BinaryData::WoodBlock_wavSize, false), true));
    
    if (reader.get() != nullptr)
    {
        mBuffer.setSize (reader->numChannels, static_cast<int> (reader->lengthInSamples));
        reader->read (&mBuffer, 0, static_cast<int> (reader->lengthInSamples), 0, true, true);
    }
    
    mNumSamples = mBuffer.getNumSamples();
}

Metronome::~Metronome()
{
}

void Metronome::prepareToPlay (double sampleRate, int bpm)
{
    const ScopedLock sl (mCriticalSection);

    mNumSamples = sampleRate * 60.0 / bpm;  // Num samples in one beat.
    
    if (mNumSamples > mBuffer.getNumSamples())
        mBuffer.setSize (mBuffer.getNumChannels(), mNumSamples, true, true, false);
    
    mReadPosition = 0;
}

void Metronome::start()
{
    const ScopedLock sl (mCriticalSection);
    
    mReadPosition = 0;
    mState.store (Metronome::State::playing);
}

void Metronome::stop()
{
    mState.store (Metronome::State::stopped);
}

void Metronome::pause()
{
    mPaused.store (true);
}

void Metronome::unpause()
{
    mPaused.store (false);
}

void Metronome::getNextAudioBlock (const AudioSourceChannelInfo& info)
{
    const ScopedLock sl (mCriticalSection);
    
    if (mPaused || mState.load() == Metronome::State::stopped)
    {
        info.clearActiveBufferRegion();
        return;
    }
    
    const int numChannels = jmin (info.buffer->getNumChannels(),
                                  mBuffer.getNumChannels());
    
    // Zero out extra channels, if necessary.
    for (int channel = numChannels; channel < info.buffer->getNumChannels(); ++channel)
        info.buffer->clear (channel, info.startSample, info.numSamples);
    
    if (mNumSamples > mReadPosition + info.numSamples)
    {
        for (int channel = 0; channel < numChannels; ++channel)
        {
            info.buffer->copyFrom (channel, info.startSample, mBuffer, channel, mReadPosition, info.numSamples);
        }
    }
    else
    {
        const int bufferRemaining = mNumSamples - mReadPosition;

        for (int channel = 0; channel < numChannels; ++channel)
        {
            info.buffer->copyFrom (channel, info.startSample, mBuffer, channel, mReadPosition, bufferRemaining);
            info.buffer->copyFrom (channel, info.startSample + bufferRemaining, mBuffer, channel, 0, info.numSamples - bufferRemaining);
        }
    }

    mReadPosition += info.numSamples;
    mReadPosition %= mNumSamples;

    if (mState.load() == Metronome::State::stopped)
    {
        // Fade out
        for (int channel = 0; channel < numChannels; ++channel)
        {
            info.buffer->applyGainRamp (channel, info.startSample, info.numSamples, 1.0f, 0.0f);
        }
    }
}
