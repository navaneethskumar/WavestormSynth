/*
  ==============================================================================

    gainControl.h
    Created: 16 Sep 2023 4:38:17pm
    Author:  Admin

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class gainControl {
public:
    gainControl();
    ~gainControl();
    void setGain(double gainInDecibels);
    void processAudio(juce::AudioBuffer<float>&);
private:
    float gaindB;

};