/*
  ==============================================================================

    OscillatorClass.cpp
    Created: 6 Oct 2023 1:23:44pm
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#include "OscillatorClass.h"
#include <cmath>
OscillatorClass::OscillatorClass() {
    //


    bufferSize = 0 ;
    bufferIndex = 0;
    modVal = -1;
    modSquareVal = 1;
    Fo = 1000.0;
    gain = 0.8;
    onOff = false;


    //
}
OscillatorClass::~OscillatorClass() {

    //
}
void OscillatorClass::prepareToPlay(float sampleRate, int samplesPrerBlock, int numInputChannels)
{

    bufferSize = sampleRate * 2;
    this->totalNumInputChannels = numInputChannels;
    BufferLeft.resize(bufferSize, 0.0f);
    BufferRight.resize(bufferSize, 0.0f);


}
void OscillatorClass::setOscillatorState(bool newState) {
    onOff = newState;

}
bool OscillatorClass::isOn(){
    return onOff;
}

void OscillatorClass::oscillator(juce::AudioBuffer<float>& buffer, double fs, int Type) {
    
    /*auto delayLength = sampleRate * 1.0;*/
    //auto delayBufferSize = delayLength + buffer.getNumSamples();
    //delayBufferSize = delayBufferSize * totalNumInputChannels;
    //delayBuffer.resize(delayBufferSize, 0.f);

    if(onOff){
        
        
        for (int bufferIndex = 0; bufferIndex < buffer.getNumSamples(); bufferIndex++){
  
            modVal += (Fo / (fs));
            if (modVal > 1.0f)
            {
                modVal -= 2.0f;
                modSquareVal *= -1.0f;
            }
            //  moduloCounter(modVal, modSquareVal, Fo, fs);
            switch (Type)
            {
                case 0: // Sinusoidal
                    BufferLeft[bufferIndex] = gain * std::sin(2.0 * juce::MathConstants<float>::pi * modVal);
                    BufferRight[bufferIndex] =  gain * std::sin(2.0 * juce::MathConstants<float>::pi * modVal);
                    break;
                case 1: // Sinusoidal
                    BufferLeft[bufferIndex] = gain * std::sin(2.0 * juce::MathConstants<float>::pi * modVal);
                    BufferRight[bufferIndex] =gain * std::sin(2.0 * juce::MathConstants<float>::pi * modVal);
                    break;
                case 2: // sawtooth
                    BufferLeft[bufferIndex] = gain * modVal;
                    BufferRight[bufferIndex] = gain * modVal;
                    break;
                case 3: // Triangle
                    BufferLeft[bufferIndex] = gain * (2.0f * std::abs(modVal)) - 1.0f;
                    BufferRight[bufferIndex]= gain * (2.0f * std::abs(modVal)) - 1.0f;
                    break;
                case 4: // Square

                    BufferLeft[bufferIndex] = gain * modSquareVal;
                    BufferRight[bufferIndex] = gain * modSquareVal;
                    break;
                default:
                    break;
            }
            //buffer.getWritePointer(0)[bufferIndex] = BufferLeft[bufferIndex];
            //buffer.getWritePointer(1)[bufferIndex] = BufferRight[bufferIndex];
            buffer.setSample(0, bufferIndex, BufferLeft[bufferIndex]);
            buffer.setSample(1, bufferIndex, BufferRight[bufferIndex]);

                           // Apply ramp-down envelope when stopping the oscillator.
                          
        }
        //
    
   

    }

}

//void OscillatorClass::initializeEnvelopes(int buffLength, int sampleStop) {
//       // You can set the envelope shapes based on your preferences.
//       // For example, you can create linear ramps for both.
//       const int envelopeSize = buffLength; // bufferSize is the size you use in prepareToPlay
//       rampUpEnvelope.resize(envelopeSize);
//       rampDownEnvelope.resize(envelopeSize);
//        
//       for (int i = 0; i < envelopeSize; ++i) {
//
//           rampUpEnvelope[i] = (static_cast<float>(i) / envelopeSize);
//           rampDownEnvelope[i] = (1.0f - rampUpEnvelope[i]);
//           
//       }
//    
//    
//}


    
    

// Initialize the envelope vectors with default values.


//void OscillatorClass::moduloCounter(float modVal, float modSquareVal, double Fo, double sampleRate)
//{
//    modVal += (Fo / sampleRate);
//    if (modVal > 1.0)
//    {
//        modVal -= 2.0;
//        modSquareVal *= -1.0;
//    }
//}
