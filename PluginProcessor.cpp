/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveStormAudioProcessor::WaveStormAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    Osc = OscillatorClass();
   // *bypassParameter =false;
    totalNumVoices = 16;  // Set this to the maximum number of voices you want to support
    voices.resize(totalNumVoices);
    noteActive.resize(128, false);  // MIDI notes range from 0 to 127

    feedbackSliderParameter = new juce::AudioParameterFloat(juce::ParameterID("1", 1), "Feedback", 0.0f, 100.0f, 5.0f);
    //double fs = getSampleRate();
    //double fs = 48000;
    delayTimeKnobParameter = new juce::AudioParameterFloat(juce::ParameterID("2", 2), "Delay Time", 0.0f, 2.0f, 1.0f);
    dryWetKnobParameter = new juce::AudioParameterFloat(juce::ParameterID("3", 3), "Wetness%", 0.0f, 100.0f, 10.0f);
    eqFcenterKnobParameter = new juce::AudioParameterFloat(juce::ParameterID("4", 4), "F Center", 20.0f, 20000.0f, 500.0f);
    eqQKnobParameter = new juce::AudioParameterFloat(juce::ParameterID("5", 5), " Q Factor", 0.0f, 2.0f, 0.0f);
    eqGainKnobParameter = new juce::AudioParameterFloat(juce::ParameterID("6", 6), "EQ Gain", -20.0f, 20.0f, 0.0f);
    outputGainParameter = new juce::AudioParameterFloat(juce::ParameterID("7", 7), "Output Gain", -20.0f, 20.0f, 0.0f);
    oscillatorTypeParameter = new juce::AudioParameterInt(juce::ParameterID("8", 8), "Oscillator Type", 1, 4, 1);
//
    bypassParameter = new juce::AudioParameterBool(juce::ParameterID("9",9),"bypass",false);
//
//
//    // order matters here - add the slider parameter first and then the knob parameter
    addParameter(feedbackSliderParameter);
    addParameter(delayTimeKnobParameter);
    addParameter(dryWetKnobParameter);
    addParameter(eqFcenterKnobParameter);
    addParameter(eqQKnobParameter);
    addParameter(eqGainKnobParameter);
    addParameter(outputGainParameter);
    addParameter(oscillatorTypeParameter);
    addParameter(bypassParameter);
//
//    //update coefficients
    //float previousFrequency = 500.0f;

    currentFeedback = *feedbackSliderParameter;

    currentDelayTime = *delayTimeKnobParameter;

    currentDryWet = *dryWetKnobParameter;
//   // currentBypassState = *bypassParameter;
    currentEQFcenter = *eqFcenterKnobParameter;
    currentEQQ = *eqQKnobParameter;
    currentEQGain = *eqGainKnobParameter;
    currentOutputGain = *outputGainParameter;
//
//    //
  //  currentOutDryWet = *outDryWetParameter;
    currentOscillatorType = *oscillatorTypeParameter;
    auto numInputs = getTotalNumInputChannels();
    EQ.resetDelay(numInputs);
}

WaveStormAudioProcessor::~WaveStormAudioProcessor()
{
}

//==============================================================================
const juce::String WaveStormAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WaveStormAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WaveStormAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WaveStormAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WaveStormAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WaveStormAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WaveStormAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WaveStormAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WaveStormAudioProcessor::getProgramName (int index)
{
    return {};
}

void WaveStormAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void WaveStormAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
        Osc.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumInputChannels());
        Delay.prepareToPlay(sampleRate, samplesPerBlock, getNumInputChannels());
        int numInputs = getTotalNumInputChannels();
        //myBuffer.setSize(numInputs, samplesPerBlock);
        //reset delays
    
        EQ.resetDelay(numInputs);
}

void WaveStormAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WaveStormAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void WaveStormAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    double sampleRate = getSampleRate();
    
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//
//        // ..do something to the data...
//    }
    if(*oscillatorTypeParameter != currentOscillatorType){
        currentOscillatorType = *oscillatorTypeParameter;
    }
        juce::MidiBuffer::Iterator it(midiMessages);
        juce::MidiMessage currentMessage;
        int samplePosition;
//        //maintain a list of active notes and thier frequency
//       // std::unordered_map<int,float>activeNotes;
//
//        while(it.getNextEvent(currentMessage, samplePosition)){
//            if(currentMessage.isNoteOn()){
//
//
//               int midiNote = currentMessage.getNoteNumber();
//
//                float frequency = 440.0 * pow (2.0, (midiNote - 69.0) / 12.0);
//               // activeNotes[midiNote]=frequency;
//                //int sampleStop=0;
//                Osc.Fo = frequency;
//                Osc.setOscillatorState(true);
//
//
//
//
//            }
//            else if(currentMessage.isNoteOff()){
//                //Osc.initializeEnvelopes(buffer.getNumSamples());
//                    Osc.setOscillatorState(false);
//
//
//    //
//            }
//
////
//            DBG(currentMessage.getDescription());
//            DBG(currentMessage.getTimeStamp());
//        }
   



        // ...



   
        Osc.oscillator(buffer, getSampleRate(), *oscillatorTypeParameter);
    
    //
    isBypassed = *bypassParameter;


    
              
    if(!isBypassed){
        
        if (*delayTimeKnobParameter != currentDelayTime || *feedbackSliderParameter != currentFeedback || *dryWetKnobParameter != currentDryWet) {
            currentDelayTime = *delayTimeKnobParameter;
            currentFeedback = *feedbackSliderParameter;
            currentDryWet = *dryWetKnobParameter;
            //
        }
        
        // Store the current frequency value
        float currentFrequency = *eqFcenterKnobParameter;
        
        // Check if the frequency parameter has changed abruptly
        if (std::abs(currentFrequency - previousFrequency) > 1000.0f)
        {
            // Handle abrupt frequency change smoothly
            currentFrequency = previousFrequency + std::signbit(currentFrequency - previousFrequency) * 1000.0f;
        }
        //
        // Update the previous frequency value
        previousFrequency = currentFrequency;
        
        // Apply the updated frequency value to your parametric EQ
        EQ.updateCoefficients(currentFrequency, *eqQKnobParameter, *eqGainKnobParameter, getSampleRate());
        
        //*************
        //              Delay.circularBuffer(buffer, *delayTimeKnobParameter * getSampleRate(), *feedbackSliderParameter, *dryWetKnobParameter);
        
        //
        // This is the place where you'd normally do the guts of your plugin's
        // audio processing...
        // Make sure to reset the state if your inner loop is processing
        // the samples and the outer loop is handling the channels.
        // Alternatively, you can process the samples with the channels
        // interleaved by keeping the same state.
        double fs = getSampleRate();
        if (*eqGainKnobParameter != currentEQGain || *eqFcenterKnobParameter != currentEQFcenter || *eqFcenterKnobParameter != currentEQQ) {
            EQ.updateCoefficients(*eqFcenterKnobParameter, *eqQKnobParameter, *eqGainKnobParameter, fs);
            currentEQGain = *eqGainKnobParameter;
            currentEQFcenter = *eqFcenterKnobParameter;
            currentEQQ = *eqQKnobParameter;
            
        }
        Delay.circularBuffer(buffer, *delayTimeKnobParameter * getSampleRate(), *feedbackSliderParameter, *dryWetKnobParameter);
        EQ.processAudio(buffer);
        
    }
    
        if (*outputGainParameter != currentOutputGain) {
            outputGain.setGain(*outputGainParameter);
        }
        outputGain.processAudio(buffer);
}

//==============================================================================
bool WaveStormAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WaveStormAudioProcessor::createEditor()
{
    return new WaveStormAudioProcessorEditor (*this);
}

//==============================================================================
void WaveStormAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WaveStormAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WaveStormAudioProcessor();
}
