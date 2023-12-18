/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#include "OscillatorClass.h"
#include "parametricEQ.h"
#include "delayEffect.h"
#include "gainControl.h"
#include <JuceHeader.h>

//==============================================================================
/**
*/
class WaveStormAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    WaveStormAudioProcessor();
    ~WaveStormAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveStormAudioProcessor)
    
        delayEffect Delay;
        parametricEQ EQ;
        gainControl outputGain;
        OscillatorClass Osc;
        juce::AudioParameterFloat* feedbackSliderParameter;
        juce::AudioParameterFloat* delayTimeKnobParameter;
        juce::AudioParameterFloat* dryWetKnobParameter;
        juce::AudioParameterFloat* eqFcenterKnobParameter;
        juce::AudioParameterFloat* eqQKnobParameter;
        juce::AudioParameterFloat* eqGainKnobParameter;
        juce::AudioParameterFloat* outputGainParameter;
        juce::AudioParameterInt* oscillatorTypeParameter;
        juce::AudioParameterFloat* outDryWetParameter;
        juce::AudioBuffer<float> myBuffer;
        juce::AudioParameterBool* bypassParameter;
        
        bool isBypassed;
        float previousFrequency = 500.0f;
        float currentFeedback;
        float currentDelayTime;
        float currentDryWet;
        float currentEQFcenter;
        float currentEQQ;
        float currentEQGain;
        float currentOutputGain;
        float currentOutDryWet;
        int currentOscillatorType;

    std::vector<OscillatorClass> voices;  // Array of OscillatorClass instances
    std::vector<bool> noteActive;  // Tracks active MIDI notes
    int totalNumVoices;

};
