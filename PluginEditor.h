/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WaveStormAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    WaveStormAudioProcessorEditor (WaveStormAudioProcessor&);
    ~WaveStormAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WaveStormAudioProcessor& audioProcessor;

        juce::Slider feedbackSlider;
        juce::Label feedbackLabel;
        juce::Slider delayTimeKnob;
        juce::Label delayTimeLabel;
        juce::Slider dryWetKnob;
        juce::Label dryWetLabel;
        juce::ToggleButton bypassButton;
        juce::Slider eqFcenterKnob;
        juce::Label eqFcenterLabel;
    
        juce::Slider eqQKnob;
        juce::Label eqQKnobLabel;
        juce::ComboBox oscillatorComboBox;
        juce::Slider eqGainKnob;
        juce::Label eqGainKnobLabel;
    
        juce::Slider outputGainSlider;
        juce::Label outputGainLabel;
        //declaring parameters here
        juce::AudioParameterFloat* feedbackSliderParameter;
        juce::AudioParameterFloat* delayTimeKnobParameter;
        juce::AudioParameterFloat* dryWetKnobParameter;
    
        juce::AudioParameterFloat* eqFcenterKnobParameter;
        juce::AudioParameterFloat* eqQKnobParameter;
        juce::AudioParameterFloat* eqGainKnobParameter;
        juce::AudioParameterInt* oscillatorTypeParameter;
        
        juce::AudioParameterBool* bypassParameter;
    
        juce::Label textLabel;
        juce::Font textFont   { 12.0f };
    juce::Image background;
      juce::AudioParameterFloat* outputGainParameter;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveStormAudioProcessorEditor)
};
