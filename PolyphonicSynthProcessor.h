/*
  ==============================================================================

    PolyphonicSynthProcessor.h
    Created: 25 Oct 2023 6:04:34pm
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#pragma once

#include "OscillatorClass.h"
#include <vector>
#include "JuceHeader.h"
class PolyphonicSynthProcessor
    {
    public:
        PolyphonicSynthProcessor() = default;
        ~PolyphonicSynthProcessor() = default;
        //PolyphonicSynthProcessor(const Synth& synth) = default;

        void prepareToPlay(double sampleRate);
       
        void render(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& messages);
       
    private:
        float midiToFreq(int midiNote);
        
        void handleMidiEvent(PolyphonicSynthProcessor);
       
//        void process(juce::AudioBuffer<float>& buffer, const uint32& startSample, const uint32& endSample)


    };

