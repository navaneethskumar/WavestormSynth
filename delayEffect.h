/*
  ==============================================================================

    delayEffect.h
    Created: 16 Sep 2023 1:29:07pm
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class delayEffect {
    //

public:
    std::vector<float>delayBufferLeft;
    std::vector<float>delayBufferRight;
    delayEffect();
    ~delayEffect();
    
    void prepareToPlay(float sampleRate, int samplesPerBlock, int numInputChannels);
    void circularBuffer(juce::AudioBuffer<float>& buffer, float delayLength, float feedback, float dryWet);

private:

    float delayBufferSize;
    float bufferSize;
    int totalNumInputChannels;

    int readIndexL;
    int readIndexR;
    int writeIndexL;
    int writeIndexR;

};
