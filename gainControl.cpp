/*
  ==============================================================================

    gainControl.cpp
    Created: 16 Sep 2023 4:38:17pm
    Author:  Admin

  ==============================================================================
*/
#include "gainControl.h"
#include <cmath>

// Constructor
gainControl::gainControl() {
    gaindB = 0.0;
}

// Destructor
gainControl::~gainControl() {}

// Set the gain in decibels (dB)
void gainControl::setGain(double gainInDecibels) {
    gaindB = gainInDecibels;
}
// Apply gain to an entire audio buffer
void gainControl::processAudio(juce::AudioBuffer<float>& buffer) {
    auto totalNumInputChannels = buffer.getNumChannels();
    for (int channel = 0; channel < totalNumInputChannels; channel++) {
        for (int n = 0; n < buffer.getNumSamples(); n++) {
            float gainLinear = std::pow(10.0, gaindB / 20.0);
            buffer.getWritePointer(channel)[n] *= gainLinear;
        }
        }
}
