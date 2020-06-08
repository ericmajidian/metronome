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
    mNumSamples = sampleRate * 60.0 / bpm;
    
    if (mNumSamples > mBuffer.getNumSamples())
        mBuffer.setSize (mBuffer.getNumChannels(), mNumSamples, true, true, false);
}

void Metronome::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    const int numChannels = jmin (bufferToFill.buffer->getNumChannels(),
                                  mBuffer.getNumChannels());
    
    // Clear out extra channels, if necessary
    for (int channel = numChannels; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        bufferToFill.buffer->clear (channel, bufferToFill.startSample, bufferToFill.numSamples);
    
    if (mNumSamples > mReadPosition + bufferToFill.numSamples)
    {
        for (int channel = 0; channel < numChannels; ++channel)
        {
            bufferToFill.buffer->copyFrom (channel, bufferToFill.startSample, mBuffer, channel, mReadPosition, bufferToFill.numSamples);
        }
    }
    else
    {
        const int bufferRemaining = mNumSamples - mReadPosition;
        
        for (int channel = 0; channel < numChannels; ++channel)
        {
            bufferToFill.buffer->copyFrom (channel, bufferToFill.startSample, mBuffer, channel, mReadPosition, bufferRemaining);
            bufferToFill.buffer->copyFrom (channel, bufferToFill.startSample + bufferRemaining, mBuffer, channel, 0, bufferToFill.numSamples - bufferRemaining);
        }
    }
    
    mReadPosition += bufferToFill.numSamples;
    mReadPosition %= mNumSamples;
}
