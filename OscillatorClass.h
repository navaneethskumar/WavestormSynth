/*
  ==============================================================================

    OscillatorClass.h
    Created: 6 Oct 2023 1:23:44pm
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class OscillatorClass {
    //

public:
    std::vector<float>BufferLeft;
    std::vector<float>BufferRight;
    OscillatorClass();
    ~OscillatorClass();
    bool onOff;
    float Fo;
    void setOscillatorState(bool newState);
    
    //void midiToFreq(int midiNote);
    void prepareToPlay(float sampleRate, int samplesPerBlock, int numInputChannels);
    void oscillator(juce::AudioBuffer<float>& buffer, double fs, int waveformIndex);
    bool isOn();
  
   
    //void moduloCounter(float modVal, float modSquareVal, double Fo, double sampleRate);
    //float initializeEnvelopes(int buffLength, int sampleStop);
    void setSampleRamp(int sampleRamp);
    int envelopeIndex;
private:
    float bufferSize;
    int bufferIndex;
    float modVal;
    float modSquareVal;
    int totalNumInputChannels;
    float gain;
    
};
