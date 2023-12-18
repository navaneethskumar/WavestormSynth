/*
  ==============================================================================

    parametricEQ.h
    Created: 16 Sep 2023 1:28:22pm
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#pragma once

#pragma once
#include <JuceHeader.h>
class parametricEQ {

public:
    parametricEQ();
    ~parametricEQ();

    void updateCoefficients(int f_center, float Q, float gain, double fs);

    void processAudio(juce::AudioBuffer<float>&);

    void resetDelay(int numInputs);
    void updateDryWetRatio(float ratio);
    
private:
    float a0, a1, a2, b1, b2, d0, w0;
    juce::Array<float> a1_delay, a2_delay, b1_delay, b2_delay;

};
